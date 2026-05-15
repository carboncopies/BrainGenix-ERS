//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <AudioPlaybackSystem.h>

// Standard Libraries (BG convention: use <> instead of "")
#include <algorithm>
#include <cstring>
#include <limits>

// Third-Party Libraries (BG convention: use <> instead of "")
// cppcheck-suppress missingIncludeSystem
#include <AL/al.h>
// cppcheck-suppress missingIncludeSystem
#include <AL/alc.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ConvertRotationToFrontVector.h>


namespace {

struct DecodedWavClip {
    int Format = 0;
    int Frequency = 0;
    std::vector<unsigned char> Samples;
};

bool ERS_FUNCTION_AudioChunkMatches(const unsigned char* Data, const char* ChunkName) {
    return std::memcmp(Data, ChunkName, 4) == 0;
}

unsigned short ERS_FUNCTION_ReadLE16(const unsigned char* Data) {
    return static_cast<unsigned short>(Data[0])
        | static_cast<unsigned short>(Data[1] << 8);
}

unsigned int ERS_FUNCTION_ReadLE32(const unsigned char* Data) {
    return static_cast<unsigned int>(Data[0])
        | (static_cast<unsigned int>(Data[1]) << 8)
        | (static_cast<unsigned int>(Data[2]) << 16)
        | (static_cast<unsigned int>(Data[3]) << 24);
}

bool ERS_FUNCTION_DecodePCM16Or8Wav(const unsigned char* Data, std::size_t Size, DecodedWavClip& Output, std::string& Error) {
    if (Data == nullptr || Size < 12) {
        Error = "Audio asset is too small to be a WAV file.";
        return false;
    }

    if (!ERS_FUNCTION_AudioChunkMatches(Data, "RIFF") || !ERS_FUNCTION_AudioChunkMatches(Data + 8, "WAVE")) {
        Error = "Audio asset is not a RIFF/WAVE file.";
        return false;
    }

    bool FoundFormat = false;
    bool FoundData = false;
    unsigned short AudioFormat = 0;
    unsigned short ChannelCount = 0;
    unsigned short BitsPerSample = 0;
    unsigned int SampleRate = 0;
    std::vector<unsigned char> PCMData;

    std::size_t Offset = 12;
    while (Offset + 8 <= Size) {
        const unsigned char* Chunk = Data + Offset;
        unsigned int ChunkSize = ERS_FUNCTION_ReadLE32(Chunk + 4);
        std::size_t ChunkDataOffset = Offset + 8;
        std::size_t NextOffset = ChunkDataOffset + ChunkSize + (ChunkSize % 2);

        if (ChunkDataOffset + ChunkSize > Size || NextOffset < Offset) {
            Error = "WAV chunk extends past the end of the asset.";
            return false;
        }

        if (ERS_FUNCTION_AudioChunkMatches(Chunk, "fmt ")) {
            if (ChunkSize < 16) {
                Error = "WAV fmt chunk is shorter than PCM metadata.";
                return false;
            }

            const unsigned char* Format = Data + ChunkDataOffset;
            AudioFormat = ERS_FUNCTION_ReadLE16(Format);
            ChannelCount = ERS_FUNCTION_ReadLE16(Format + 2);
            SampleRate = ERS_FUNCTION_ReadLE32(Format + 4);
            BitsPerSample = ERS_FUNCTION_ReadLE16(Format + 14);
            FoundFormat = true;
        } else if (ERS_FUNCTION_AudioChunkMatches(Chunk, "data")) {
            PCMData.assign(Data + ChunkDataOffset, Data + ChunkDataOffset + ChunkSize);
            FoundData = true;
        }

        Offset = NextOffset;
    }

    if (!FoundFormat || !FoundData) {
        Error = "WAV asset is missing a fmt or data chunk.";
        return false;
    }

    if (AudioFormat != 1) {
        Error = "Only uncompressed PCM WAV audio is supported.";
        return false;
    }

    if (SampleRate == 0) {
        Error = "WAV sample rate is invalid.";
        return false;
    }

    if (ChannelCount == 1 && BitsPerSample == 8) {
        Output.Format = AL_FORMAT_MONO8;
    } else if (ChannelCount == 2 && BitsPerSample == 8) {
        Output.Format = AL_FORMAT_STEREO8;
    } else if (ChannelCount == 1 && BitsPerSample == 16) {
        Output.Format = AL_FORMAT_MONO16;
    } else if (ChannelCount == 2 && BitsPerSample == 16) {
        Output.Format = AL_FORMAT_STEREO16;
    } else {
        Error = "Only mono/stereo 8-bit or 16-bit PCM WAV audio is supported.";
        return false;
    }

    if (PCMData.empty()) {
        Error = "WAV data chunk is empty.";
        return false;
    }

    Output.Frequency = static_cast<int>(SampleRate);
    Output.Samples = std::move(PCMData);
    return true;
}

} // namespace


ERS_CLASS_AudioPlaybackSystem::ERS_CLASS_AudioPlaybackSystem(ERS_STRUCT_SystemUtils* SystemUtils) {
    SystemUtils_ = SystemUtils;
}

ERS_CLASS_AudioPlaybackSystem::~ERS_CLASS_AudioPlaybackSystem() {
    StopScenePlayback();
    DeleteClipBuffers();
    Shutdown();
}

bool ERS_CLASS_AudioPlaybackSystem::IsAvailable() const {
    return Available_;
}

bool ERS_CLASS_AudioPlaybackSystem::Initialize() {
    if (Available_) {
        return true;
    }

    if (InitializationAttempted_) {
        return false;
    }
    InitializationAttempted_ = true;

    Device_ = alcOpenDevice(nullptr);
    if (Device_ == nullptr) {
        SystemUtils_->Logger_->Log("OpenAL audio device could not be opened; runtime audio playback is disabled.", 7);
        return false;
    }

    Context_ = alcCreateContext(Device_, nullptr);
    if (Context_ == nullptr) {
        SystemUtils_->Logger_->Log("OpenAL audio context could not be created; runtime audio playback is disabled.", 7);
        alcCloseDevice(Device_);
        Device_ = nullptr;
        return false;
    }

    if (alcMakeContextCurrent(Context_) == ALC_FALSE) {
        SystemUtils_->Logger_->Log("OpenAL audio context could not be activated; runtime audio playback is disabled.", 7);
        alcDestroyContext(Context_);
        alcCloseDevice(Device_);
        Context_ = nullptr;
        Device_ = nullptr;
        return false;
    }

    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
    Available_ = true;
    SystemUtils_->Logger_->Log("Initialized OpenAL audio playback system", 4);
    return true;
}

void ERS_CLASS_AudioPlaybackSystem::Shutdown() {
    if (Context_ != nullptr) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(Context_);
        Context_ = nullptr;
    }

    if (Device_ != nullptr) {
        alcCloseDevice(Device_);
        Device_ = nullptr;
    }

    Available_ = false;
}

void ERS_CLASS_AudioPlaybackSystem::DeleteClipBuffers() {
    for (auto& Buffer : ClipBuffers_) {
        unsigned int BufferID = Buffer.second;
        if (BufferID != 0) {
            alDeleteBuffers(1, &BufferID);
        }
    }
    ClipBuffers_.clear();
}

bool ERS_CLASS_AudioPlaybackSystem::LogOpenALError(const std::string& Context) {
    int ErrorCode = alGetError();
    if (ErrorCode != AL_NO_ERROR) {
        std::string Message = Context + " failed with OpenAL error " + std::to_string(ErrorCode);
        SystemUtils_->Logger_->Log(Message.c_str(), 7);
        return false;
    }
    return true;
}

unsigned int ERS_CLASS_AudioPlaybackSystem::LoadClipBuffer(long AssetID) {
    if (AssetID < 0) {
        return 0;
    }

    auto ExistingBuffer = ClipBuffers_.find(AssetID);
    if (ExistingBuffer != ClipBuffers_.end()) {
        return ExistingBuffer->second;
    }

    BG::ERS::IOSubsystem::IOData AudioData;
    bool ReadStatus = SystemUtils_->ERS_IOSubsystem_->ReadAsset(AssetID, &AudioData);
    if (!ReadStatus || AudioData.Data == nullptr || AudioData.Size_B == 0) {
        std::string Message = "Could not read audio asset " + std::to_string(AssetID);
        SystemUtils_->Logger_->Log(Message.c_str(), 7);
        return 0;
    }

    DecodedWavClip Clip;
    std::string DecodeError;
    if (!ERS_FUNCTION_DecodePCM16Or8Wav(AudioData.Data.get(), AudioData.Size_B, Clip, DecodeError)) {
        std::string Message = "Could not decode audio asset " + std::to_string(AssetID) + ": " + DecodeError;
        SystemUtils_->Logger_->Log(Message.c_str(), 7);
        return 0;
    }

    if (Clip.Samples.size() > static_cast<std::size_t>(std::numeric_limits<int>::max())) {
        std::string Message = "Audio asset " + std::to_string(AssetID) + " is too large for OpenAL buffer upload";
        SystemUtils_->Logger_->Log(Message.c_str(), 7);
        return 0;
    }

    unsigned int BufferID = 0;
    alGenBuffers(1, &BufferID);
    if (!LogOpenALError("alGenBuffers") || BufferID == 0) {
        return 0;
    }

    alBufferData(
        BufferID,
        Clip.Format,
        Clip.Samples.data(),
        static_cast<int>(Clip.Samples.size()),
        Clip.Frequency
    );
    if (!LogOpenALError("alBufferData")) {
        alDeleteBuffers(1, &BufferID);
        return 0;
    }

    ClipBuffers_[AssetID] = BufferID;
    return BufferID;
}

void ERS_CLASS_AudioPlaybackSystem::StartScenePlayback(ERS_STRUCT_Scene* Scene) {
    if (Scene == nullptr || !Initialize()) {
        return;
    }

    StopScenePlayback();

    for (unsigned long Index = 0; Index < Scene->AudioSources.size(); Index++) {
        ERS_STRUCT_AudioSource* AudioSource = Scene->AudioSources[Index].get();
        if (AudioSource == nullptr || !AudioSource->Autoplay || AudioSource->AudioAssetID < 0) {
            continue;
        }

        unsigned int BufferID = LoadClipBuffer(AudioSource->AudioAssetID);
        if (BufferID == 0) {
            continue;
        }

        unsigned int SourceID = 0;
        alGenSources(1, &SourceID);
        if (!LogOpenALError("alGenSources") || SourceID == 0) {
            continue;
        }

        alSourcei(SourceID, AL_BUFFER, static_cast<int>(BufferID));
        alSourcef(SourceID, AL_GAIN, std::max(0.0f, AudioSource->Gain));
        alSourcei(SourceID, AL_LOOPING, AudioSource->Looping ? AL_TRUE : AL_FALSE);
        alSourcef(SourceID, AL_REFERENCE_DISTANCE, 1.0f);
        alSourcef(SourceID, AL_MAX_DISTANCE, std::max(0.01f, AudioSource->MaxDistance));
        alSourcef(SourceID, AL_ROLLOFF_FACTOR, 1.0f);
        alSource3f(SourceID, AL_POSITION, AudioSource->Pos.x, AudioSource->Pos.y, AudioSource->Pos.z);
        alSourcePlay(SourceID);
        if (!LogOpenALError("alSourcePlay")) {
            alDeleteSources(1, &SourceID);
            continue;
        }

        ActiveSources_.push_back({Index, SourceID});
    }
}

void ERS_CLASS_AudioPlaybackSystem::StopScenePlayback() {
    for (ActiveAudioSource& Source : ActiveSources_) {
        if (Source.SourceID != 0) {
            alSourceStop(Source.SourceID);
            alDeleteSources(1, &Source.SourceID);
        }
    }
    ActiveSources_.clear();
}

void ERS_CLASS_AudioPlaybackSystem::Update(ERS_STRUCT_Scene* Scene, ERS_STRUCT_Camera* ListenerCamera) {
    if (!Available_ || Scene == nullptr || ListenerCamera == nullptr) {
        return;
    }

    glm::vec3 ListenerPosition = ListenerCamera->GetPosition();
    glm::vec3 ListenerRotation = ListenerCamera->GetRotation();
    glm::vec3 ListenerFront = ERS_FUNCTION_ConvertRotationToFrontVector(ListenerRotation);
    glm::vec3 ListenerUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float ListenerOrientation[] = {
        ListenerFront.x, ListenerFront.y, ListenerFront.z,
        ListenerUp.x, ListenerUp.y, ListenerUp.z
    };

    alListener3f(AL_POSITION, ListenerPosition.x, ListenerPosition.y, ListenerPosition.z);
    alListenerfv(AL_ORIENTATION, ListenerOrientation);

    std::vector<ActiveAudioSource> StillPlaying;
    StillPlaying.reserve(ActiveSources_.size());

    for (ActiveAudioSource& Source : ActiveSources_) {
        if (Source.AudioSourceIndex >= Scene->AudioSources.size()) {
            alSourceStop(Source.SourceID);
            alDeleteSources(1, &Source.SourceID);
            continue;
        }

        ERS_STRUCT_AudioSource* AudioSource = Scene->AudioSources[Source.AudioSourceIndex].get();
        if (AudioSource == nullptr) {
            alSourceStop(Source.SourceID);
            alDeleteSources(1, &Source.SourceID);
            continue;
        }

        alSource3f(Source.SourceID, AL_POSITION, AudioSource->Pos.x, AudioSource->Pos.y, AudioSource->Pos.z);
        alSourcef(Source.SourceID, AL_GAIN, std::max(0.0f, AudioSource->Gain));
        alSourcef(Source.SourceID, AL_MAX_DISTANCE, std::max(0.01f, AudioSource->MaxDistance));

        int State = AL_STOPPED;
        alGetSourcei(Source.SourceID, AL_SOURCE_STATE, &State);
        if (State == AL_PLAYING || State == AL_PAUSED || AudioSource->Looping) {
            StillPlaying.push_back(Source);
        } else {
            alDeleteSources(1, &Source.SourceID);
        }
    }

    ActiveSources_ = StillPlaying;
}

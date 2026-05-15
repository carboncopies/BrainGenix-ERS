//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// Forward declarations for OpenAL types. Keep OpenAL headers out of this public
// header so renderer users do not inherit platform audio headers.
struct ALCdevice_struct;
struct ALCcontext_struct;
using ALCdevice = ALCdevice_struct;
using ALCcontext = ALCcontext_struct;

// Internal Libraries (BG convention: use <> instead of "")
#include <Camera.h>
#include <Scene.h>
#include <SystemUtils.h>


class ERS_CLASS_AudioPlaybackSystem {

private:

    struct ActiveAudioSource {
        unsigned long AudioSourceIndex = 0;
        unsigned int SourceID = 0;
    };

    ERS_STRUCT_SystemUtils* SystemUtils_ = nullptr;

    ALCdevice* Device_ = nullptr;
    ALCcontext* Context_ = nullptr;

    bool InitializationAttempted_ = false;
    bool Available_ = false;

    std::unordered_map<long, unsigned int> ClipBuffers_;
    std::vector<ActiveAudioSource> ActiveSources_;

    bool Initialize();
    void Shutdown();
    void DeleteClipBuffers();

    unsigned int LoadClipBuffer(long AssetID);
    bool LogOpenALError(const std::string& Context);

public:

    explicit ERS_CLASS_AudioPlaybackSystem(ERS_STRUCT_SystemUtils* SystemUtils);
    ~ERS_CLASS_AudioPlaybackSystem();

    ERS_CLASS_AudioPlaybackSystem(const ERS_CLASS_AudioPlaybackSystem&) = delete;
    ERS_CLASS_AudioPlaybackSystem& operator=(const ERS_CLASS_AudioPlaybackSystem&) = delete;

    bool IsAvailable() const;

    void StartScenePlayback(ERS_STRUCT_Scene* Scene);
    void StopScenePlayback();
    void Update(ERS_STRUCT_Scene* Scene, ERS_STRUCT_Camera* ListenerCamera);

};

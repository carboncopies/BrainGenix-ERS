//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_ModelWriter.h>


ERS_CLASS_ModelWriter::ERS_CLASS_ModelWriter(ERS_CLASS_LoggingSystem* Logger, ERS_CLASS_InputOutputSubsystem* IOSubsystem) {

    Logger_ = Logger;
    IOSubsystem_ = IOSubsystem;
    Logger_->Log("Initializing ERS ModelWriter Subsystem", 5);

}
ERS_CLASS_ModelWriter::~ERS_CLASS_ModelWriter() {

    Logger_->Log("ModelWriter Subsystem Destructor Invoked", 5);

}


// Export Helpers
bool ERS_CLASS_ModelWriter::WriteModelGeometry(ERS_STRUCT_ModelWriterData &Data, std::string ExportFormat) {

    // Export Model File
    Logger_->Log(std::string("Exporting Model Geometry To Blob With Encoding '") + ExportFormat + "'", 4);

    Assimp::Exporter Exporter;
    const aiExportDataBlob* Blob = Exporter.ExportToBlob(Data.ModelScene, ExportFormat);

    std::string ExportStatus = Exporter.GetErrorString();
    if (ExportStatus == "") {
        Logger_->Log(std::string("Finished Exporting Model Geometry To Blob"), 3);
    } else {
        Logger_->Log(std::string("Error Exporting Model Geometry '") + ExportStatus + "'", 7);
        return false;
    }
    

    // Write Model Geo Data
    std::unique_ptr<ERS_STRUCT_IOData> IOData = std::make_unique<ERS_STRUCT_IOData>();
    IOData->Data.reset(new unsigned char[Blob->size]);
    ::memcpy(IOData->Data.get(), Blob->data, Blob->size);
    IOData->Size_B = Blob->size;

    long ModelID = IOSubsystem_->AllocateAssetID();
    Logger_->Log(std::string(std::string("Assigning ID '") + std::to_string(ModelID) + std::string("' To Model '") + Data.Model->Name + std::string("'")).c_str(), 4);
    IOSubsystem_->WriteAsset(ModelID, IOData.get());    


    // Update State, Finish
    Data.ModelAssetID = ModelID;
    return true;
}

void ERS_CLASS_ModelWriter::WriteTextures(ERS_STRUCT_Model* Model, std::vector<std::vector<int>>* TextureImageMemorySizes, std::vector<std::vector<long>>* TextureImageAssetIDs, std::vector<std::vector<std::pair<int, int>>>* TextureImageResolutions, std::vector<std::vector<int>>* TextureImageChannels, std::string AssetPath, FREE_IMAGE_FORMAT Format, int MipMaps) {

    // Create List Of Texture Files To Be Copied
    std::vector<std::pair<std::string, std::shared_ptr<ERS_STRUCT_IOData>>> TextureFiles;
    for (int i = 0; (long)i < (long)TextureList_.size(); i++) {

        std::shared_ptr<ERS_STRUCT_IOData> Data = std::make_shared<ERS_STRUCT_IOData>();
        std::string TexturePath = TextureList_[i];
        bool Success = ReadFile(TextureList_[i], Data.get());
        Data->AssetTypeName = "Texture";
        Data->AssetFileName = TextureList_[i].substr(AssetPath.find_last_of("/") + 1, AssetPath.size() - 1);
        Data->AssetCreationDate = SystemUtils_->ERS_IOSubsystem_->GetCurrentTime();


        bool SecondTryStatus = false;
        if (!Success) {
            SystemUtils_->Logger_->Log(std::string("Error Loading Texture From Given Path '") + AssetPath + std::string("', Will Search Current Directory For Texture"), 7);

            // Strip To Last Item In Path (With Forward Slashes And Backward Slashes)
            std::string Path = TextureList_[i];
            std::replace(Path.begin(), Path.end(), '\\', '/');
            if (Path.find("/") != std::string::npos) {
                Path = Path.substr(Path.find_last_of("/") + 1, Path.size()-1);
            }

            // Create Reference String To Be Tested Against
            std::string RefString = Path.substr(0, Path.find_first_of("."));
            size_t Pos = 0;
            while ((Pos = RefString.find(" ", Pos)) != std::string::npos) {
                RefString.replace(Pos, 1, "_");
                Pos ++;
            }

            // Check Against Filesystem
            std::replace(AssetPath.begin(), AssetPath.end(), '\\', '/');
            for (const auto &Entry : std::filesystem::recursive_directory_iterator(AssetPath.substr(0, AssetPath.find_last_of("/")))) {

                std::string FilePath{Entry.path().u8string()};
                std::replace(FilePath.begin(), FilePath.end(), '\\', '/');
                std::string FileName = FilePath.substr(FilePath.find_last_of('/') + 1, FilePath.size() - 1);
                std::string FileNameWithoutExtension = FileName.substr(0, FileName.find_first_of("."));

                // Remove Spaces From Filename And Replace With Underscores
                Pos = 0;
                while ((Pos = FileNameWithoutExtension.find(" ", Pos)) != std::string::npos) {
                    FileNameWithoutExtension.replace(Pos, 1, "_");
                    Pos ++;
                }


                if (FileNameWithoutExtension == RefString) {
                    Path = FilePath;
                    SystemUtils_->Logger_->Log(std::string("Found Potential Match '") + FilePath + std::string("', Attempting To Load"), 5);
                    break;
                }

            
            }


            SecondTryStatus = ReadFile(Path, Data.get());
            TexturePath = Path;
            
            if (!SecondTryStatus) {
                SystemUtils_->Logger_->Log("Failed To Find Texture During Second Try Effort, Abandoning Texture", 8);
            } else {
                SystemUtils_->Logger_->Log("Found Probable File, However This Is Not Guarenteed To Be Correct", 6);
            }

        }

        if (Success || SecondTryStatus) {
            TextureFiles.push_back(std::make_pair(TexturePath, Data));
        }

    }

    // Load Textures Into Memory
    std::vector<std::pair<std::string, FIBITMAP*>> ImageBytes;
    for (unsigned int i = 0; i < TextureFiles.size(); i++) {

        SystemUtils_->Logger_->Log(std::string("Loading Texture Image '")  + TextureFiles[i].first + "'", 4);
        
        ERS_STRUCT_IOData* ImageData = TextureFiles[i].second.get();
        FIMEMORY* FIImageData = FreeImage_OpenMemory(ImageData->Data.get(), ImageData->Size_B);
        FREE_IMAGE_FORMAT Format = FreeImage_GetFileTypeFromMemory(FIImageData);
        FIBITMAP* RawImage = FreeImage_LoadFromMemory(Format, FIImageData);
        FreeImage_CloseMemory(FIImageData);

        //FreeImage_FlipVertical(RawImage);

        FIBITMAP* Image = FreeImage_ConvertTo32Bits(RawImage);
        FreeImage_Unload(RawImage);

        SystemUtils_->Logger_->Log(std::string("Loaded Texture Image"), 3);


        ImageBytes.push_back(std::make_pair(TextureFiles[i].first, Image));
    }

    // Remove Duplicate Stuff (Like Alpha Maps), Just Generally Consolidate Stuff
    MergeTextures(Model, &ImageBytes);

    // Resize For Mipmaps, Save To New Project
    for (unsigned int i = 0; i < ImageBytes.size(); i++) {

        // Get Raw Source Texture Information
        FIBITMAP* Image = ImageBytes[i].second;
        int SourceImageWidth = FreeImage_GetWidth(Image);
        int SourceImageHeight = FreeImage_GetHeight(Image);

        // Generate List Of New Resolutions
        std::vector<std::pair<int, int>> Resolutions;
        int X = SourceImageWidth;
        int Y = SourceImageHeight;
        for (int MipMapIndex = MipMaps - 1; MipMapIndex >= 0; MipMapIndex--) {

            X = std::max(1, X);
            Y = std::max(1, Y);
            
            Resolutions.push_back(std::make_pair(X, Y));
            SystemUtils_->Logger_->Log(std::string("Calculating Texture Level '") + std::to_string(MipMapIndex) + "' Size '" + std::to_string(X) + "," + std::to_string(Y) + "'", 4);

            // Limit Sizes
            if (X > 1) {
                X /= 2;
            }
            if (Y > 1) {
                Y /= 2;
            }

        }

        // Resize Images
        std::vector<int> ImageMemorySizes;
        std::vector<long> ImageAssetIDs;
        std::vector<int> ImageChannels;
        for (int MipMapIndex = 0; MipMapIndex < MipMaps; MipMapIndex++) {

            // Resize Image
            int TargetX, TargetY;
            TargetX = Resolutions[MipMapIndex].first;
            TargetY = Resolutions[MipMapIndex].second;
            SystemUtils_->Logger_->Log(std::string("Resizing Texture Image To Size '") + std::to_string(TargetX) + "," + std::to_string(TargetY) + "'", 4);
            FIBITMAP* NewImage = FreeImage_Rescale(Image, TargetX, TargetY);

            // Swap Colors From RGB To BGR
            FIBITMAP* Red = FreeImage_GetChannel(NewImage, FICC_RED);
            FIBITMAP* Green = FreeImage_GetChannel(NewImage, FICC_GREEN);
            FIBITMAP* Blue = FreeImage_GetChannel(NewImage, FICC_BLUE);
            FIBITMAP* Alpha = FreeImage_GetChannel(NewImage, FICC_ALPHA);
            FreeImage_SetChannel(NewImage, Red, FICC_BLUE);
            FreeImage_SetChannel(NewImage, Green, FICC_GREEN);
            FreeImage_SetChannel(NewImage, Blue, FICC_RED);
            FreeImage_SetChannel(NewImage, Alpha, FICC_ALPHA);
            FreeImage_Unload(Red);
            FreeImage_Unload(Green);
            FreeImage_Unload(Blue);



            // Save Image
            long ImageAssetID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
            SystemUtils_->Logger_->Log(std::string("Writing Texture Image For Layer '")
            + std::to_string((MipMaps - 1) - MipMapIndex)
            + "' With ID '" + std::to_string(ImageAssetID)
            + "' For Asset Texture '" + TextureList_[i], 3);
            FIMEMORY* Memory = FreeImage_OpenMemory();
            FreeImage_SaveToMemory(Format, NewImage, Memory);
            FreeImage_Unload(NewImage);


            std::unique_ptr<ERS_STRUCT_IOData> Data = std::make_unique<ERS_STRUCT_IOData>();
            Data->AssetTypeName = "TextureImage";
            DWORD ImageCompressedSize = 0;
            BYTE *ImageCompressedBytes;
            FreeImage_AcquireMemory(Memory, &ImageCompressedBytes, &ImageCompressedSize);
            Data->Data.reset(new unsigned char[ImageCompressedSize]);
            ::memcpy(Data->Data.get(), ImageCompressedBytes, ImageCompressedSize);
            FreeImage_CloseMemory(Memory);
            Data->Size_B = ImageCompressedSize;
            Data->AssetCreationDate = SystemUtils_->ERS_IOSubsystem_->GetCurrentTime();
            Data->AssetModificationDate = SystemUtils_->ERS_IOSubsystem_->GetCurrentTime();
            bool WriteSuccess = SystemUtils_->ERS_IOSubsystem_->WriteAsset(ImageAssetID, Data.get());

            if (!WriteSuccess) {
                SystemUtils_->Logger_->Log("Error Writing Texture File", 8);
                ImageChannels.push_back(0);
                ImageChannels.push_back(0);
                ImageMemorySizes.push_back(0);
                ImageAssetIDs.push_back(-1);

            } else {

                // Test Re-Loading Image And Confirm it's all good
                SystemUtils_->Logger_->Log(std::string("Testing Texture Image For Layer '")
                + std::to_string((MipMaps - 1) - MipMapIndex)
                + "' With ID '" + std::to_string(ImageAssetID)
                + "' For Asset Texture '" + TextureList_[i], 3);
                bool ReadSuccess = SystemUtils_->ERS_IOSubsystem_->ReadAsset(ImageAssetID, Data.get());

                if (ReadSuccess) {
                    FIMEMORY* FIImageData = FreeImage_OpenMemory(Data->Data.get(), Data->Size_B);
                    FREE_IMAGE_FORMAT Format = FreeImage_GetFileTypeFromMemory(FIImageData);
                    FIBITMAP* TestImage = FreeImage_LoadFromMemory(Format, FIImageData);
                    FreeImage_CloseMemory(FIImageData);
                    FreeImage_FlipVertical(TestImage);

                    // Detect Channels
                    int Line = FreeImage_GetLine(TestImage);
                    int Width = FreeImage_GetWidth(TestImage);
                    if (Width == 0 || Line == 0) {
                        ImageChannels.push_back(0);
                    } else {
                        ImageChannels.push_back(Line / Width);
                    }
                    SystemUtils_->Logger_->Log(std::string("Detected Number Of Channels To Be '")
                    + std::to_string(Line/Width) + "' For " + TextureList_[i], 3);

                    // Get Metadata Info
                    int MemorySize = FreeImage_GetMemorySize(TestImage);
                    ImageMemorySizes.push_back(MemorySize);
                    ImageAssetIDs.push_back(ImageAssetID);
                    SystemUtils_->Logger_->Log(std::string("Generating Texture Image Metadata,  Size Is '") + std::to_string(MemorySize) + "' Bytes, ID Is '" + std::to_string(ImageAssetID) + "'", 3);

                    FreeImage_Unload(TestImage);


                } else {
                    SystemUtils_->Logger_->Log("Error Reading Image Asset Data", 8);
                    ImageChannels.push_back(0);
                    ImageMemorySizes.push_back(0);
                    ImageAssetIDs.push_back(-1);
                }

            }


        }
        FreeImage_Unload(Image);

        // Add To Output Vectors
        TextureImageMemorySizes->push_back(ImageMemorySizes);
        TextureImageAssetIDs->push_back(ImageAssetIDs);
        TextureImageResolutions->push_back(Resolutions);
        TextureImageChannels->push_back(ImageChannels);

    }

}


std::string ERS_CLASS_ModelWriter::GenerateModelMetadata(ERS_STRUCT_Model* Model) {

    // Create Model Metadata, Begin Writing
    YAML::Emitter Metadata;
    Metadata << YAML::BeginMap;

    // Set Constant Info
    Metadata << YAML::Key << "Type" << YAML::Value << "ModelDescriptor";
    Metadata << YAML::Key << "FormatVersion" << YAML::Value << "0.0.1";

    // Stop Writing, Return Metadata
    Metadata << YAML::EndMap;
    return std::string(Metadata.c_str());

}

void ERS_CLASS_ModelWriter::WriteModel(ERS_STRUCT_ModelWriterData &Data) {

    // Setup Vars
    std::vector<std::vector<int>> TextureMemorySizes;
    std::vector<std::vector<long>> ImageAssetIDs;
    std::vector<std::vector<std::pair<int, int>>> ImageResolutions;
    std::vector<std::vector<int>> ImageChannels;

    // Write
    WriteModelGeometry(Data);
    WriteTextures(Data.Model, &TextureMemorySizes, &ImageAssetIDs, &ImageResolutions, &ImageChannels, Data.ModelOriginDirectoryPath);


}



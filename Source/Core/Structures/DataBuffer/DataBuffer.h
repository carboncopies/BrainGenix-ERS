//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing in-memory storage of all loaded assets.
    Additonal Notes: None
    Date Created: 2021-11-12
*/   

#pragma once


#include <vector>
#include <variant>
#include <string>

#include <LoggingSystem.h>


#include <Scene.h>
#include "Model.h"
#include "ImageDecoder.h"


struct ERS_STRUCTURE_DATA_BUFFER {

    // Create Internal Structures
    struct VectorData {

        std::string AssetType; // Stores Type Of Object, EG: "ERS_OBJECT_MODEL" or "ERS_OBJECT_SCENE"
        std::string AssetPath; // Optional string that contains info about the "path"
        long VectorIndex; // Stores Position In Given Vector

    };

    // Internal Vars
    LoggerClass *Logger_ = nullptr;

    // Create Buffers
    std::map<long, VectorData> MetadataMap_;
    std::vector<ERS_OBJECT_MODEL> ERS_OBJECT_MODEL_Vector_;
    std::vector<ERS_OBJECT_SCENE> ERS_OBJECT_SCENE_Vector_;
    std::vector<ERSImage> ERS_OBJECT_IMAGE_Vector_;
    int TestVar = 5;

    // Return Number Of Elements In Model Vector
    long GetNumberObjectModels() {
        return ERS_OBJECT_MODEL_Vector_.size();
    }

    // Return An Image Stored In The Image Vector With A Matching Path
    ERSImage* GetImage(const char* Path) {

        // Get Map Length
        long MapLength = (long)MetadataMap_.size();

        // Iterate Through Map
        for (long i = 0; i < MapLength; i++) {

            // Get Map Element
            VectorData MapElement = MetadataMap_[i];

            // Check Type
            if (MapElement.AssetType == std::string("ERS_OBJECT_IMAGE")) {
                if (MapElement.AssetPath == std::string(Path)) {
                    
                    // Get Vector Index
                    long VectorIndex = MapElement.VectorIndex;

                    // Return Element
                    return &ERS_OBJECT_IMAGE_Vector_[VectorIndex];

                }
            }


        }

        // No Image Found
        return nullptr;

    }



    // Initialize Buffer
    void Init( LoggerClass *Logger) {

        // Copy Pointer To The Logger
        Logger_ = Logger;

        // Log System Initialization
        Logger_->Log("Initialized ERS Data Buffer", 6);

    }

    // Add Types To Buffer
    void Add_ERS_OBJECT_MODEL(ERS_OBJECT_MODEL Input, long AssetID) {

        // Add Model To Buffer
        ERS_OBJECT_MODEL_Vector_.push_back(Input);

        VectorData AssetData;
        AssetData.AssetType = "ERS_OBJECT_MODEL";
        AssetData.VectorIndex = (long)ERS_OBJECT_MODEL_Vector_.size()-1;

        MetadataMap_.insert({AssetID, AssetData});

        // Log Model Loading
        if (Logger_ != nullptr) {
            Logger_->Log(std::string(std::string("Adding ERS_OBJECT_MODEL Asset To Data Buffer With Global Asset ID: ") + std::to_string(AssetID)).c_str(), 4);
        }

    }

    void Add_ERS_OBJECT_SCENE(ERS_OBJECT_SCENE Input, long AssetID) {

        // Add Scene To Buffer
        ERS_OBJECT_SCENE_Vector_.push_back(Input);

        VectorData AssetData;
        AssetData.AssetType = "ERS_OBJECT_SCENE";
        AssetData.VectorIndex = (long)ERS_OBJECT_SCENE_Vector_.size()-1;

        MetadataMap_.insert({AssetID, AssetData});

        // Log Scene Loading
        if (Logger_ != nullptr) {
            Logger_->Log(std::string(std::string("Adding ERS_OBJECT_SCENE Asset To Data Buffer With Global Asset ID: ") + std::to_string(AssetID)).c_str(), 4);
        }

    }

    void Add_ERS_OBJECT_IMAGE(ERSImage Input, long AssetID, std::string AssetPath) {

        // Add Image To Buffer
        ERS_OBJECT_IMAGE_Vector_.push_back(Input);

        VectorData AssetData;
        AssetData.AssetType = "ERS_OBJECT_IMAGE";
        AssetData.VectorIndex = (long)ERS_OBJECT_IMAGE_Vector_.size()-1;
        AssetData.AssetPath = AssetPath;

        MetadataMap_.insert({AssetID, AssetData});

        // Log Scene Loading
        if (Logger_ != nullptr) {
            Logger_->Log(std::string(std::string("Adding ERS_OBJECT_IMAGE Asset To Data Buffer With Global Asset ID: ") + std::to_string(AssetID)).c_str(), 4);
        }

    }


};


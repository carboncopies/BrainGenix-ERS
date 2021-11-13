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

#include "Core/Management/LoggingSystem.h"

#include "Core/Structures/Scene/Scene.h"
#include "Core/Structures/Model/Model.h"




struct ERS_STRUCTURE_DATA_BUFFER {

    // Create Internal Structures
    struct VectorData {

        std::string AssetType; // Stores Type Of Object, EG: "ERS_OBJECT_MODEL" or "ERS_OBJECT_SCENE"
        long VectorIndex; // Stores Position In Given Vector

    };

    // Internal Vars
    LoggerClass *Logger_ = nullptr;
    bool LoggerInitialized_ = false;

    // Create Buffers
    std::map<long, VectorData> MetadataMap_;
    std::vector<ERS_OBJECT_MODEL> ERS_OBJECT_MODEL_Vector_;
    std::vector<ERS_OBJECT_SCENE> ERS_OBJECT_MODEL_Vector_;



    // Initialize Buffer
    void Init( LoggerClass *Logger) {

        // Copy Pointer To The Logger
        Logger_ = Logger;
        LoggerInitialized_ = true;

        // Log System Initialization
        Logger_->Log("Initialized ERS Data Buffer", 6);

    }

    // Add Types To Buffer
    bool Add_ERS_OBJECT_MODEL(ERS_OBJECT_MODEL Input, long AssetID) {

        // Add Model To Buffer
        ERS_OBJECT_MODEL_Vector_.push_back(Input);
        MetadataMap_.insert()


    }

    // // Add To Data Buffer
    // void AddToBuffer(auto Input, long ID) {

    //     // If Logger Enabled, Log Entry To Buffer
    //     if (Logger_ != nullptr) {
    //         Logger_->Log(std::string(std::string("Adding Asset To Data Buffer With Index: ") + std::to_string(ID)).c_str(), 7);
    //     }


    //     /*
    //     TODO: HAVE THE SYSTEM CHECK THE TYPE AND PICK THE INDEX OF THAT TYPES VECTOR, THEN APPEND TO VECTOR WITH THAT INDEX.
    //     */

    //     StructureBuffer.push_back(Input);
    //     IndexMap.insert({ID, (long)StructureBuffer.size()-1});

    // }

    // // Get Data From Buffer
    // auto* PullFromBuffer(long ID) {

    //     /*
    //     TODO: PULL FROM BUFFER WITH TYPE INDEX, USE std::get<TYPEINDEX> TO GET ANY TYPE.
    //     */

    //     // Get Data From Buffer
    //     long VectorIndex = IndexMap[ID];
    //     return &std::get<long>(StructureBuffer[VectorIndex]);

    // }


};


//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the model writer class.
    Documentation Status: Completed
    Additonal Notes: None
    Date Created: 2021-11-22
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <Model.h>
#include <ModelLoader.h>
#include <Scene.h>
#include <Mesh.h>
#include <2DTexture.h>

#include <Shader.h>

#include <ERS_InputOutputSubsystem.h>


// This Class Encodes Models In The ERS Format (Modified GLTF)
class ERS_CLASS_ModelWriter {

    // Member Vars
    private:

        std::shared_ptr<LoggerClass> Logger_; /**<Pointer To Logger Instance*/
        std::shared_ptr<ERS_CLASS_InputOutputSubsystem> IOSubsystem_; /**<Pointer To IOSubsystem*/

    // Member Functions
    private:

        /**
         * @brief Generate YAML metadata from the model object.
         * 
         * @param Model 
         * @return YAML::Node 
         */
        std::string GenerateModelMetadata(std::shared_ptr<ERS_OBJECT_MODEL> Model);



    // Public Member Vars
    public:

    // Public Member Functions
    public:

        /**
         * @brief Construct a new ers class modelwriter object
         * 
         * @param Logger 
         */
        ERS_CLASS_ModelWriter(std::shared_ptr<LoggerClass> Logger, std::shared_ptr<ERS_CLASS_InputOutputSubsystem> IOSubsystem);
        
        /**
         * @brief Destroy the ers class modelwriter object
         * 
         */
        ~ERS_CLASS_ModelWriter();


        /**
         * 
         * @brief Write a batch of models to storage in the ERS format
         * 
         * @param Models 
         */
        void BatchWriteModels(std::vector<std::shared_ptr<ERS_OBJECT_MODEL>> Models);

        /**
         * @brief Write a single model to storage. Single Threaded.
         * 
         * @param Model 
         */
        void WriteModel(std::shared_ptr<ERS_OBJECT_MODEL> Model);

};
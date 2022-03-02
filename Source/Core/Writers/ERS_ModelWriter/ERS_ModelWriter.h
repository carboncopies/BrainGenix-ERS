//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>
#include <ERS_STRUCT_Model.h>
#include <ERS_STRUCT_Scene.h>
#include <ERS_STRUCT_Mesh.h>
#include <ERS_STRUCT_Texture.h>

#include <ERS_InputOutputSubsystem.h>


/**
 * @brief This Class Encodes Models In The ERS Format (Modified GLTF)
 * 
 */
class ERS_CLASS_ModelWriter {

private:

    ERS_CLASS_LoggingSystem* Logger_; /**<Pointer To Logger Instance*/
    std::shared_ptr<ERS_CLASS_InputOutputSubsystem> IOSubsystem_; /**<Pointer To IOSubsystem*/

private:

    /**
     * @brief Generate YAML metadata from the model object.
     * 
     * @param Model 
     * @return YAML::Node 
     */
    std::string GenerateModelMetadata(std::shared_ptr<ERS_STRUCT_Model> Model);



public:

    /**
     * @brief Construct a new ers class modelwriter object
     * 
     * @param Logger 
     */
    ERS_CLASS_ModelWriter(ERS_CLASS_LoggingSystem* Logger, std::shared_ptr<ERS_CLASS_InputOutputSubsystem> IOSubsystem);
    
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
    void BatchWriteModels(std::vector<std::shared_ptr<ERS_STRUCT_Model>> Models);

    /**
     * @brief Copy A Model To Insternal Storage, Does Not Re-encode model in proper format. Single Threaded.
     * 
     * @param InputData 
     * @param Model 
     * @param OverwriteExisting 
     */
    void WriteModel(std::shared_ptr<ERS_STRUCT_IOData> InputData, std::vector<std::shared_ptr<ERS_STRUCT_IOData>> TextureData, std::shared_ptr<ERS_STRUCT_Model> Model);

};
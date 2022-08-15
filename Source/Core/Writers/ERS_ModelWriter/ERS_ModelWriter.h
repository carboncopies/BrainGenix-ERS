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
    ERS_CLASS_InputOutputSubsystem* IOSubsystem_; /**<Pointer To IOSubsystem*/

private:

    /**
     * @brief Generate YAML metadata from the model object.
     * 
     * @param Model 
     * @return YAML::Node 
     */
    std::string GenerateModelMetadata();


    /**
     * @brief Decodes and writes resized textures into the ERS project file.
     * 
     * @param Model
     * @param TextureMemorySizes 
     * @param ImageAssetIDs 
     * @param ImageResolutions 
     * @param ImageChannels
     * @param AssetPath 
     * @param Format 
     * @param MipMaps 
     */
    void WriteTextures(ERS_STRUCT_Model* Model, std::vector<std::vector<int>>* TextureMemorySizes, std::vector<std::vector<long>>* ImageAssetIDs, std::vector<std::vector<std::pair<int, int>>>* ImageResolutions, std::vector<std::vector<int>>* ImageChannels, std::string AssetPath, FREE_IMAGE_FORMAT Format = FIF_PNG, int MipMaps = 10);

    /**
     * @brief Calculates the bounding box of the model and it's offset
     * 
     * @param Model
     */
    void DetectBoundingBox(ERS_STRUCT_Model* Model);

    /**
     * @brief Sets metadata parameters for number of vertices and indices in the model
     * 
     * @param Model 
     */
    void CalculateTotalVertsIndices(ERS_STRUCT_Model* Model);

    /**
     * @brief Here, we reduce the number of textures or convert into the expected ERS system
     * For example, alpha maps are baked into the diffuse map.
     * 
     * @param Model 
     */
    void MergeTextures(ERS_STRUCT_Model* Model, std::vector<std::pair<std::string, FIBITMAP*>>* LoadedTextures);

public:

    /**
     * @brief Construct a new ers class modelwriter object
     * 
     * @param Logger 
     */
    ERS_CLASS_ModelWriter(ERS_CLASS_LoggingSystem* Logger, ERS_CLASS_InputOutputSubsystem* IOSubsystem);
    
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
    void WriteModel(ERS_STRUCT_IOData* InputData, std::vector<ERS_STRUCT_IOData*> TextureData, std::shared_ptr<ERS_STRUCT_Model> Model);

    /**
     * @brief Write a model to disk.
     * 
     * @param Model 
     */
    void WriteModel2(ERS_STRUCT_Model &Model);

};
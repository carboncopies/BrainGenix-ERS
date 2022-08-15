//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Exporter.hpp>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>

#include <ERS_STRUCT_Model.h>
#include <ERS_STRUCT_Scene.h>
#include <ERS_STRUCT_Mesh.h>
#include <ERS_STRUCT_Texture.h>
#include <ERS_STRUCT_ModelWriterData.h>

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
    std::string GenerateModelMetadata(ERS_STRUCT_Model* Model);


    /**
     * @brief Decodes and writes resized textures into the ERS project file.
     * 
     * @param Data
     * @param TextureMemorySizes 
     * @param ImageAssetIDs 
     * @param ImageResolutions 
     * @param ImageChannels
     * @param AssetPath 
     * @param Format 
     * @param MipMaps 
     */
    void WriteTextures(ERS_STRUCT_ModelWriterData &Data, std::vector<std::vector<int>>* TextureMemorySizes, std::vector<std::vector<long>>* ImageAssetIDs, std::vector<std::vector<std::pair<int, int>>>* ImageResolutions, std::vector<std::vector<int>>* ImageChannels, std::string AssetPath, FREE_IMAGE_FORMAT Format = FIF_PNG, int MipMaps = 10);

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

    /**
     * @brief Writes the model's geometry data into a binary blob for later decoding.
     * Returns true on success, false on failure.
     * 
     * @param Data Pointer to ModelWriterData struct whose data is to be saved
     * @param FormatName Name of the format to be exported. If the format specified is unsupported, we'll default to fbx.
     * @return true 
     * @return false 
     */
    bool WriteModelGeometry(ERS_STRUCT_ModelWriterData &Data, std::string FormatName = "fbx");

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
     * @brief Write a model to disk.
     * 
     * @param ModelWriterData
     */
    void WriteModel(ERS_STRUCT_ModelWriterData &Data);

};
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_ModelLoader.h>

#include <ERS_CLASS_LoggingSystem.h>

#include <ERS_STRUCT_Model.h>
#include <ERS_STRUCT_Scene.h>
#include <ERS_STRUCT_Mesh.h>
#include <ERS_STRUCT_Texture.h>
#include <ERS_STRUCT_Shader.h>
#include <ERS_STRUCT_Light.h>

/**
 * @brief The ERS_CLASS_SceneLoader Class Is responsible for loading scene files and associated models/textures.
 * 
 */
class ERS_CLASS_SceneLoader{

private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<System Utils Structure*/
    std::shared_ptr<ERS_CLASS_ModelLoader> ModelLoader_; /**<Contians A ModelLoader Class Pointer*/

    // Templates
    std::map<std::string, ERS_STRUCT_Model> TemplateModels_; /**<Template Map Used to Store Models In Original LocRotScale*/


private:

    /**
     * @brief Populate The Scene Structure, Fill In Vectors, etc. Should Be Called Before Sending Scene Struct To SceneManager.
     * 
     * @param RawSceneData 
     * @return ERS_STRUCT_Scene 
     */
    ERS_STRUCT_Scene ProcessScene(YAML::Node RawSceneData, long AssetID);


public:

    /**
     * @brief Construct a new Scene Loader object
     * 
     * @param Logger 
     */
    ERS_CLASS_SceneLoader(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_CLASS_ModelLoader> ModelLoader);

    /**
     * @brief Destroy the Scene Loader object
     * 
     */
    ~ERS_CLASS_SceneLoader();




    /**
     * @brief Populate The Scene Structure, Fill In Vectors, etc. Should Be Called Before Sending Scene Struct To SceneManager.
     * 
     * @param FileData
     * @return ERS_STRUCT_Scene 
     */
    ERS_STRUCT_Scene ProcessScene(long AssetID);


    /**
     * @brief Adds a model with the given id to the scene pointer passed in.
     * 
     * @param Scene 
     * @param AssetID 
     */
    void AddModel(std::shared_ptr<ERS_STRUCT_Scene> Scene, long AssetID);



};
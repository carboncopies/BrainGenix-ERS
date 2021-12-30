//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the scene loader class.
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
#include <ERS_ModelLoader.h>
#include <Scene.h>
#include <Mesh.h>
#include <2DTexture.h>


#include <Shader.h>


/**
 * @brief The ERS_CLASS_SceneLoader Class Is responsible for loading scene files and associated models/textures.
 * 
 */
class ERS_CLASS_SceneLoader{

private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<System Utils Structure*/
    std::shared_ptr<ERS_CLASS_ModelLoader> ModelLoader_; /**<Contians A ModelLoader Class Pointer*/

    // Templates
    std::map<std::string, ERS_OBJECT_MODEL> TemplateModels_; /**<Template Map Used to Store Models In Original LocRotScale*/


private:

    /**
     * @brief Populate The Scene Structure, Fill In Vectors, etc. Should Be Called Before Sending Scene Struct To SceneManager.
     * 
     * @param RawSceneData 
     * @return ERS_OBJECT_SCENE 
     */
    ERS_OBJECT_SCENE ProcessScene(YAML::Node RawSceneData, long AssetID);


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
     * @return ERS_OBJECT_SCENE 
     */
    ERS_OBJECT_SCENE ProcessScene(long AssetID);


};
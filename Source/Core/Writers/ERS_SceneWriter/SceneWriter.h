//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <BG/Common/Logger/Logger.h>
#include <Model.h>
#include <Scene.h>
#include <Mesh.h>
#include <Texture.h>

#include <IOData.h>
#include <SystemUtils.h>



/**
 * @brief The SceneWriter Class Is responsible for writing scene files.
 * 
 */
class SceneWriter{


private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<Contains System Utils Instance*/


public:

    /**
     * @brief Construct a new Scene Writer object
     * 
     * @param SystemUtils
     */
    SceneWriter(ERS_STRUCT_SystemUtils* SystemUtils);

    /**
     * @brief Destroy the Scene Writer object
     * 
     */
    ~SceneWriter();


    /**
     * @brief Save the scene passed in as a yaml::node.
     * 
     * @return std::string 
     */
    std::string ProcessScene(ERS_STRUCT_Scene* Scene);

    /**
     * @brief Save the scene passed in as a yaml::node.
     * 
     * @param FilePath 
     */
    void ProcessScene(ERS_STRUCT_Scene*, long SceneID);


};
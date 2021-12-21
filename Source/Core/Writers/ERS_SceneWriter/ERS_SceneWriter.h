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
#include <ModelLoader.h>
#include <Scene.h>
#include <Mesh.h>
#include <2DTexture.h>


#include <Shader.h>


/**
 * @brief The SceneWriter Class Is responsible for writing scene files.
 * 
 */
class SceneWriter{

    private:

        std::shared_ptr<LoggerClass> Logger_; /**<Contains A SceneWriter Class Instance*/


    public:
    
        /**
         * @brief Construct a new Scene Writer object
         * 
         * @param Logger 
         */
        SceneWriter(std::shared_ptr<LoggerClass> Logger);

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
        std::string ProcessScene(std::shared_ptr<ERS_OBJECT_SCENE> Scene);

        /**
         * @brief Save the scene passed in as a yaml::node.
         * 
         * @param FilePath 
         */
        void ProcessScene(std::shared_ptr<ERS_OBJECT_SCENE>, const char* FilePath);


};
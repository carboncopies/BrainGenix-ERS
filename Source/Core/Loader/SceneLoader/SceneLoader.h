//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the scene loader class.
    Documentation Status: Done
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


#include <Shader.h>


/**
 * @brief The Sceneloader Class Is responsible for loading scene files and associated models/textures.
 * 
 */
class SceneLoader{

    private:

        LoggerClass *Logger_; /**<Contains A SceneLoader Class Instance*/
        ModelLoader *ModelLoader_; /**<Contians A ModelLoader Class Pointer*/


    public:
    
        /**
         * @brief Construct a new Scene Loader object
         * 
         * @param Logger 
         */
        SceneLoader(LoggerClass *Logger, ModelLoader *ModelLoader);

        /**
         * @brief Destroy the Scene Loader object
         * 
         */
        ~SceneLoader();


        /**
         * @brief Populate The Scene Structure, Fill In Vectors, etc. Should Be Called Before Sending Scene Struct To ModelLoader.
         * 
         * @param RawSceneData 
         */
        void ProcessScene(YAML::Node RawSceneData);


};
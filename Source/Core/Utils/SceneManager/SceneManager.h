//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the scene manager classes.
    Documentation Status: Done
    Additonal Notes: None
    Date Created: 2021-11-21
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <ShaderManager.h>
#include <Scene.h>


/**
 * @brief The SceneManager Class Handles the Presentation and Rendering of BrainGenix ERS Scene Structures.
 * 
 */
class SceneManager{

    private:

        // Internal Member Pointers
        LoggerClass *Logger_; /**<Pointer To Logger Instance*/

        std::vector<ERS_OBJECT_SCENE> Scenes_; /**<Vector Containing Scenes To Be Drawn*/
        int ActiveScene_ = 0; /**<Set The Active Scene */

    public:

        /**
         * @brief Construct a new Scene Manager object
         * 
         * @param Logger 
         */
        SceneManager(LoggerClass *Logger);
        
        /**
         * @brief Destroy the Scene Manager object
         * 
         */
        ~SceneManager();


        /**
         * @brief Set the active scene. (Overloaded) [This Version Takes The Scene Index]. Returns True/False For Success/Fail
         * 
         * @param SceneIndex
         * @return true 
         * @return false 
         */
        bool SetActiveScene(int SceneIndex);

        /**
         * @brief Set the active scene. (Overloaded) [This Version Takes The Scene Name]. Returns True/False For Success/Fail
         * 
         * @param TargetSceneName 
         * @return true 
         * @return false 
         */
        bool SetActiveScene(std::string TargetSceneName);


        /**
         * @brief Add a populated scene structure to the scenes vector.
         * 
         * @param Scene 
         * @return true 
         * @return false
         */
        bool AddScene(ERS_OBJECT_SCENE Scene);

        /**
         * @brief Render scene set to active.
         * 
         * @param Shader 
         */
        void Render(ERS_OBJECT_SHADER* Shader);

};
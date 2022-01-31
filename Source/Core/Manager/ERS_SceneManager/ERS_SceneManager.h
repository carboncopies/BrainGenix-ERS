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
#include <glm/glm.hpp>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>
#include <ERS_STRUCT_Shader.h>
#include <Scene.h>
#include <ERS_STRUCT_LocRotScale.h>


/**
 * @brief The ERS_CLASS_SceneManager Class Handles the Presentation and Rendering of BrainGenix ERS Scene Structures.
 * 
 */
class ERS_CLASS_SceneManager{

    private:

        // Internal Member Pointers
        std::shared_ptr<ERS_CLASS_LoggingSystem> Logger_; /**<Pointer To Logger Instance*/


    public:

        std::vector<std::shared_ptr<ERS_OBJECT_SCENE>> Scenes_; /**<Vector Containing Scenes To Be Drawn*/
        int ActiveScene_ = 0; /**<Set The Active Scene */

    public:

        /**
         * @brief Construct a new Scene Manager object
         * 
         * @param Logger 
         */
        ERS_CLASS_SceneManager(std::shared_ptr<ERS_CLASS_LoggingSystem> Logger);
        
        /**
         * @brief Destroy the Scene Manager object
         * 
         */
        ~ERS_CLASS_SceneManager();


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
        void Render(std::shared_ptr<ERS_STRUCT_Shader> Shader);

        /**
         * @brief Send LocRotScale Update To Object(s) In Active Scene
         * 
         * @param LocRotScale 
         */
        void UpdateLocRotScale(glm::vec3 Pos, glm::vec3 Rot, glm::vec3 Scale);
        

};
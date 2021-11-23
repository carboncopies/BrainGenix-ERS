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



class SceneManager{

    private:

        // Internal Member Pointers
        LoggerClass *Logger_; /**<Pointer To Logger Instance*/

        //std::vector<ERS_OBJECT_> Models_; /**<Vector Containing Models To be Iterated Through When Drawn*/
        ERS_OBJECT_SCENE Scene_; // TEMPORARY, EVENTUALLY SWITCH TO SCENE VECTOR WITH ONE SCENE ACTIVE AT A TIME OR SOMETHING.

    public:


        SceneManager(LoggerClass *Logger);
        

        ~SceneManager();


        void AddScene(ERS_OBJECT_SCENE Scene);


        void Render(ERS_OBJECT_SHADER Shader);

};
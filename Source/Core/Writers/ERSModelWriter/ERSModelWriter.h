//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the model writer class.
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


// This Class Encodes Models In The ERS Format (Modified GLTF)
class ERS_CLASS_ModelWriter {

    // Member Vars
    private:

        std::shared_ptr<LoggerClass> Logger_; /**<Pointer To Logger Instance*/

    // Member Functions
    private:

    // Public Member Vars
    public:

    // Public Member Functions
    public:

        /**
         * @brief Construct a new ers class modelwriter object
         * 
         * @param Logger 
         */
        ERS_CLASS_ModelWriter(std::shared_ptr<LoggerClass> Logger);
        
        /**
         * @brief Destroy the ers class modelwriter object
         * 
         */
        ~ERS_CLASS_ModelWriter();

};
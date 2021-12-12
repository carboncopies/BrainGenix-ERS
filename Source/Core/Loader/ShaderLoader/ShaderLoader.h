//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the shader loader class.
    Documentation Status: Completed
    Additonal Notes: None
    Date Created: 2021-11-27
*/

#pragma once


// Standard Library (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <Shader.h>
#include <LoggingSystem.h>



/**
 * @brief The Shader Loader Is Responsible For Populating Shader Structs.
 * 
 */
class ShaderLoader {

    private:

        std::shared_ptr<LoggerClass> Logger_; /**<Pointer To Instance Of Logging System*/


    public:

        /**
         * @brief Construct a new Shader Loader object
         * 
         * @param Logger 
         */
        ShaderLoader(std::shared_ptr<LoggerClass> Logger);

        /**
         * @brief Destroy the Shader Loader object
         * 
         */
        ~ShaderLoader();
        

        /**
         * @brief Create a Shader Object object
         * 
         * @param VertexText 
         * @param FragmentText 
         * @return ERS_OBJECT_SHADER 
         */
        ERS_OBJECT_SHADER CreateShaderObject(const char* VertexText, const char* FragmentText);


        /**
         * @brief 
         * 
         * @param VertexPath 
         * @param FragmentPath 
         * @return ERS_OBJECT_SHADER 
         */
        ERS_OBJECT_SHADER LoadShaderFromFile(const char* VertexPath, const char* FragmentPath);



};
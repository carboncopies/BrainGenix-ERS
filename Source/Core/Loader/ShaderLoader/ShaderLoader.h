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


/**
 * @brief The Shader Loader Is Responsible For Populating Shader Structs.
 * 
 */
class ShaderLoader {

    private:



    public:


        
    ERS_OBJECT_SHADER CreateShaderObject(const char* VertexText, const char* FragmentText, LoggerClass *Logger_);

    ERS_OBJECT_SHADER LoadShaderFromFile(const char* VertexPath, const char* FragmentPath, LoggerClass *Logger_);



};
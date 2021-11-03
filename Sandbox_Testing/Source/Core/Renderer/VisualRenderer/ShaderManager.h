//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the shader compiler.
    Additonal Notes: None
    Date Created: 2021-11-02
*/

#pragma once

// Structure To Hold Shader Ids
struct ShaderObject{

    unsigned int VertexShader;
    unsigned int FragmentShader;

};


unsigned int VertexShaderCompiler(const char* VertexText, LoggerClass *Logger_);

unsigned int FragmentShaderCompiler(const char* FragmentText, LoggerClass *Logger_);

ShaderObject CreateShaderObject(const char* VertexText, const char* FragmentText, LoggerClass *Logger_);


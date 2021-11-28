//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the shader compiler.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-02
*/



#include "ShaderManager.h"



ERS_OBJECT_SHADER::ERS_OBJECT_SHADER(const char* VertexText, const char* FragmentText, LoggerClass *Logger_) {

    // Log Shader Creation
    Logger_->Log("Creating Shader Object", 5);

    // Create Shader
    CompileVertexShader(VertexText);
    CompileFragmentShader(FragmentText);

    // Attach Shaders
    Logger_->Log("Linking Shader Program", 5);
    CreateShaderProgram();
    Logger_->Log("Linked Shader Program", 4);


}

ERS_OBJECT_SHADER::ERS_OBJECT_SHADER(const char* VertexPath, const char* FragmentPath, LoggerClass *Logger_) {

    // Load Shaders From Disk Into RAM
    Logger_->Log("Loading Shaders From Disk", 5);
    std::string VertexText = ReadFile(VertexPath, Logger_);
    std::string FragmentText = ReadFile(FragmentPath, Logger_);

    
    // Log Shader Creation
    Logger_->Log("Creating Shader Object", 5);

    // Create Shader
    CompileVertexShader(VertexText.c_str());
    CompileFragmentShader(FragmentText.c_str());

    // Attach Shaders
    Logger_->Log("Linking Shader Program", 5);
    CreateShaderProgram();
    Logger_->Log("Linked Shader Program", 4);


}
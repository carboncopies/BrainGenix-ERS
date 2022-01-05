//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the shader loader class.
    Documentation Status: Completed
    Additonal Notes: None
    Date Created: 2021-11-27
*/

#include <ShaderLoader.h>


// ShaderLoader Constructor
ShaderLoader::ShaderLoader(std::shared_ptr<LoggerClass> Logger) {

    // Copy Member Pointers
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Shader Loader", 5);

}

// ShaderLoader Destructor
ShaderLoader::~ShaderLoader() {

    // Log Destructor Call
    Logger_->Log("Shader Loader Destructor Called", 6);

}

// Load Shader From Memory
ERS_OBJECT_SHADER ShaderLoader::CreateShaderObject(const char* VertexText, const char* FragmentText) {

    // Log Shader Creation
    Logger_->Log("Creating Shader Object", 5);

    // Create Shader
    ERS_OBJECT_SHADER ShaderStruct;

    ShaderStruct.CompileVertexShader(VertexText);
    ShaderStruct.CompileFragmentShader(FragmentText);

    // Attach Shaders
    Logger_->Log("Linking Shader Program", 5);
    ShaderStruct.CreateShaderProgram();
    Logger_->Log("Linked Shader Program", 4);

    // Return Struct
    return ShaderStruct;

}

// Load Shader From Disk
ERS_OBJECT_SHADER ShaderLoader::LoadShaderFromFile(const char* VertexPath, const char* FragmentPath) {

    // Load Shaders From Disk Into RAM
    Logger_->Log("Loading Shaders From Disk", 5);
    std::string VertexText = ReadFile(VertexPath, Logger_);
    std::string FragmentText = ReadFile(FragmentPath, Logger_);

    // Return Compiled Shader
    return CreateShaderObject(VertexText.c_str(), FragmentText.c_str());


}
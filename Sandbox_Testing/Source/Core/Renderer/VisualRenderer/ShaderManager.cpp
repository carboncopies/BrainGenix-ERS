//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the shader compiler.
    Additonal Notes: None
    Date Created: 2021-11-02
*/

#include <vector>

#include "Core/Loader/Shaders/ShaderLoader.cpp"

#include "Core/Renderer/VisualRenderer/ShaderManager.h"


unsigned int VertexShaderCompiler(const char* VertexText, LoggerClass *Logger_) {

    // Compile The Vertex Shader Text Into A Binary
    Logger_->Log("Compiling Vertex Shader", 5);
    unsigned int VertexShader;
    VertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(VertexShader, 1, &VertexText, NULL);
    glCompileShader(VertexShader);
    Logger_->Log("Compiled Vertex Shader", 5);

    // Report Compilation Status
    int VertexSuccess;
    char VertexInfoLog[512];
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &VertexSuccess);
    if (!VertexSuccess) {
        glGetShaderInfoLog(VertexShader, 512, NULL, VertexInfoLog);
        Logger_->Log("Vertex Shader Compilation Failed", 10);
        Logger_->Log(VertexInfoLog, 10);
    }

    // Return ID
    return VertexShader;

}

unsigned int FragmentShaderCompiler(const char* FragmentText, LoggerClass *Logger_) {

    // Compile The Fragment Shader Text Into A Binary
    Logger_->Log("Compiling Fragment Shader", 5);
    unsigned int FragmentShader;
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(FragmentShader, 1, &FragmentText, NULL);
    glCompileShader(FragmentShader);
    Logger_->Log("Compiled Fragment Shader", 5);

    // Report Compilation Status
    int FragmentSuccess;
    char FragmentInfoLog[512];
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &FragmentSuccess);
    if (!FragmentSuccess) {
        glGetShaderInfoLog(FragmentShader, 512, NULL, FragmentInfoLog);
        Logger_->Log("Fragment Shader Compilation Failed", 10);
        Logger_->Log(FragmentInfoLog, 10);
    }

    // Return ID
    return FragmentShader;

}

ShaderObject CreateShaderObject(const char* VertexText, const char* FragmentText, LoggerClass *Logger_) {

    // Log Shader Creation
    Logger_->Log("Creating Shader Object", 5);

    // Create Shader
    ShaderObject ShaderStruct;

    ShaderStruct.PopulateVertexShader(VertexShaderCompiler(VertexText, Logger_));
    ShaderStruct.PopulateFragmentShader(FragmentShaderCompiler(FragmentText, Logger_));

    // Return Struct
    return ShaderStruct;

}

ShaderObject LoadShaderFromFile(const char* VertexPath, const char* FragmentPath, LoggerClass *Logger_) {

    // Load Shaders From Disk Into RAM
    Logger_->Log("Loading Shaders From Disk", 5);
    std::string VertexText = ReadFile(VertexPath, Logger_);
    std::string FragmentText = ReadFile(FragmentPath, Logger_);

    
    // Return Compiled Shader
    return CreateShaderObject(VertexText.c_str(), FragmentText.c_str(), Logger_);


}
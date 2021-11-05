//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the shader compiler.
    Additonal Notes: None
    Date Created: 2021-11-02
*/






ERS_OBJECT_SHADER CreateShaderObject(const char* VertexText, const char* FragmentText, LoggerClass *Logger_) {

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

ERS_OBJECT_SHADER LoadShaderFromFile(const char* VertexPath, const char* FragmentPath, LoggerClass *Logger_) {

    // Load Shaders From Disk Into RAM
    Logger_->Log("Loading Shaders From Disk", 5);
    std::string VertexText = ReadFile(VertexPath, Logger_);
    std::string FragmentText = ReadFile(FragmentPath, Logger_);

    
    // Return Compiled Shader
    return CreateShaderObject(VertexText.c_str(), FragmentText.c_str(), Logger_);


}
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_ShaderLoader.h>


// ShaderLoader Constructor
ShaderLoader::ShaderLoader(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy Member Pointers
    SystemUtils_ = SystemUtils;

    // Log Initialization
    SystemUtils->Logger_->Log("Initializing Shader Loader", 5);

}

// ShaderLoader Destructor
ShaderLoader::~ShaderLoader() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("Shader Loader Destructor Called", 6);

}

// Load Shader From Memory
std::shared_ptr<ERS_STRUCT_Shader> ShaderLoader::CreateShaderObject(const char* VertexText, const char* FragmentText) {

    // Log Shader Creation
    SystemUtils_->Logger_->Log("Creating Shader Object", 5);

    // Create Shader
    std::shared_ptr<ERS_STRUCT_Shader> ShaderStruct = std::make_shared<ERS_STRUCT_Shader>();

    ShaderStruct->CompileVertexShader(VertexText);
    ShaderStruct->CompileFragmentShader(FragmentText);

    // Attach Shaders
    SystemUtils_->Logger_->Log("Linking Shader Program", 5);
    ShaderStruct->CreateShaderProgram();
    SystemUtils_->Logger_->Log("Linked Shader Program", 4);

    // Return Struct
    return ShaderStruct;

}

// Load Shader From Disk
std::shared_ptr<ERS_STRUCT_Shader> ShaderLoader::LoadShaderFromFile(long VertexID, long FragmentID) {

    // Load Shaders From Disk Into RAM
    SystemUtils_->Logger_->Log("Loading Shaders From Asset ID", 5);

    std::shared_ptr<ERS_STRUCT_IOData> VertexData = std::make_shared<ERS_STRUCT_IOData>();
    std::shared_ptr<ERS_STRUCT_IOData> FragmentData = std::make_shared<ERS_STRUCT_IOData>();


    std::string VertexText = ReadFile(VertexPath, SystemUtils_->Logger_);
    std::string FragmentText = ReadFile(FragmentPath, SystemUtils_->Logger_);

    // Return Compiled Shader
    return CreateShaderObject(VertexText.c_str(), FragmentText.c_str());


}
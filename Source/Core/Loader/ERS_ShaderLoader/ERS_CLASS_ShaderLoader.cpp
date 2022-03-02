//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_ShaderLoader.h>


ERS_CLASS_ShaderLoader::ERS_CLASS_ShaderLoader(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils->Logger_->Log("Initializing Shader Loader", 5);

}

ERS_CLASS_ShaderLoader::~ERS_CLASS_ShaderLoader() {

    SystemUtils_->Logger_->Log("Shader Loader Destructor Called", 6);

}

std::shared_ptr<ERS_STRUCT_Shader> ERS_CLASS_ShaderLoader::CreateShaderObject(const char* VertexText, const char* FragmentText, bool LogBuild) {

    if (LogBuild) {
        SystemUtils_->Logger_->Log("Creating Shader Object", 5);
    }

    // Create Shader
    std::shared_ptr<ERS_STRUCT_Shader> ShaderStruct = std::make_shared<ERS_STRUCT_Shader>();

    if (LogBuild) {
        SystemUtils_->Logger_->Log("Creating Vertex Shader Object", 3);
    }
    ShaderStruct->CompileVertexShader(VertexText, SystemUtils_->Logger_.get());
    if (LogBuild) {
        SystemUtils_->Logger_->Log("Finished Creating Vertex Shader", 4);
        SystemUtils_->Logger_->Log("Creating Fragment Shader", 3);
    }
    ShaderStruct->CompileFragmentShader(FragmentText, SystemUtils_->Logger_);
    if (LogBuild) {
        SystemUtils_->Logger_->Log("Finished Creating Fragment Shader Object", 4);
    }

    // Attach Shaders
    if (LogBuild) {
        SystemUtils_->Logger_->Log("Linking Shader Program", 5);
    }
    ShaderStruct->CreateShaderProgram(SystemUtils_->Logger_);
    if (LogBuild) {
        SystemUtils_->Logger_->Log("Linked Shader Program", 4);
    }

    return ShaderStruct;

}

std::shared_ptr<ERS_STRUCT_Shader> ERS_CLASS_ShaderLoader::LoadShaderFromAsset(long VertexID, long FragmentID, std::string ShaderName) {

    // Load Shaders From Disk Into RAM
    SystemUtils_->Logger_->Log("Loading Shaders From Asset ID", 5);

    std::shared_ptr<ERS_STRUCT_IOData> VertexData = std::make_shared<ERS_STRUCT_IOData>();
    std::shared_ptr<ERS_STRUCT_IOData> FragmentData = std::make_shared<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(VertexID, VertexData);
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(FragmentID, FragmentData);
    std::string VertexText = std::string((const char*)VertexData->Data.get());
    std::string FragmentText = std::string((const char*)FragmentData->Data.get());



    // Return Compiled Shader
    std::shared_ptr<ERS_STRUCT_Shader> ShaderStruct = CreateShaderObject(VertexText.c_str(), FragmentText.c_str());
    ShaderStruct->VertexID = VertexID;
    ShaderStruct->FragmentID = FragmentID;
    ShaderStruct->DisplayName = ShaderName;
    ShaderStruct->InternalName = ShaderName;
    return ShaderStruct;


}
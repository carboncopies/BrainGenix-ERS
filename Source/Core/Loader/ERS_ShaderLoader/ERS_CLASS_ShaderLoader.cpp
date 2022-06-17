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

void ERS_CLASS_ShaderLoader::CreateShaderObject(const char* VertexText, const char* FragmentText, ERS_STRUCT_Shader* ShaderStruct, bool LogBuild) {

    if (LogBuild) {
        SystemUtils_->Logger_->Log("Creating Shader Object", 5);
    }


    if (LogBuild) {
        SystemUtils_->Logger_->Log("Creating Vertex Shader Object", 3);
    }
    ShaderStruct->CompileVertexShader(VertexText, SystemUtils_->Logger_.get());
    if (LogBuild) {
        SystemUtils_->Logger_->Log("Finished Creating Vertex Shader", 4);
        SystemUtils_->Logger_->Log("Creating Fragment Shader", 3);
    }
    ShaderStruct->CompileFragmentShader(FragmentText, SystemUtils_->Logger_.get());
    if (LogBuild) {
        SystemUtils_->Logger_->Log("Finished Creating Fragment Shader Object", 4);
    }

    // Attach Shaders
    if (LogBuild) {
        SystemUtils_->Logger_->Log("Linking Shader Program", 5);
    }
    ShaderStruct->CreateShaderProgram(SystemUtils_->Logger_.get());
    if (LogBuild) {
        SystemUtils_->Logger_->Log("Linked Shader Program", 4);
    }


}

void ERS_CLASS_ShaderLoader::LoadShaderFromAsset(ERS_STRUCT_Shader*, long VertexID, long FragmentID, long GeometryID, long ComputeID, ShaderStruct, std::string ShaderName) {

    // Load Shaders From Disk Into RAM
    SystemUtils_->Logger_->Log(std::string("Loading Shaders From Asset IDs ")
     + std::to_string(VertexID) + std::string(", ")
     + std::to_string(FragmentID) + std::string(", ")
     + std::to_string(GeometryID) + std::string(", ")
     + std::to_string(ComputeID)
     , 5);

    std::unique_ptr<ERS_STRUCT_IOData> VertexData = std::make_unique<ERS_STRUCT_IOData>();
    std::unique_ptr<ERS_STRUCT_IOData> FragmentData = std::make_unique<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(VertexID, VertexData.get());
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(FragmentID, FragmentData.get());
    std::string VertexText = std::string((const char*)VertexData->Data.get());
    std::string FragmentText = std::string((const char*)FragmentData->Data.get());



    // Return Compiled Shader
    CreateShaderObject(VertexText.c_str(), FragmentText.c_str(), ShaderStruct);
    ShaderStruct->VertexID = VertexID;
    ShaderStruct->FragmentID = FragmentID;
    ShaderStruct->DisplayName = ShaderName;
    ShaderStruct->InternalName = ShaderName;

    SystemUtils_->Logger_->Log(std::string("Loaded Shader '") + ShaderName + std::string("'"), 5);



}
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ShaderLoader.h>


namespace {

std::string ShaderTextFromAssetData(const BG::ERS::IOSubsystem::IOData& AssetData) {

    if (AssetData.Data == nullptr || AssetData.Size_B == 0) {
        return "";
    }

    return std::string(reinterpret_cast<const char*>(AssetData.Data.get()), AssetData.Size_B);

}

}


ERS_CLASS_ShaderLoader::ERS_CLASS_ShaderLoader(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils->Logger_->Log("Initializing Shader Loader", 5);

}

ERS_CLASS_ShaderLoader::~ERS_CLASS_ShaderLoader() {

    SystemUtils_->Logger_->Log("Shader Loader Destructor Called", 6);

}

void ERS_CLASS_ShaderLoader::CreateShaderObject(ERS_STRUCT_Shader* ShaderStruct, std::string VertexText, std::string FragmentText, std::string GeometryText, std::string ComputeText, std::string TCText, std::string TEText, bool LogBuild) {

    SystemUtils_->Logger_->Log("Creating Shader Object", 5, LogBuild);


    SystemUtils_->Logger_->Log("Creating Vertex Shader Object", 3, LogBuild);
    ShaderStruct->CompileVertexShader(VertexText.c_str(), SystemUtils_->Logger_.get());
    SystemUtils_->Logger_->Log("Finished Creating Vertex Shader", 4, LogBuild);

    SystemUtils_->Logger_->Log("Creating Fragment Shader", 3, LogBuild);
    ShaderStruct->CompileFragmentShader(FragmentText.c_str(), SystemUtils_->Logger_.get());
    SystemUtils_->Logger_->Log("Finished Creating Fragment Shader Object", 4, LogBuild);

    if (GeometryText != "") {
        SystemUtils_->Logger_->Log("Creating Geometry Shader", 3, LogBuild);
        ShaderStruct->CompileGeometryShader(GeometryText.c_str(), SystemUtils_->Logger_.get());
        SystemUtils_->Logger_->Log("Finished Creating Geometry Shader Object", 4, LogBuild);
    }

    if (ComputeText != "") {
        SystemUtils_->Logger_->Log("Creating Compute Shader", 3, LogBuild);
        ShaderStruct->CompileComputeShader(ComputeText.c_str(), SystemUtils_->Logger_.get());
        SystemUtils_->Logger_->Log("Finished Creating Compute Shader Object", 4, LogBuild);
    }

    if (TCText != "") {
        SystemUtils_->Logger_->Log("Creating Tessellation Control Shader", 3, LogBuild);
        ShaderStruct->CompileTCShader(TCText.c_str(), SystemUtils_->Logger_.get());
        SystemUtils_->Logger_->Log("Finished Creating Tessellation Control Shader Object", 4, LogBuild);
    }

    if (TEText != "") {
        SystemUtils_->Logger_->Log("Creating Tessellation Evaluation Shader", 3, LogBuild);
        ShaderStruct->CompileTEShader(TEText.c_str(), SystemUtils_->Logger_.get());
        SystemUtils_->Logger_->Log("Finished Creating Tessellation Evaluation Shader Object", 4, LogBuild);
    }

    // Attach Shaders
    SystemUtils_->Logger_->Log("Linking Shader Program", 5, LogBuild);
    
    ShaderStruct->CreateShaderProgram(SystemUtils_->Logger_.get());
    SystemUtils_->Logger_->Log("Linked Shader Program", 4, LogBuild);

}

void ERS_CLASS_ShaderLoader::LoadShaderFromAsset(ERS_STRUCT_Shader* ShaderStruct, long VertexID, long FragmentID, long GeometryID, long ComputeID, long TCID, long TEID, std::string ShaderName) {

    // Load Shaders From Disk Into RAM
    SystemUtils_->Logger_->Log(std::string("Loading Shaders From Asset IDs ")
     + std::to_string(VertexID) + std::string(", ")
     + std::to_string(FragmentID) + std::string(", ")
     + std::to_string(GeometryID) + std::string(", ")
     + std::to_string(ComputeID) + std::string(", ")
     + std::to_string(TCID) + std::string(", ")
     + std::to_string(TEID)
     , 5);

    std::unique_ptr<BG::ERS::IOSubsystem::IOData> VertexData = std::make_unique<BG::ERS::IOSubsystem::IOData>();
    std::unique_ptr<BG::ERS::IOSubsystem::IOData> FragmentData = std::make_unique<BG::ERS::IOSubsystem::IOData>();
    std::unique_ptr<BG::ERS::IOSubsystem::IOData> GeometryData = std::make_unique<BG::ERS::IOSubsystem::IOData>();
    std::unique_ptr<BG::ERS::IOSubsystem::IOData> ComputeData = std::make_unique<BG::ERS::IOSubsystem::IOData>();
    std::unique_ptr<BG::ERS::IOSubsystem::IOData> TCData = std::make_unique<BG::ERS::IOSubsystem::IOData>();
    std::unique_ptr<BG::ERS::IOSubsystem::IOData> TEData = std::make_unique<BG::ERS::IOSubsystem::IOData>();

    std::string GeometryText, ComputeText, TCText, TEText;

    SystemUtils_->ERS_IOSubsystem_->ReadAsset(VertexID, VertexData.get());
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(FragmentID, FragmentData.get());


    if (GeometryID != -1) {
        SystemUtils_->ERS_IOSubsystem_->ReadAsset(GeometryID, GeometryData.get());
        GeometryText = ShaderTextFromAssetData(*GeometryData);
    }

    if (ComputeID != -1) {
        SystemUtils_->ERS_IOSubsystem_->ReadAsset(ComputeID, ComputeData.get());
        ComputeText = ShaderTextFromAssetData(*ComputeData);
    }

    if (TCID != -1) {
        SystemUtils_->ERS_IOSubsystem_->ReadAsset(TCID, TCData.get());
        TCText = ShaderTextFromAssetData(*TCData);
    }

    if (TEID != -1) {
        SystemUtils_->ERS_IOSubsystem_->ReadAsset(TEID, TEData.get());
        TEText = ShaderTextFromAssetData(*TEData);
    }


    std::string VertexText = ShaderTextFromAssetData(*VertexData);
    std::string FragmentText = ShaderTextFromAssetData(*FragmentData);


    // Return Compiled Shader
    CreateShaderObject(ShaderStruct, VertexText, FragmentText, GeometryText, ComputeText, TCText, TEText);
    ShaderStruct->VertexID = VertexID;
    ShaderStruct->FragmentID = FragmentID;
    ShaderStruct->GeometryID = GeometryID;
    ShaderStruct->ComputeID = ComputeID;
    ShaderStruct->TessellationControlShaderID = TCID;
    ShaderStruct->TessellationEvaluationShaderID = TEID;
    ShaderStruct->DisplayName = ShaderName;
    ShaderStruct->InternalName = ShaderName;

    SystemUtils_->Logger_->Log(std::string("Loaded Shader '") + ShaderName + std::string("' With OpenGL Program ID '") + std::to_string(ShaderStruct->ShaderProgram_) + std::string("'"), 5);



}

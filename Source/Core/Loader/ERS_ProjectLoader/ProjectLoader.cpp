//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ProjectLoader.h>


namespace {

    ERS::Renderer::ShadowFilteringType LoadShadowFilteringType(int Value, ERS::Renderer::ShadowFilteringType Fallback) {

        switch (Value) {
            case ERS::Renderer::ERS_SHADOW_FILTERING_DISABLED:
            case ERS::Renderer::ERS_SHADOW_FILTERING_PCF:
            case ERS::Renderer::ERS_SHADOW_FILTERING_POISSON_SAMPLING:
            case ERS::Renderer::ERS_SHADOW_FILTERING_STRATIFIED_POISSON_SAMPLING:
                return static_cast<ERS::Renderer::ShadowFilteringType>(Value);
            default:
                return Fallback;
        }

    }

    ERS::Renderer::ShadowUpdateMode LoadShadowUpdateMode(int Value, ERS::Renderer::ShadowUpdateMode Fallback) {

        switch (Value) {
            case ERS::Renderer::ERS_SHADOW_UPDATE_MODE_DISABLED:
            case ERS::Renderer::ERS_SHADOW_UPDATE_MODE_RANDOM:
            case ERS::Renderer::ERS_SHADOW_UPDATE_MODE_CONSECUTIVE:
            case ERS::Renderer::ERS_SHADOW_UPDATE_MODE_DISTANCE_PRIORITIZED:
            case ERS::Renderer::ERS_SHADOW_UPDATE_MODE_ALL:
                return static_cast<ERS::Renderer::ShadowUpdateMode>(Value);
            default:
                return Fallback;
        }

    }

    void LoadRendererSettings(const YAML::Node& RendererSettingsNode, ERS_STRUCT_RendererSettings* RendererSettings) {

        if (!RendererSettingsNode || RendererSettings == nullptr) {
            return;
        }

        if (RendererSettingsNode["ShadowMapX"]) {
            RendererSettings->ShadowMapX_ = RendererSettingsNode["ShadowMapX"].as<int>();
        }
        if (RendererSettingsNode["ShadowMapY"]) {
            RendererSettings->ShadowMapY_ = RendererSettingsNode["ShadowMapY"].as<int>();
        }
        if (RendererSettingsNode["ShadowFilteringType"]) {
            RendererSettings->ShadowFilteringType_ = LoadShadowFilteringType(RendererSettingsNode["ShadowFilteringType"].as<int>(), RendererSettings->ShadowFilteringType_);
        }
        if (RendererSettingsNode["ShadowUpdateMode"]) {
            RendererSettings->ShadowUpdateMode_ = LoadShadowUpdateMode(RendererSettingsNode["ShadowUpdateMode"].as<int>(), RendererSettings->ShadowUpdateMode_);
        }
        if (RendererSettingsNode["MaxShadowUpdatesPerFrame"]) {
            RendererSettings->MaxShadowUpdatesPerFrame_ = RendererSettingsNode["MaxShadowUpdatesPerFrame"].as<int>();
        }
        if (RendererSettingsNode["ShadowFilterKernelSize"]) {
            RendererSettings->ShadowFilterKernelSize_ = RendererSettingsNode["ShadowFilterKernelSize"].as<int>();
        }
        if (RendererSettingsNode["VRAMBudget"]) {
            RendererSettings->VRAMBudget_ = RendererSettingsNode["VRAMBudget"].as<unsigned long long>();
        }
        if (RendererSettingsNode["RAMBudget"]) {
            RendererSettings->RAMBudget_ = RendererSettingsNode["RAMBudget"].as<unsigned long long>();
        }
        if (RendererSettingsNode["WarningLowRAMBytes"]) {
            RendererSettings->WarningLowRAMBytes = RendererSettingsNode["WarningLowRAMBytes"].as<unsigned long long>();
        }
        if (RendererSettingsNode["CriticalLowRAMBytes"]) {
            RendererSettings->CriticalLowRAMBytes = RendererSettingsNode["CriticalLowRAMBytes"].as<unsigned long long>();
        }
        if (RendererSettingsNode["FatalLowRAMBytes"]) {
            RendererSettings->FatalLowRAMBytes = RendererSettingsNode["FatalLowRAMBytes"].as<unsigned long long>();
        }
        if (RendererSettingsNode["TerminateLowRAMBytes"]) {
            RendererSettings->TerminateLowRAMBytes = RendererSettingsNode["TerminateLowRAMBytes"].as<unsigned long long>();
        }
        if (RendererSettingsNode["WarningLowVRAMBytes"]) {
            RendererSettings->WarningLowVRAMBytes = RendererSettingsNode["WarningLowVRAMBytes"].as<unsigned long long>();
        }
        if (RendererSettingsNode["CriticalLowVRAMBytes"]) {
            RendererSettings->CriticalLowVRAMBytes = RendererSettingsNode["CriticalLowVRAMBytes"].as<unsigned long long>();
        }
        if (RendererSettingsNode["FatalLowVRAMBytes"]) {
            RendererSettings->FatalLowVRAMBytes = RendererSettingsNode["FatalLowVRAMBytes"].as<unsigned long long>();
        }
        if (RendererSettingsNode["TerminateLowVRAMBytes"]) {
            RendererSettings->TerminateLowVRAMBytes = RendererSettingsNode["TerminateLowVRAMBytes"].as<unsigned long long>();
        }

    }

}


ERS_CLASS_ProjectLoader::ERS_CLASS_ProjectLoader(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;

    SystemUtils_->Logger_->Log("Initializing Project Loader", 5);

}

ERS_CLASS_ProjectLoader::~ERS_CLASS_ProjectLoader() {

    SystemUtils_->Logger_->Log("ProjectLoader Destructor Called", 6);

}

ERS_STRUCT_Project ERS_CLASS_ProjectLoader::LoadProject(long AssetID) {

    // Log Project Loading
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Project With Asset ID ") + std::to_string(AssetID)).c_str(), 4);
    std::unique_ptr<BG::ERS::IOSubsystem::IOData> ProjectData = std::make_unique<BG::ERS::IOSubsystem::IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(AssetID, ProjectData.get());

    // Decode YAML
    std::string DataString = std::string((const char*)ProjectData->Data.get());
    YAML::Node ProjectNode = YAML::Load(DataString);



    // Create New Struct
    ERS_STRUCT_Project Project;
    Project.ControllerSettings = new std::vector<ERS_STRUCT_ControllerSettings>();

    // Populate Struct Metadata
    Project.ProjectName = ProjectNode["ProjectName"].as<std::string>();
    Project.ProjectDescription = ProjectNode["ProjectDescription"].as<std::string>();
    Project.ProjectVersion = ProjectNode["ProjectVersion"].as<std::string>();
    
    Project.ProjectCreationDate = ProjectNode["ProjectCreationDate"].as<std::string>();
    Project.ProjectModificationDate = ProjectNode["ProjectModificationDate"].as<std::string>();

    Project.ProjectCreator = ProjectNode["ProjectCreator"].as<std::string>();
    Project.ProjectLicense = ProjectNode["ProjectLicense"].as<std::string>();
    Project.IsLicenseProprietary = ProjectNode["IsLicenseProprietary"].as<bool>();
    
    Project.DefaultLayout = ProjectNode["DefaultLayout"].as<int>();
    Project.DefaultScene = ProjectNode["DefaultScene"].as<int>();
    Project.DefaultShaderProgram = ProjectNode["DefaultShaderProgram"].as<int>();
    
    if (ProjectNode["PlayOnLoad"]) {
        Project.StartPlayingOnLoad = ProjectNode["PlayOnLoad"].as<bool>();
    } else {
        Project.StartPlayingOnLoad = false;
        SystemUtils_->Logger_->Log("Project Metadata Missing 'PlayOnLoad' Param, Defaulting to 'FALSE'", 7);
    }

    LoadRendererSettings(ProjectNode["RendererSettings"], &Project.RendererSettings);
    if (SystemUtils_->RendererSettings_ != nullptr) {
        *SystemUtils_->RendererSettings_ = Project.RendererSettings;
    }


    // Populate Scene IDs
    YAML::Node ProjectSceneIDs = ProjectNode["SceneIDs"];
    for (YAML::const_iterator it=ProjectSceneIDs.begin(); it!=ProjectSceneIDs.end(); ++it) {
        SystemUtils_->Logger_->Log(std::string(std::string("Identified Scene In Project With ID: ") + std::to_string(it->second.as<long>())).c_str(), 3);
        Project.SceneIDs.push_back(it->second.as<long>());
    }

    // Populate Layouts
    YAML::Node EditorLayouts = ProjectNode["EditorLayouts"];
    for (YAML::const_iterator it=EditorLayouts.begin(); it!=EditorLayouts.end(); ++it) {
        SystemUtils_->Logger_->Log(std::string(std::string("Identified Layout Project With ID: ") + std::to_string(it->second.as<long>())).c_str(), 3);
        Project.EditorLayoutIDs.push_back(it->second.as<long>());
    }

    // Populate Controller Settings
    YAML::Node ControllerSettings = ProjectNode["ControllerSettings"];
    for (YAML::const_iterator it=ControllerSettings.begin(); it!=ControllerSettings.end(); ++it) {
        SystemUtils_->Logger_->Log(std::string(std::string("Identified Controller Settings Map With ID: ") + std::to_string(it->second.as<long>())).c_str(), 3);
        Project.GameControllerSettingsIDs.push_back(it->second.as<long>());
    }

    // Populate Shader Structs
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Shader Programs From Project Asset")).c_str(), 3);
    YAML::Node ShadersPrograms = ProjectNode["ShaderPrograms"];
    for (YAML::const_iterator it=ShadersPrograms.begin(); it!=ShadersPrograms.end(); ++it) {
        ERS_STRUCT_ShaderProgramAssetIDs Program;
        Program.Name = it->second["Name"].as<std::string>();
        Program.VertexID = it->second["VertexID"].as<long>();
        Program.FragmentID = it->second["FragmentID"].as<long>();

        if (it->second["GeometryID"]) {
            Program.GeometryID = it->second["GeometryID"].as<long>();
        } else {
            Program.GeometryID = -1;
        }

        if (it->second["ComputeID"]) {
            Program.ComputeID = it->second["ComputeID"].as<long>();
        } else {
            Program.ComputeID = -1;
        }

        if (it->second["TessControlID"]) {
            Program.TCID = it->second["TessControlID"].as<long>();
        } else {
            Program.TCID = -1;
        }
        
        if (it->second["TessEvalID"]) {
            Program.TEID = it->second["TessEvalID"].as<long>();
        } else {
            Program.TEID = -1;
        }
        
        

        Project.ShaderPrograms.push_back(Program);
    }
    SystemUtils_->Logger_->Log(std::string(std::string("Finished Loading Shader Programs")).c_str(), 4);

    // Populate Script Structs With Metadata
    if (ProjectNode["Scripts"]) {
        SystemUtils_->Logger_->Log("Loading Project Script Metadata", 5);
        YAML::Node Scripts = ProjectNode["Scripts"];
        for (YAML::const_iterator it=Scripts.begin(); it!=Scripts.end(); ++it) {
            ERS_STRUCT_Script Script;
            Script.Name_ = it->second["Name"].as<std::string>();
            Script.AssetID = it->second["AssetID"].as<long>();
            Project.Scripts.push_back(Script);
        }
    } else {
        SystemUtils_->Logger_->Log("Project Script Metadata Missing", 7);
    }


    // Load Script(s)
    SystemUtils_->Logger_->Log("Loading Project Scripts", 5);
    for (unsigned long i = 0; i < Project.Scripts.size(); i++) {
        
        ERS_STRUCT_Script* Script = &Project.Scripts[i];

        std::string LogStr = std::string("Loading Script '") + std::to_string(i) + std::string("' of '") + std::to_string(Project.Scripts.size()) + std::string("'");
        SystemUtils_->Logger_->Log(LogStr, 4);


        std::unique_ptr<BG::ERS::IOSubsystem::IOData> ScriptData = std::make_unique<BG::ERS::IOSubsystem::IOData>();
        SystemUtils_->ERS_IOSubsystem_->ReadAsset(Script->AssetID, ScriptData.get());
        Script->Code_ = std::string((const char*)ScriptData->Data.get());

        LogStr = std::string("Loaded Script '") + Script->Name_ + std::string("'");
        SystemUtils_->Logger_->Log(LogStr, 3);
    }


    // Return Struct When Populated
    return Project;

}

//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the project loader.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-30
*/

#include <ERS_ProjectLoader.h>


// Constructor
ERS_CLASS_ProjectLoader::ERS_CLASS_ProjectLoader(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Create Local Pointer
    SystemUtils_ = SystemUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Initializing Project Loader", 5);

}

// Destructor
ERS_CLASS_ProjectLoader::~ERS_CLASS_ProjectLoader() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("ERS_CLASS_ProjectLoader Destructor Called", 6);

}

// Project Loader Struct
ERS_STRUCT_Project ERS_CLASS_ProjectLoader::LoadProject(long AssetID) {

    // Log Project Loading
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Project With Asset ID ") + std::to_string(AssetID)).c_str(), 4);
    std::shared_ptr<ERS_STRUCT_IOData> ProjectData = std::make_shared<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(AssetID, ProjectData);

    std::cout<<ProjectData->Data.get()<<std::endl;

    // // Load File
    // YAML::Node ProjectNode = YAML::LoadFile();

    // // Create New Struct
    // ERS_PROJECT Project;


    // // Populate Struct
    // Project.ProjectName = ProjectNode["ProjectName"].as<std::string>();
    // Project.VersionMajor = ProjectNode["ProjectVersionMajor"].as<int>();
    // Project.VersionMinor = ProjectNode["ProjectVersionMinor"].as<int>();
    // Project.VersionPatch = ProjectNode["ProjectVersionPatch"].as<int>();
    

    // // Return Struct When Populated
    // return Project;

}

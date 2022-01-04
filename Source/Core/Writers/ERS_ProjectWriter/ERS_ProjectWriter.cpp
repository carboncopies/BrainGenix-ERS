//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This class writes ers projects to asset ids.
    Documentation Status: Completed
    Additonal Notes: None
    Date Created: 2022-01-04
*/

#include <ERS_ProjectWriter.h>



// Constructor
ERS_CLASS_ProjectWriter::ERS_CLASS_ProjectWriter(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy Pointer
    SystemUtils_ = SystemUtils;

    SystemUtils->Logger_->Log("Initializing ERS Project Writer Class", 5);

}

// Destructor
ERS_CLASS_ProjectWriter::~ERS_CLASS_ProjectWriter() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("System Destructor Called", 6);

}


// Save Project
bool ERS_CLASS_ProjectWriter::SaveProject(std::shared_ptr<ERS_STRUCT_Project> ProjectPointer, long AssetID) {

    // Log Save
    SystemUtils_->Logger_->Log(std::string(std::string("Saving Project To Asset ID ") + std::to_string(AssetID)).c_str(), 5);

    // Serialize Data
    SystemUtils_->Logger_->Log("Serializing Project", 4);
    YAML::Emitter ProjectEmitter;
    ProjectEmitter<<YAML::BeginMap;
    
    ProjectEmitter<<YAML::EndMap;

}
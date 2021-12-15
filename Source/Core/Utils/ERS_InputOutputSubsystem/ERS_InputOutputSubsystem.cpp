//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a single I/O interface for asset loading/saving.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-19
*/

#include <ERS_InputOutputSubsystem.h>


// Constructor
ERS_CLASS_InputOutputSubsystem::ERS_CLASS_InputOutputSubsystem(std::shared_ptr<LoggerClass> Logger, YAML::Node SystemConfiguration) {

    // Log Initialization
    Logger_->Log("Initializing Input/Output Subsystem", 5);

    // Get Database Loading / File Loading Config
    Logger_->Log("Reading Configuration For 'BOOL' 'UseDatabaseLoading'", 1);
    UseDatabase_ = SystemConfiguration["UseDatabaseLoading"].as<bool>();

}

// Destructor
ERS_CLASS_InputOutputSubsystem::~ERS_CLASS_InputOutputSubsystem() {

    // Log Destructor Call
    Logger_->Log("Input/Output Subsystem Destructor Called", 6);

}
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for implementing hardware information collection.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-03
*/

#include <HardwareInformation.h>


// HWinfo Constructor
HardwareInformation::HardwareInformation(LoggerClass *Logger) {

    // Copy Pointers
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Hardware Info Subsystem", 5);

    // Collect Static Hardware Information
    Logger_->Log("Collecting Static Hardware Information", 5);

    // Get CPU Info
    Logger_->Log("Getting CPU Information", 4);
    const auto CPUQuantities = iware::cpu::quantities();
    HardwareInfo_.Static_.CPUPhysicalCores = CPUQuantities.physical;
    HardwareInfo_.Static_.CPULogicalCores = CPUQuantities.logical;
    HardwareInfo_.Static_.CPUPackages = CPUQuantities.packages;
    Logger_->Log(std::string(std::string("Physical CPU Cores: ") + std::string(HardwareInfo_.Static_.CPUPhysicalCores)).c_str(), 4);
    Logger_->Log(std::string(std::string("Logical CPU Cores: ") + std::string(HardwareInfo_.Static_.CPULogicalCores)).c_str(), 4);
    Logger_->Log(std::string(std::string("Physical CPU Packages: ") + std::string(HardwareInfo_.Static_.CPUPackages)).c_str(), 4);


}

// Destructor
HardwareInformation::~HardwareInformation() {

    // Log Destructor Call
    Logger_->Log("Hardware Information Destructor Called", 4);

}
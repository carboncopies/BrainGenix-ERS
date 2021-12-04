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







static const char* cache_type_name(iware::cpu::cache_type_t cache_type) noexcept {
	switch(cache_type) {
		case iware::cpu::cache_type_t::unified:
			return "Unified";
		case iware::cpu::cache_type_t::instruction:
			return "Instruction";
		case iware::cpu::cache_type_t::data:
			return "Data";
		case iware::cpu::cache_type_t::trace:
			return "Trace";
		default:
			return "Unknown";
	}
}

static const char* architecture_name(iware::cpu::architecture_t architecture) noexcept {
	switch(architecture) {
		case iware::cpu::architecture_t::x64:
			return "x64";
		case iware::cpu::architecture_t::arm:
			return "ARM";
		case iware::cpu::architecture_t::itanium:
			return "Itanium";
		case iware::cpu::architecture_t::x86:
			return "x86";
		default:
			return "Unknown";
	}
}

static const char* endianness_name(iware::cpu::endianness_t endianness) noexcept {
	switch(endianness) {
		case iware::cpu::endianness_t::little:
			return "Little-Endian";
		case iware::cpu::endianness_t::big:
			return "Big-Endian";
		default:
			return "Unknown";
	}
}









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
    Logger_->Log(std::string(std::string("Physical CPU Cores: ") + std::to_string(HardwareInfo_.Static_.CPUPhysicalCores)).c_str(), 4);
    Logger_->Log(std::string(std::string("Logical CPU Cores: ") + std::to_string(HardwareInfo_.Static_.CPULogicalCores)).c_str(), 4);
    Logger_->Log(std::string(std::string("Physical CPU Packages: ") + std::to_string(HardwareInfo_.Static_.CPUPackages)).c_str(), 4);

    // Get CPU Cache Info
    for (int i = 0; i < HardwareInfo_.Static_.CPUPhysicalCores; i++) {
        const auto CPUCacheInfo = iware::cpu::cache(i);
        HardwareInfo_.Static_.CPUPhysicalCoreCacheSize.push_back(CPUCacheInfo.size);
        HardwareInfo_.Static_.CPUPhysicalCoreCacheLineSize.push_back(CPUCacheInfo.line_size);
        HardwareInfo_.Static_.CPUPhysicalCoreAssociativity.push_back(CPUCacheInfo.associativity);
        HardwareInfo_.Static_.CPUPhysicalCoreType.push_back(cache_type_name(CPUCacheInfo.type));
        
        
        


    }


}

// Destructor
HardwareInformation::~HardwareInformation() {

    // Log Destructor Call
    Logger_->Log("Hardware Information Destructor Called", 4);

}
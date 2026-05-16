//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

#include <HardwareInfo.h>
#include <BG/Common/Logger/Logger.h>


// Requests using the high power gpu on windows (YUCK!) platforms
#ifdef _WIN32
#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

#ifdef __cplusplus
}
#endif
#endif

void ERS_FUNCTION_ApplyGPUSelectionRequest(BG::Common::Logger::LoggingSystem* Logger, const ERS_STRUCT_HardwareInfo& HardwareInfo);

//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

#include <ghc/filesystem.hpp>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_GetExecutablePath.h>


namespace BrainGenix {
namespace ERS {
namespace Module {

/**
 * @brief Load the configuration from disk
 * 
 */
bool LoadLocalConfiguration(std::string Path, YAML::Node& Configuration);


} // Close Namespace: Module
} // Close Namespace: ERS
} // Close Namespace: BrainGenix

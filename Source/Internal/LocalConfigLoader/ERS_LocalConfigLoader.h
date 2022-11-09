//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <thread>
#include <chrono>
#include <iostream>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>


// Internal Libraries (BG convention: use <> instead of "")




namespace BrainGenix {
namespace ERS {
namespace Module {

/**
 * @brief Load the configuration from disk
 * 
 */
bool LoadLocalConfiguration(std::string Path, YAML::Node& Configuration);


}
}
}

//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <thread>
#include <chrono>
#include <iostream>

#ifdef __APPLE__
    #include <mach-o/dyld.h>
    #include <limits.h>
#endif

// Third-Party Libraries (BG convention: use <> instead of "")
#include <whereami.h>

// Internal Libraries (BG convention: use <> instead of "")




namespace BrainGenix {
namespace ERS {
namespace Module {

/**
 * @brief Returns the full absolute path of the executable
 * 
 */
std::string GetExecutablePath();

/**
 * @brief Returns the full absolute path of the directory containing the executable
 * 
 */
std::string GetExecutableDirectory();


} // Close Namespace: Module
} // Close Namespace: ERS
} // Close Namespace: BrainGenix

//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for implementing a struct to simplify includes within classes..
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-07
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory.h>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggerClass.h>

/**
 * @brief The System utils struct contains most system utils prepopulated as shared pointers within.
 * 
 */
struct ERS_STRUCT_SystemUtils {

    std::shared_ptr<LoggerClass> Logger_; /**<Pointer To BG-ERS Logging System*/


};
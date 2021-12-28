//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for implementing a struct to simplify includes within classes..
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-16
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory.h>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <ERS_InputOutputSubsystem.h>
#include <ERS_ModelWriter.h>
#include <ERS_CLASS_FramerateManager.h>


/**
 * @brief The System utils struct contains most system utils prepopulated as shared pointers within.
 * 
 */
struct ERS_STRUCT_SystemUtils {

    std::shared_ptr<LoggerClass> Logger_; /**<Pointer To BG-ERS Logging System*/
    std::shared_ptr<YAML::Node> LocalSystemConfiguration_; /**<Pointer To Config.yaml Data From Local Hard Drive*/
    std::shared_ptr<ERS_CLASS_InputOutputSubsystem> ERS_IOSubsystem_; /**<Pointer To ERS Input Output Subsystem*/
    std::shared_ptr<ERS_CLASS_ModelWriter> ERS_ModelWriter_; /**<Pointer To ERS Model Writer Instance*/
    std::shared_ptr<bool> SystemShouldRun_; /**<Pointer To Variable Setting If System Should Run Or Not*/
    std::shared_ptr<ERS_CLASS_FramerateManager> FramerateManager_; /**<Pointer to framerate subsystem*/

    int RenderWidth_ = 0; /**<Width of the display being rendered to (if using a window, this is the size of the window)*/
    int RenderHeight_ = 0; /**<Height of the display being rendered to (if using a window, this is the size of the window)*/
    
    bool IsLinux_ = true; /**<Boolean Value Set To True When Binary Is Compiled For Linux, False Otherwise*/

};
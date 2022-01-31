//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <chrono>
#include <filesystem>
#include <thread>
#include <mutex>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CASS_LoggingSystem.h>

#include <ERS_STRUCT_IOData.h>


class ERS_CLASS_IOTypeIdentifier {

// Private Member Vars
private:

    std::shared_ptr<ERS_CLASS_LoggingSystem> Logger_; /**<Shared Pointer To Logger Instance*/

// Private Methods
private:


// Public Member Vars
public:

// Public Methods
public:

    /**
     * @brief Construct a new ers class iotypeidentifier object
     * 
     * @param Logger 
     */
    ERS_CLASS_IOTypeIdentifier(std::shared_ptr<ERS_CLASS_LoggingSystem> Logger);


    /**
     * @brief Destroy the ers class iotypeidentifier object
     * 
     */
    ~ERS_CLASS_IOTypeIdentifier();

    /**
     * @brief Identify the type of the given data struct.
     * 
     * @param Data 
     */
    void IdentifyType(std::shared_ptr<ERS_STRUCT_IOData> Data);

};

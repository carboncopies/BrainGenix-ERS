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
#include <LoggingSystem.h>

#include <ERS_STRUCT_IOData.h>


class ERS_CLASS_IOTypeIdentifier {

// Private Member Vars
private:

    std::shared_ptr<LoggerClass> Logger_; /**<Shared Pointer To Logger Instance*/

// Private Methods
private:


// Public Member Vars
public:

// Public Methods
public:

    ERS_CLASS_IOTypeIdentifier(std::shared_ptr<LoggerClass> Logger);
    ~ERS_CLASS_IOTypeIdentifier();

};

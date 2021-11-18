//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for loading/compiling shaders.
    Additonal Notes: None
    Date Created: 2021-09-28
*/

#pragma once

#include <fstream>
#include <string>



#include "LoggingSystem.h"

std::string ReadFile(const std::string& FileName, LoggerClass *Logger_ = nullptr);


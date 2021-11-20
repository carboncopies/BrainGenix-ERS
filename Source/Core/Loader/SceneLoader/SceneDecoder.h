//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing scene decoding.
    Additonal Notes: None
    Date Created: 2021-10-13
*/  

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <map>
#include <iomanip>
#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <map>
#include <list>
#include <array>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <Scene.h>
#include <LoggingSystem.h>

ERS_OBJECT_SCENE LoadScene(long SceneID, LoggerClass *Logger_ = nullptr, bool LogLoading = false);



//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing scene decoding.
    Additonal Notes: None
    Date Created: 2021-10-13
*/  

#pragma once

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

#include <yaml-cpp/yaml.h>

#include "Core/Structures/Scene/Scene.h"

ERS_STRUCTURE_SCENE LoadScene(long SceneID, LoggerClass *Logger_ = nullptr, bool LogLoading = false);


#include "Core/Loader/Scene/SceneDecoder.cpp"
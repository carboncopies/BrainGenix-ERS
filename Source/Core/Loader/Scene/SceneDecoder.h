//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing scene decoding.
    Additonal Notes: None
    Date Created: 2021-10-13
*/  

#include <string>
#include <yaml-cpp/yaml.h>

YAML::Node LoadScene(long SceneID, LoggerClass *Logger_ = nullptr, bool LogLoading = false);


#include "Core/Loader/Scene/SceneDecoder.cpp"
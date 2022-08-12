//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")


/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to int to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetInt(YAML::Node Data, std::string Name, int &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to float to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetFloat(YAML::Node Data, std::string Name, float &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to bool to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetBool(YAML::Node Data, std::string Name, bool &Target);
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

#include <glm/glm.hpp>

// Internal Libraries (BG convention: use <> instead of "")




/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
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
 * @param Target Reference to the variable to be set to the decoded value
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
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetBool(YAML::Node Data, std::string Name, bool &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetLong(YAML::Node Data, std::string Name, long &Target);


/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetDouble(YAML::Node Data, std::string Name, double &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetUnsignedInt(YAML::Node Data, std::string Name, unsigned int &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetUnsignedLong(YAML::Node Data, std::string Name, unsigned long &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetLongLong(YAML::Node Data, std::string Name, long long &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetUnsignedLongLong(YAML::Node Data, std::string Name, unsigned long long &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetString(YAML::Node Data, std::string Name, std::string &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetVec3(YAML::Node Data, std::string Name, glm::vec3 &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetVec4(YAML::Node Data, std::string Name, glm::vec4 &Target);


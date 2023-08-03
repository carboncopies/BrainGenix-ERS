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
#include <BG/Common/Logger/Logger.h>



/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetInt(BG::Common::Logger::LoggingSystem* Logger, YAML::Node Data, std::string Name, int &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetFloat(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string Name, float &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetBool(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string Name, bool &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetLong(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string Name, long &Target);


/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetDouble(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string Name, double &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetUnsignedInt(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string Name, unsigned int &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetUnsignedLong(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string Name, unsigned long &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetLongLong(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string Name, long long &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetUnsignedLongLong(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string Name, unsigned long long &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetString(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string Name, std::string &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetNode(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string NameBase, YAML::Node &Target);



/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetStringVector(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string NameBase, std::vector<std::string> &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetIntVector(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string NameBase, std::vector<int> &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetLongVector(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string NameBase, std::vector<long> &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetNodeVector(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string NameBase, std::vector<YAML::Node> &Target);



/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * Will append X,Y,Z to get the three components of the vector.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetVec3(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string NameBase, glm::vec3 &Target);

/**
 * @brief Helper function to the YAML::CPP Library that helps catch errors and other problems.
 * Returns true on success, false on fail.
 * Will append Red,Green,Blue to get the three components of the vector.
 * 
 * @param Logger Pointer to ERS Logging system, used to log errors.
 * @param Data YAML::Node containing the target data
 * @param Name Name of the parameter in the yaml node
 * @param Target Reference to the variable to be set to the decoded value
 * @return true
 * @return false 
 */
bool ERS_FUNCTION_GetVec3Color(BG::Common::Logger::LoggingSystem* Logger,  YAML::Node Data, std::string NameBase, glm::vec3 &Target);
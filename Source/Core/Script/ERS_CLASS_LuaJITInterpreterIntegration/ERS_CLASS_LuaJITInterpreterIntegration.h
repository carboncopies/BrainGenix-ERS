//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <lua.hpp>

// Internal Libraries (BG convention: use <> instead of "")
#include <BG/Common/Logger/Logger.h>
#include <Model.h>
#include <PointLight.h>
#include <DirectionalLight.h>
#include <SpotLight.h>
#include <SceneCamera.h>

/**
 * @brief This class hosts the LuaJIT Interpreter, all other LuaJIT systems use this class to run their LuaJIT code.
 * 
 */
class ERS_CLASS_LuaJITInterpreterIntegration {

private:
    BG::Common::Logger::LoggingSystem*                      Logger_ = nullptr; /**<Pointer to the logging system class instance*/
    lua_State* L;
    double RunTime_ = -1.0f; /**<Time since game started playing*/


public:

    /**
     * @brief Construct a new ERS class LuaJItInterpreterintegration object
     * 
     */
    ERS_CLASS_LuaJITInterpreterIntegration(BG::Common::Logger::LoggingSystem* Logger);

    /**
     * @brief Destroy the ERS class LuaJITInterpreterintegration object
     * 
     */
    ~ERS_CLASS_LuaJITInterpreterIntegration();


    /**
     * @brief Test LuaJIT Scripting System. 
     * 
     * 
     */
    void Test_Script();


     /**
     * @brief Writes to the target error handling string if there's a pointer passed in.
     * 
     * @param Target 
     * @param LineNumber 
     * @param Error 
     */
    void ErrorHandle(std::vector<std::string>* Target, unsigned long LineNumber, std::string Error);

    /**
     * @brief Updates info sent to system info parts of the scripts. 
     * 
     * @param PlayTime 
     */
    void UpdateSystemInfoData(double PlayTime);


    /**
     * @brief Runs a script attached to a model object
     * 
     */
    bool ExecuteModelScript(std::string ScriptSource, ERS_STRUCT_Model* Model, std::vector<std::string>* ErrorMessageString = nullptr);

    /**
     * @brief Runs a script attached to a model object
     * 
     */
    bool ExecuteSceneCameraScript(std::string ScriptSource, ERS_STRUCT_SceneCamera* Camera, std::vector<std::string>* ErrorMessageString = nullptr);

    /**
     * @brief Runs a script attached to a point light
     * 
     */
    bool ExecutePointLightScript(std::string ScriptSource, ERS_STRUCT_PointLight* PointLight, std::vector<std::string>* ErrorMessageString = nullptr);


    /**
     * @brief Runs a script attached to a directional light
     * 
     */
    bool ExecuteDirectionalLightScript(std::string ScriptSource, ERS_STRUCT_DirectionalLight* DirectionalLight, std::vector<std::string>* ErrorMessageString = nullptr);


    /**
     * @brief Runs a script attached to a spot light
     * 
     */
    bool ExecuteSpotLightScript(std::string ScriptSource, ERS_STRUCT_SpotLight* SpotLight, std::vector<std::string>* ErrorMessageString = nullptr);


    /**
     * @brief Provides access to systeminfo data
     * 
     */
    void SetSystemInfoData(lua_State* L);


};


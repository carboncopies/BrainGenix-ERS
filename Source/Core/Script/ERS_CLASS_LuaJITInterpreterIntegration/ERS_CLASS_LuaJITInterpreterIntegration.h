//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <string>
#include <memory>
//#include <chrono>
#include <iostream>
//#include <algorithm>
#include <sstream>
//#include <iterator>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <lua.hpp>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
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
    ERS_LoggingSystem*                      Logger_ = nullptr; /**<Pointer to the logging system class instance*/
    lua_State* L;
    double RunTime_ = -1.0f; /**<Time since game started playing*/


public:

    /**
     * @brief Construct a new ERS class LuaJItInterpreterintegration object
     * 
     */
    ERS_CLASS_LuaJITInterpreterIntegration(ERS_LoggingSystem* Logger);

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
    void UpdateSystemInfoData(double RunTime);
    void ErrorHandle(std::vector<std::string>* Target, unsigned long LineNumber, std::string Error);
    bool ExecuteSceneCameraScript(std::string ScriptSource, ERS_STRUCT_SceneCamera* Camera, std::vector<std::string>* ErrorMessageString);


};


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
#include <LuaCpp.hpp>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_LoggingSystem.h>
using namespace LuaCpp;
using namespace LuaCpp::Registry;
using namespace LuaCpp::Engine;

/**
 * @brief This class hosts the LuaJIT Interpreter, all other LuaJIT systems use this class to run their LuaJIT code.
 * 
 */
class ERS_CLASS_LuaJITInterpreterIntegration {

private:

    ERS_LoggingSystem*                      Logger_ = nullptr; /**<Pointer to the logging system class instance*/
    std::unique_ptr<LuaJIT::scoped_interpreter> Guard_;            /**<LuaJIT Interpreter Guard Class*/
    

public:

    /**
     * @brief Construct a new ERS class LuaJItInterpreterintegration object
     * 
     * @param Logger 
     */
    ERS_CLASS_ LuaJItInterpreterIntegration(ERS_LoggingSystem* Logger);

    /**
     * @brief Destroy the ERS class LuaJITInterpreterintegration object
     * 
     */
    ~ERS_CLASS_ LuaJItInterpreterIntegration();


    /**
     * @brief Test LuaJIT Scripting System. 
     * 
     * 
     */
    void Test_Script();

};


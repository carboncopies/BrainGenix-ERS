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
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>

#include <ERS_STRUCT_Model.h>
#include <ERS_STRUCT_PointLight.h>
#include <ERS_STRUCT_DirectionalLight.h>
#include <ERS_STRUCT_SpotLight.h>

#include <PyBind11ModelClass.h>
#include <PyBind11SystemInfo.h>



/**
 * @brief This class hosts the python Interpreter, all other python systems use this class to run their python code.
 * 
 */
class ERS_CLASS_PythonInterpreterIntegration {

private:

    ERS_CLASS_LoggingSystem* Logger_; /**<Pointer to the logging system class instance*/
    std::unique_ptr<pybind11::scoped_interpreter> Guard_; /**<Python Interpreter Guard Class*/

    double RunTime_; /**<Time since game started playing*/


    /**
     * @brief Writes to the target error handling string if there's a pointer passed in.
     * 
     * @param Target 
     * @param LineNumber 
     * @param Error 
     */
    void ErrorHandle(std::vector<std::string>* Target, unsigned long LineNumber, std::string Error);


public:

    /**
     * @brief Construct a new ers class pythonInterpreterintegration object
     * 
     * @param Logger 
     */
    ERS_CLASS_PythonInterpreterIntegration(ERS_CLASS_LoggingSystem* Logger);

    /**
     * @brief Destroy the ers class pythonInterpreterintegration object
     * 
     */
    ~ERS_CLASS_PythonInterpreterIntegration();


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
     * @brief Runs a script attached to a point light
     * 
     */
    bool ExecutePointLightScript(std::string ScriptSource, ERS_STRUCT_PointLight* Model);


    /**
     * @brief Provides access to systeminfo data
     * 
     */
    void SetSystemInfoData(pybind11::module* Locals);

};


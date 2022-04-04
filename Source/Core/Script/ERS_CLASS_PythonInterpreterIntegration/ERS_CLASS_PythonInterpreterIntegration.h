//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <string>
#include <memory>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>


// Clear warnings about visibility issues
#pragma GCC visibility push(hidden)

/**
 * @brief This class hosts the python Interpreter, all other python systems use this class to run their python code.
 * 
 */
class ERS_CLASS_PythonInterpreterIntegration {

private:

    ERS_CLASS_LoggingSystem* Logger_; /**<Pointer to the logging system class instance*/
    std::unique_ptr<pybind11::scoped_interpreter> Guard_; /**<Python Interpreter Guard Class*/

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
     * @brief Runs some python code, passed in as the 'code' argument.
     * 
     * @param Code 
     */
    void ExecuteCode(std::string Code);


    int foo();

};


// Re-enable warnings about visibility
#pragma GCC visibility pop
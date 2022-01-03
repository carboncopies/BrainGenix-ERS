//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the project loader.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-30
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>


// Third-Party Libraries (BG convention: use <> instead of "")


// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_IOData.h>
#include <ERS_STRUCT_SystemUtils.h>

#include <ERS_InputOutputSystem.h>




/**
 * @brief Class for loading project files
 * 
 */
class ProjectLoader {


private:

    // Logger
    std::shared_ptr<ERS_STRUCTURE_SystemUtils> Logger_; /**<Pointer to Logging System.*/



public:

    /**
     * @brief Construct a new Project Loader object
     * 
     * @param Logger 
     */
    ProjectLoader(std::shared_ptr<LoggerClass> Logger);

    /**
     * @brief 
     * 
     */
    ~ProjectLoader();

    /**
     * @brief Load a project from a file path.
     * 
     * @param FilePath 
     */
    ERS_PROJECT LoadProject(const char* FilePath = "Assets/Project.yaml");





};


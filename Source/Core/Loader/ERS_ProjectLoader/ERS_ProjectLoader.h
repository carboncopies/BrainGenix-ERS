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

#include <ERS_STRUCT_Project.h>

#include <ERS_InputOutputSubsystem.h>




/**
 * @brief Class for loading project files
 * 
 */
class ERS_CLASS_ProjectLoader {


private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Pointer to system utils*/



public:

    /**
     * @brief Construct a new Project Loader object
     * 
     * @param Logger 
     */
    ERS_CLASS_ProjectLoader(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);

    /**
     * @brief 
     * 
     */
    ~ERS_CLASS_ProjectLoader();

    /**
     * @brief Load a project from a file path.
     * 
     * @param FilePath 
     */
    ERS_STRUCT_Project LoadProject(long AssetID);


};
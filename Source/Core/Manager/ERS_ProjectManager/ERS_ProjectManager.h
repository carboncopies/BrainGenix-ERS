//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a class to manage project loading/writing/storage functions.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2022-01-03
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <thread>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_CLASS_ProjectLoader.h>


/**
 * @brief Project Manager Class
 * 
 */
class ERS_CLASS_ProjectManager {


private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Pointer To System Utils Struct*/
    std::shared_ptr<ERS_CLASS_ProjectLoader> ProjectLoader_; /**<Project Loader Util*/

public:


    ERS_CLASS_ProjectManager();
    ~ERS_CLASS_ProjectManager();


};
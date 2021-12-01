//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the project struct.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-30
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")


struct ERS_PROJECT {

    // Project Metadata
    int VersionMajor = 0;
    int VersionMinor = 0;
    int VersionPatch = 0;
    std::string ProjectName = "Untitled";


};
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for implementing a struct to store project info.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2022-01-02
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")



/**
 * @brief Struct to store project information
 * 
 */
struct ERS_STRUCT_Project {

    // Project Metadata
    std::string ProjectName = ""; /**<Stores The Project's Name*/
    std::string ProjectDescription = ""; /**<Stores Project's description*/
    std::string ProjectVersion = ""; /**<Project Version Information*/

    std::string ProjectCreationDate = ""; /**<Project's creation date*/
    std::string ProjectModificationDate = ""; /**<Date when project was last modified*/
    std::string ProjectCreator = ""; /**<Name Of Organization/Team/Person That Created The Project*/
    
    std::string ProjectLicense = ""; /**<Name Of License Used By Project*/
    bool IsLicenseProprietary = false; /**<Presents a user warning when loading to make them aware that the project is not free software*/

    std::vector<long> ProjectSceneIDs; /**<Vector Of Scene IDs Used In The Project*/
    std::vector<long> ProjectConfigurationIDs; /**<Vector Of Configuration IDs Used In The Project*/
    long DefaultLayout = 0; /**<Default Layout Used*/

};
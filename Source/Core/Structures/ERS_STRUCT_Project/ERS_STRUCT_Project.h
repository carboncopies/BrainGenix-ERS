//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_ControllerSettings.h>
#include <ERS_STRUCT_ShaderProgramAssetIDs.h>


/**
 * @brief Struct to store project information
 * 
 */
struct ERS_STRUCT_Project {

    std::string ProjectName = ""; /**<Stores The Project's Name*/
    std::string ProjectDescription = ""; /**<Stores Project's description*/
    std::string ProjectVersion = ""; /**<Project Version Information*/

    std::string ProjectCreationDate = ""; /**<Project's creation date*/
    std::string ProjectModificationDate = ""; /**<Date when project was last modified*/
    std::string ProjectCreator = ""; /**<Name Of Organization/Team/Person That Created The Project*/
    
    std::string ProjectLicense = ""; /**<Name Of License Used By Project*/
    bool IsLicenseProprietary = false; /**<Presents a user warning when loading to make them aware that the project is not free software*/

    std::vector<long> SceneIDs; /**<Vector Of Scene IDs Used In The Project*/
    std::vector<long> EditorLayoutIDs; /**<Vector Of Editor Layouts To Be Used In This Project*/
    std::vector<long> GameControllerSettingsIDs; /**<Vector of layouts for game controller settings*/
    std::vector<ERS_STRUCT_ShaderProgramAssetIDs> ShaderPrograms; /**<List of Shader Program Instances*/
    long DefaultShaderProgram; /**<Set default index of the shader program*/
    std::vector<std::shared_ptr<ERS_STRUCT_ControllerSettings>> ControllerSettings; /**<List of game controller settings instances*/

    int DefaultScene = 0; /**<Defualt Scene Index*/
    int DefaultLayout = 0; /**<Default Layout Used*/

};
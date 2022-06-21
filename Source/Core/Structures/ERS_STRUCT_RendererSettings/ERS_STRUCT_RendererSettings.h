// ToDO: then add to project struct, then update project loader/writer with this info. Then check trello board for other related tasks like live ediitng.


//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_ENUM_ShadowFilteringType.h>


/**
 * @brief Struct containing renderer settings.
 * 
 */
struct ERS_STRUCT_RendererSettings {

    // Shadow Map Settings
    int ShadowMapX_ = 2048;
    int ShadowMapY_ = 2048;

    // Set Shadow Filtering Type
    ERS::Renderer::ShadowFilteringType ShadowFilteringType_ = ERS::Renderer::ERS_PCF_FILTERING;
    
    // Set Max Shadow Updates Per Frame
    int MaxShadowUpdatesPerFrame_ = 20;

    

};
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
#include <ERS_ENUM_ShadowUpdateMode.h>


/**
 * @brief Struct containing renderer settings.
 * 
 */
struct ERS_STRUCT_RendererSettings {

    // Shadow Map Settings
    int ShadowMapX_ = 2048;
    int ShadowMapY_ = 2048;

    // Set Shadow Update Settings
    ERS::Renderer::ShadowFilteringType ShadowFilteringType_ = ERS::Renderer::ERS_SHADOW_FILTERING_POISSON_SAMPLING;
    ERS::Renderer::ShadowUpdateMode ShadowUpdateMode_ = ERS::Renderer::ERS_SHADOW_UPDATE_MODE_DISTANCE_PRIORITIZED;
    int MaxShadowUpdatesPerFrame_ = 5;
    int ShadowFilterKernelSize_ = 2;
    
    unsigned long long VRAMBudget_ = 68719476736; // 64 GB default
    unsigned long long RAMBudget_ = 549755813888; // 512 GB default

    unsigned long long CurrentVRAMUsage_ = 0;
    unsigned long long CurrentRAMUsage_ = 0;
    
};
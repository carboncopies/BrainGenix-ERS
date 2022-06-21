//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")


namespace ERS {

    namespace Renderer {

        enum ShadowUpdateMode {

            ERS_NO_SHADOW_UPDATES,
            ERS_RANDOM_SHADOW_UPDATES,
            ERS_CONSECUTIVE_SHADOW_UPDATES,
            ERS_DISTANCE_PRIORITIZED_SHADOW_UPDATES,
            ERS_ALL_SHADOW_UPDATES

        };

    }

}
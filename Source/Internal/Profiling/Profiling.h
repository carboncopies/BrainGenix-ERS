//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

#ifdef ERS_ENABLE_TRACY

#include <tracy/Tracy.hpp>

#define ERS_PROFILE_SCOPE() ZoneScoped
#define ERS_PROFILE_NAMED_SCOPE(Name) ZoneScopedN(Name)
#define ERS_PROFILE_FRAME_MARK() FrameMark

#else

#define ERS_PROFILE_SCOPE() do {} while (0)
#define ERS_PROFILE_NAMED_SCOPE(Name) do { (void)sizeof(Name); } while (0)
#define ERS_PROFILE_FRAME_MARK() do {} while (0)

#endif

########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

add_library(ERS_Profiling INTERFACE)

target_include_directories(ERS_Profiling INTERFACE ./)

if(ENABLE_TRACY)
    target_compile_definitions(ERS_Profiling INTERFACE ERS_ENABLE_TRACY TRACY_ENABLE)
    target_link_libraries(ERS_Profiling INTERFACE Tracy::TracyClient)
endif()

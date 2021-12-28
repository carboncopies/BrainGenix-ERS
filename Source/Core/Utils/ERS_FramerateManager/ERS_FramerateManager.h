//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a system for managing the framerate, it also provides FR related metrics.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-28
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <thread>
#include <chrono>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>


/**
 * @brief This class provides a system for managing the framerate. Additionally, it provides an interface for adjusting the target and identifying when targets are not met, etc.
 * 
 */
class ERS_CLASS_FramerateManager {

private:

public:

    ERS_CLASS_FramerateManager();
    ~ERS_CLASS_FramerateManager();
    

};
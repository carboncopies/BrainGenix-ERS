//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a system for managing the framerate, it also provides FR related metrics.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-28
*/

#include <ERS_FramerateManager.h>


// Constructor
ERS_CLASS_FramerateManager::ERS_CLASS_FramerateManager() {

}

// Destructor
ERS_CLASS_FramerateManager::~ERS_CLASS_FramerateManager() {

}


// Set Target Framerate
void ERS_CLASS_FramerateManager::SetTargetFramerate(int Framerate) {

    // Copy FR
    TargetFrameRate_ = Framerate;

    // Calculate Target Frame Time
    TargetFrameTime_ = 1/Framerate;

}


// Start Timer
void ERS_CLASS_FramerateManager::StartNewFrame() {

    // Get Current Time, Set To Start Time
    FrameStartTime_ = Clock_.now();

}

// Delay Until Next Frame
void ERS_CLASS_FramerateManager::DelayUntilNextFrame() {

    // Get Current Time
    FrameEndTime_ = Clock_.now();

    // Calculate Delta Time
    double FrameTime = std::chrono::duration_cast<std::chrono::microseconds>(FrameEndTime_ - FrameStartTime_).count();
    std::cout<<FrameTime<<std::endl;

}
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

    SetTargetFramerate(60);

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
    FrameStartTime_ = glfwGetTime();

}

// Delay Until Next Frame
void ERS_CLASS_FramerateManager::DelayUntilNextFrame() {

    // Get Current Time
    FrameEndTime_ = glfwGetTime();

    // Calculate Delta Time
    double FrameTime = (FrameEndTime_ - FrameStartTime_);

    FrameSamples_.push_back(FrameTime);
    if (FrameSamples_.size() > NumberSamples_) {
        FrameSamples_.erase(FrameSamples_.begin());
    }
    ActualFrameTimes_.push_back(FrameTime);
    if (ActualFrameTimes_.size() > 1000) {
        ActualFrameTimes_.erase(ActualFrameTimes_.begin());
    }

    // Calc Average
    double SumFrameTimes = 0.0f;
    for (int i = 0; i < FrameSamples_.size(); i++) {
        SumFrameTimes += FrameSamples_[i];
    }
    AverageFrameTime_ = SumFrameTimes / FrameSamples_.size();

    // Add To Avg Array
    AverageFrameTimes_.push_back(AverageFrameTime_);
    if (AverageFrameTimes_.size() > 1000) {
        AverageFrameTimes_.erase(AverageFrameTimes_.begin());
    }

    // Sleep For Duration
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::nanoseconds((int)(TargetFrameTime_*100000000)));

}

// Get Last Frame Time
float ERS_CLASS_FramerateManager::GetLastFrameTime() {

    // Return Averate Frame Time
    return AverageFrameTime_;

}
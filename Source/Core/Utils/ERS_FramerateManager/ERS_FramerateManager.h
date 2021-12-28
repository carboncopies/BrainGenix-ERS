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
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")



/**
 * @brief This class provides a system for managing the framerate. Additionally, it provides an interface for adjusting the target and identifying when targets are not met, etc.
 * 
 */
class ERS_CLASS_FramerateManager {

// Private Member Vars
private:

    std::chrono::high_resolution_clock Clock_; /**<High Res Clock Used For Frame Time Calcs*/
    int TargetFrameRate_ = 60; /**<Target Frame Rate In FPS*/
    float TargetFrameTime_; /**<Target Frame Time In MS*/

    std::chrono::_V2::system_clock::time_point FrameStartTime_; /**<Starting Time Of Frame*/
    std::chrono::_V2::system_clock::time_point FrameEndTime_; /**<Ending Time Of Frame*/
    float AverageFrameTime_; /**<Float representing the average time in ms*/
    int NumberSamples_ = 20; /**<Set number of samples used in average*/


// Public Info
public:

    std::vector<double> ActualFrameTimes_; /**<List of last thousand actual measured frame times in seconds*/
    

// Public Methods
public:

    /**
     * @brief Construct a new ers class frameratemanager object
     * 
     */
    ERS_CLASS_FramerateManager();

    /**
     * @brief Destroy the ers class frameratemanager object
     * 
     */
    ~ERS_CLASS_FramerateManager();
    


    /**
     * @brief Call at the start of every frame, starts the timer.
     * 
     */
    void StartNewFrame(); 

    /**
     * @brief Call at the end of every frame, delays to next frame if needed.
     * 
     */
    void DelayUntilNextFrame();

    /**
     * @brief Set the Target Framerate value.
     * 
     * @param TargetFramerate 
     */
    void SetTargetFramerate(int TargetFramerate);

};
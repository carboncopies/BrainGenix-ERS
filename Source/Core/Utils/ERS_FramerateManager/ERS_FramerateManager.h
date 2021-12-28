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

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>



/**
 * @brief This class provides a system for managing the framerate. Additionally, it provides an interface for adjusting the target and identifying when targets are not met, etc.
 * 
 */
class ERS_CLASS_FramerateManager {

private:
    
    std::chrono::high_resolution_clock Clock_; /**<High Res Clock Used For Frame Time Calcs*/
    int TargetFrameRate_; /**<Target Frame Rate In FPS*/
    float TargetFrameTime_; /**<Target Frame Time In MS*/

    double FrameStartTime_; /**<Starting Time Of Frame*/
    double FrameEndTime_; /**<Ending Time Of Frame*/

// Public Info
public:

    std::vector<double> ActualFrameTimes_; /**<List of actual measured frame times in seconds*/
    
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
     * @brief Call every frame, delays to next frame if needed.
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
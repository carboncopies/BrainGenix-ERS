//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides IOManager functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-29
*/

#include <IOManager.h>



// IOManager Constructor
IOManager::IOManager(LoggerClass *Logger, GLFWwindow* Window, ERS_OBJECT_CAMERA_NOCLIP *Camera) {

    // Copy Pointer
    Logger_ = Logger;
    Camera_ = Camera;
    Window_ = Window;
    //FramebufferManager_ = FramebufferManager;

    // Log Initialization
    Logger_->Log("Initializing IOManager", 5);

    // Create InputProcssor
    Logger_->Log("Setting Up Window Input Processor", 5);
    InputProcessor_ = new InputProcessor(Camera_, Window_);



}


// IOManager Destructor
IOManager::~IOManager() {

    // Log Destructor Call
    Logger_->Log("IOManager Destructor Called", 6);

}


// Update Frame
void IOManager::UpdateFrame(float DeltaTime) {


    // Process Window Input
    glfwGetWindowSize(Window_, &WindowWidth_, &WindowHeight_);
    glfwPollEvents();


}
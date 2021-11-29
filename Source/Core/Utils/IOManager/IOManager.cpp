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
IOManager::IOManager(LoggerClass *Logger) {

    // Copy Pointer
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing IOManager", 5);

    // Create InputProcssor
    Logger_->Log("Setting Up Window Input Processor", 5);
    InputProcessor_ = new InputProcessor(&Camera_, Window_, FramebufferManager_);



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

    // Get IMGUI IO State
    auto Io = &ImGui::GetIO();

    // Enable/Disable Mouse Capture
    if ((glfwGetMouseButton(Window_, 0) == GLFW_PRESS) && (!Io->WantCaptureMouse) ){
        CaptureMouseCursor_ = true;
    } else {
        CaptureMouseCursor_ = false;
    }


    InputProcessor_->ProcessKeyboardInput(Logger_, DeltaTime, CaptureMouseCursor_);
    InputProcessor_->UpdateFramebuffer();
    InputProcessor_->UpdateMouse(CaptureMouseCursor_);


    // Update Mouse Capture State
    if (CaptureMouseCursor_) {
        glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

}
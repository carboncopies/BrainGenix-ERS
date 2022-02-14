//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <IOManager.h>



IOManager::IOManager(std::shared_ptr<ERS_CLASS_LoggingSystem> Logger, GLFWwindow* Window, std::shared_ptr<ERS_STRUCT_Camera> Camera) {

    Logger_ = Logger;
    Camera_ = Camera;
    Window_ = Window;
    Logger_->Log("Initializing IOManager", 5);

    // Create InputProcssor
    Logger_->Log("Setting Up Window Input Processor", 5);
    InputProcessor_ = std::make_shared<ERS_CLASS_InputProcessor>(Camera_, Window_);



}


IOManager::~IOManager() {

    Logger_->Log("IOManager Destructor Called", 6);

}


// Update Frame
void IOManager::UpdateFrame(float DeltaTime) {


    // Process Window Input
    glfwGetWindowSize(Window_, &WindowWidth_, &WindowHeight_);
    glfwPollEvents();


}
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the visual renderer callback functions.
    Documentation Status: Done
    Additonal Notes: None
    Date Created: 2021-11-16
*/

#include "InputProcessor.h"


// InputProcessor Constructor
InputProcessor::InputProcessor(ERS_OBJECT_CAMERA_NOCLIP *Camera, GLFWwindow *Window) {

    // Copy To Member Pointer
    Camera_ = Camera;
    Window_ = Window;

}

// InputProcessor Destructor
InputProcessor::~InputProcessor() {

    // Nothing To Do
}


// UpdateFramebuffer Function
void InputProcessor::UpdateFramebuffer() {

    // Get Window Size
    int WindowX;
    int WindowY;
    glfwGetFramebufferSize(Window_, &WindowX, &WindowY);

    // Call UpdateFramebuffer
    FramebufferSizeCallback(WindowX, WindowY);

}

// Update Mouse Function
void InputProcessor::UpdateMouse( bool WindowMouseCaptureEnabled) {

    // Get Mouse Position
    double MouseX;
    double MouseY;
    glfwGetCursorPos(Window_, &MouseX, &MouseY);

    // Call Update
    MouseCallback(MouseX, MouseY);

}






// Internal Callback Framebuffer
void InputProcessor::FramebufferSizeCallback(int Width, int Height) {

    // Update Viewport
    glViewport(0, 0, Width, Height);
    glScissor(0, 0, Width, Height);

}

// Internal Callback MouseCallback
void InputProcessor::MouseCallback(double XPos, double YPos) {

    // Update Positions
    if (FirstMouse) {

        LastX = XPos;
        LastY = YPos;

        FirstMouse = false;

    }

    // Calculate Offsets
    float XOffset = XPos - LastX;
    float YOffset = YPos - LastY;

    // Update Last Positions
    LastX = XPos;
    LastY = YPos;

    // Process Camera Movement
    Camera_->ProcessMouseMovement(XOffset, YOffset);

}


// Internal Callback ScrollCallback
void InputProcessor::ScrollCallback(double YOffset) {

    Camera_->ProcessMouseScroll(YOffset);

}
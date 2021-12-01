//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the visual renderer callback functions.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-16
*/

#include "InputProcessor.h"


// InputProcessor Constructor
InputProcessor::InputProcessor(ERS_OBJECT_CAMERA_NOCLIP *Camera, GLFWwindow *Window) {

    // Copy To Member Pointer
    Camera_ = Camera;
    Window_ = Window;
    //FramebufferManager_ = FramebufferManager;

}

// InputProcessor Destructor
InputProcessor::~InputProcessor() {

    // Nothing To Do
}


// Process Mouse Scroll Input
void InputProcessor::ProcessMouseScroll(bool CaptureEnabled) {

    // Get Mouse Scroll Info
    float MouseScrollX = ImGui::GetScrollX();
    float MouseScrollY = ImGui::GetScrollY();

    // If Input Processing Enabled
    if (CaptureEnabled) {

        // Pass To Callback
        ScrollCallback(MouseScrollY);

    }

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
    if (WindowMouseCaptureEnabled) {
        MouseCallback(MouseX, MouseY);
    } else {
        LastX = MouseX;
        LastY = MouseY;

    }

}

// Update Keyboard Input
void InputProcessor::ProcessKeyboardInput(LoggerClass *Logger_, float DeltaTime, bool WindowCaptureEnabled) {


    if (glfwGetKey(Window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        Logger_->Log("Window Shutdown Invoked By Keyboard [ESC]", 2);
        glfwSetWindowShouldClose(Window_, true);
    }


    // Get Keyboard Input
    if (WindowCaptureEnabled) {

        if (glfwGetKey(Window_, GLFW_KEY_W) == GLFW_PRESS)
            Camera_->ProcessKeyboard(FORWARD, DeltaTime);
        if (glfwGetKey(Window_, GLFW_KEY_S) == GLFW_PRESS)
            Camera_->ProcessKeyboard(BACKWARD, DeltaTime);
        if (glfwGetKey(Window_, GLFW_KEY_A) == GLFW_PRESS)
            Camera_->ProcessKeyboard(LEFT, DeltaTime);
        if (glfwGetKey(Window_, GLFW_KEY_D) == GLFW_PRESS)
            Camera_->ProcessKeyboard(RIGHT, DeltaTime);
        if (glfwGetKey(Window_, GLFW_KEY_SPACE) == GLFW_PRESS)
            Camera_->ProcessKeyboard(UP, DeltaTime);
        if (glfwGetKey(Window_, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            Camera_->ProcessKeyboard(DOWN, DeltaTime);

    }

}

// Internal Callback Framebuffer
void InputProcessor::FramebufferSizeCallback(int Width, int Height) {


    // Update Viewport
    glViewport(0, 0, Width, Height);
    glScissor(0, 0, Width, Height);

    // Update Framebuffer Size
    //FramebufferManager_->ResizeFramebuffer(Width, Height);

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
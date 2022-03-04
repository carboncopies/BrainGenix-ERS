//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include "ERS_CLASS_InputProcessor.h"


ERS_CLASS_InputProcessor::ERS_CLASS_InputProcessor(ERS_STRUCT_Camera* Camera, GLFWwindow *Window) {

    Camera_ = Camera;
    Window_ = Window;
    //FramebufferManager_ = FramebufferManager;

}

ERS_CLASS_InputProcessor::~ERS_CLASS_InputProcessor() {
}


void ERS_CLASS_InputProcessor::ProcessMouseScroll(bool CaptureEnabled) {

    // Get Mouse Scroll Info
    float MouseScrollX = ImGui::GetIO().MouseWheel;
    //float MouseScrollY = ImGui::GetIO().MouseWheelH;


    // If Input Processing Enabled
    if (CaptureEnabled) {

        // Pass To Callback
        ScrollCallback(MouseScrollX);

    }

}

void ERS_CLASS_InputProcessor::UpdateFramebuffer() {

    // Get Window Size
    int WindowX;
    int WindowY;
    glfwGetFramebufferSize(Window_, &WindowX, &WindowY);

    // Call UpdateFramebuffer
    FramebufferSizeCallback(WindowX, WindowY);

}

void ERS_CLASS_InputProcessor::UpdateMouse( bool WindowMouseCaptureEnabled) {

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

void ERS_CLASS_InputProcessor::ProcessKeyboardInput(ERS_CLASS_LoggingSystem* Logger_, float DeltaTime, bool WindowCaptureEnabled) {


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

void ERS_CLASS_InputProcessor::FramebufferSizeCallback(int Width, int Height) {


    // Update Viewport
    glViewport(0, 0, Width, Height);
    glScissor(0, 0, Width, Height);

    // Update Framebuffer Size
    //FramebufferManager_->ResizeFramebuffer(Width, Height);

}

void ERS_CLASS_InputProcessor::MouseCallback(double XPos, double YPos) {

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

void ERS_CLASS_InputProcessor::ScrollCallback(double YOffset) {

    Camera_->ProcessMouseScroll(YOffset);

}
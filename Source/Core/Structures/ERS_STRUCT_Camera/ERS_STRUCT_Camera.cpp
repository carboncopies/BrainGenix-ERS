//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_STRUCT_Camera.h>
#include <iostream>

glm::mat4 ERS_STRUCT_Camera::GetViewMatrix() {
    return glm::lookAt(Position_, Position_ + Front_, Up_);
}

glm::mat4 ERS_STRUCT_Camera::GetProjectionMatrix() {
    return glm::perspective(glm::radians(Zoom_), AspectRatio_, 0.1f, 100.0f);
}


void ERS_STRUCT_Camera::SetAspectRatio(float AspectRatio) {
    AspectRatio_ = AspectRatio;
}

void ERS_STRUCT_Camera::ProcessKeyboard(CameraMovement Direction, float DeltaTime) {

    // Calculate Velocity
    float Velocity = MovementSpeed_ * DeltaTime;

    // Update Position(s)
    if (Direction == FORWARD)
        Position_ += Front_ * Velocity;
    if (Direction == BACKWARD)
        Position_ -= Front_ * Velocity;
    if (Direction == LEFT)
        Position_ -= Right_ * Velocity;
    if (Direction == RIGHT)
        Position_ += Right_ * Velocity;
    if (Direction == UP)
        Position_ += glm::vec3(0.0f, 1.0f, 0.0f) * Velocity;
    if (Direction == DOWN)
        Position_ -= glm::vec3(0.0f, 1.0f, 0.0f) * Velocity;

}


void ERS_STRUCT_Camera::ProcessMouseMovement(float XOffset, float YOffset, GLboolean ConstrainPitch) {

    // Change Offset By Sensitivity
    XOffset *= MouseSensitivity_;
    YOffset *= MouseSensitivity_;

    // Update Pitch/Yaw
    Yaw_ += XOffset;
    Pitch_ -= YOffset;

    std::cout<<Pitch_<<"|"<<Yaw_<<std::endl;


    // Bound Pitch
    if (ConstrainPitch) {

        if (Pitch > 89.0f) {
            Pitch = 89.0f;
        }
        if (Pitch < -89.0f) {
            Pitch = -89.0f;
        }
    }

    // Update Front, Right, Up Vectors
    UpdateCameraVectors();

}


void ERS_STRUCT_Camera::ProcessMouseScroll(float YOffset) {

    // Update Movement Speed
    MovementSpeed_ += (MovementSpeed_*(float)YOffset/10.0f);

    // Adjust Movement Speed
    if (MovementSpeed_ < MinMovementSpeed_)
        MovementSpeed_ = MinMovementSpeed_;
    if (MovementSpeed_ > MaxMovementSpeed_)
        MovementSpeed_ = MaxMovementSpeed_;

    // Update Vectors
    //UpdateCameraVectors();


}

void ERS_STRUCT_Camera::UpdateCameraVectors() {
    
    // Calculate New Front Vector
    glm::vec3 NewFront;
    NewFront.x = cos(glm::radians(Yaw_)) * cos(glm::radians(Pitch_));
    NewFront.y = sin(glm::radians(Pitch));
    NewFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(NewFront);

    // Calculate Right, Up Vector
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));

}
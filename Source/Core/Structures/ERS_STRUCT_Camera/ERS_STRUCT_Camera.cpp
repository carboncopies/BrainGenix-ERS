//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_STRUCT_Camera.h>
#include <iostream>

//fixme: implement support for roll in the camera, currently it ignores this./
// suspects include GetViewMatrix or GetProjectionMatrix. These might be ignoring this, try googling it?

glm::mat4 ERS_STRUCT_Camera::GetViewMatrix() {
    return glm::lookAt(Position_, Position_ + Front_, Up_);
}

glm::mat4 ERS_STRUCT_Camera::GetProjectionMatrix() {
    return glm::perspective(glm::radians(FOV_), AspectRatio_, 0.01f, 100.0f);
}

void ERS_STRUCT_Camera::Rotate(glm::vec3 Rotation) {

    Yaw_ = Rotation.x;
    Pitch_ = Rotation.y;
    Roll_ = Rotation.z;

    glm::mat4 RotMatrix;
    RotMatrix = glm::rotate(RotMatrix, glm::radians(Rotation[0]), glm::vec3(1, 0, 0));
    RotMatrix = glm::rotate(RotMatrix, glm::radians(Rotation[1]), glm::vec3(0, 1, 0));
    RotMatrix = glm::rotate(RotMatrix, glm::radians(Rotation[2]), glm::vec3(0, 0, 1));
    Front_ = glm::normalize(glm::vec3(RotMatrix[2]));

    // Calculate Right, Up Vector
    Right_ = glm::normalize(glm::cross(Front_, WorldUp_));
    Up_ = glm::normalize(glm::cross(Right_, Front_));
    
    glm::mat4 roll_mat = glm::rotate(glm::mat4(1.0f), glm::radians(Roll_), Front_);
    Up_ = glm::mat3(roll_mat) * Up_;
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



    // Bound Pitch
    if (ConstrainPitch) {

        if (Pitch_ > 89.0f) {
            Pitch_ = 89.0f;
        }
        if (Pitch_ < -89.0f) {
            Pitch_ = -89.0f;
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
    NewFront.y = sin(glm::radians(Pitch_));
    NewFront.z = sin(glm::radians(Yaw_)) * cos(glm::radians(Pitch_));
    Front_ = glm::normalize(NewFront);

    // Calculate Right, Up Vector
    Right_ = glm::normalize(glm::cross(Front_, WorldUp_));

    Up_ = glm::normalize(glm::cross(Right_, Front_));

    glm::mat4 roll_mat = glm::rotate(glm::mat4(1.0f), glm::radians(Roll_), Front_);
    Up_ = glm::mat3(roll_mat) * Up_;

}
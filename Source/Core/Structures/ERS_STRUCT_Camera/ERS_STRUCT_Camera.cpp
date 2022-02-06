//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_STRUCT_Camera.h>

glm::mat4 ERS_STRUCT_Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 ERS_STRUCT_Camera::GetProjectionMatrix() {
    return glm::perspective(glm::radians(Zoom), AspectRatio_, 0.1f, 100.0f);
}


void ERS_STRUCT_Camera::SetAspectRatio(float AspectRatio) {
    AspectRatio_ = AspectRatio;
}

void ERS_STRUCT_Camera::ProcessKeyboard(CameraMovement Direction, float DeltaTime) {

    // Calculate Velocity
    float Velocity = MovementSpeed * DeltaTime;

    // Update Position(s)
    if (Direction == FORWARD)
        Position += Front * Velocity;
    if (Direction == BACKWARD)
        Position -= Front * Velocity;
    if (Direction == LEFT)
        Position -= Right * Velocity;
    if (Direction == RIGHT)
        Position += Right * Velocity;
    if (Direction == UP)
        Position += glm::vec3(0.0f, 1.0f, 0.0f) * Velocity;
    if (Direction == DOWN)
        Position -= glm::vec3(0.0f, 1.0f, 0.0f) * Velocity;

}


void ERS_STRUCT_Camera::ProcessMouseMovement(float XOffset, float YOffset, GLboolean ConstrainPitch) {

    // Change Offset By Sensitivity
    XOffset *= MouseSensitivity;
    YOffset *= MouseSensitivity;

    // Update Pitch/Yaw
    Yaw += XOffset;
    Pitch -= YOffset;

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
    MovementSpeed += (MovementSpeed*(float)YOffset/10.0f);

    // Adjust Movement Speed
    if (MovementSpeed < MinMovementSpeed)
        MovementSpeed = MinMovementSpeed;
    if (MovementSpeed > MaxMovementSpeed)
        MovementSpeed = MaxMovementSpeed;

    // Update Vectors
    //UpdateCameraVectors();


}

void ERS_STRUCT_Camera::UpdateCameraVectors() {
    
    // Calculate New Front Vector
    glm::vec3 NewFront;
    NewFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    NewFront.y = sin(glm::radians(Pitch));
    NewFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(NewFront);

    // Calculate Right, Up Vector
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));

}
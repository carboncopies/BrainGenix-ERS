//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_STRUCT_EditorCamera.h>


// Constructor/Destructor
ERS_STRUCT_EditorCamera::ERS_STRUCT_EditorCamera() {
}
ERS_STRUCT_EditorCamera::~ERS_STRUCT_EditorCamera() {

}


// Setup
void ERS_STRUCT_EditorCamera::SetupCamera(ERS_STRUCT_Camera* Camera) {
    Camera_ = Camera;
    HasCameraAttached_ = true;
}


// Callbacks
void ERS_STRUCT_EditorCamera::ProcessKeyboard(CameraMovement Direction, float DeltaTime) {

    // Exit Early If Camera Not Setup Yet
    if (!HasCameraAttached_) {
        return;
    }


    // Calculate Movement Direction Vectors
    glm::mat4 Perspective, ViewMatrix;
    glm::vec3 Right, Front, Up;
    Camera_->GetMatrices(Perspective, ViewMatrix);
    Right  =  glm::normalize(glm::vec3(ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]));
    Up     =  glm::normalize(glm::vec3(ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]));
    Front  = -glm::normalize(glm::vec3(ViewMatrix[0][2], ViewMatrix[1][2], ViewMatrix[2][2]));

    // Calculate Velocity
    float Velocity = MovementSpeed_ * DeltaTime;

    // Update Position(s)
    if (Direction == FORWARD)
        Position_ += Front  * Velocity;
    if (Direction == BACKWARD)
        Position_ -= Front  * Velocity;
    if (Direction == LEFT)
        Position_ -= Right  * Velocity;
    if (Direction == RIGHT)
        Position_ += Right  * Velocity;
    if (Direction == UP)
        Position_ += Up     * Velocity;
    if (Direction == DOWN)
        Position_ -= Up     * Velocity;

}
void ERS_STRUCT_EditorCamera::ProcessMouseMovement(float XOffset, float YOffset, GLboolean ConstrainPitch) {

    // Change Offset By Sensitivity
    XOffset *= MouseSensitivity_;
    YOffset *= MouseSensitivity_;

    // Update Pitch/Yaw
    Orientation_.y += XOffset;
    Orientation_.p += YOffset;



    // Bound Pitch
    if (ConstrainPitch) {

        if (Orientation_.p > 89.0f) {
            Orientation_.p = 89.0f;
        }
        if (Orientation_.p < -89.0f) {
            Orientation_.p = -89.0f;
        }
    }

}
void ERS_STRUCT_EditorCamera::ProcessMouseScroll(float YOffset) {

    // Update Movement Speed
    MovementSpeed_ += (MovementSpeed_*(float)YOffset/10.0f);

    // Adjust Movement Speed
    if (MovementSpeed_ < MinMovementSpeed_)
        MovementSpeed_ = MinMovementSpeed_;
    if (MovementSpeed_ > MaxMovementSpeed_)
        MovementSpeed_ = MaxMovementSpeed_;

}


// Update Matricies
void ERS_STRUCT_EditorCamera::Update() {

    Camera_->SetPosition(Position_);
    Camera_->SetRotation(Orientation_);

}


// Camera Parameter Helper Functions
void ERS_STRUCT_EditorCamera::SetMovementSpeedBoundries(float MinSpeed, float MaxSpeed) {
    MinMovementSpeed_ = MinSpeed;
    MaxMovementSpeed_ = MaxSpeed;
}
void ERS_STRUCT_EditorCamera::GetMovementSpeedBoundries(float &MinSpeed, float &MaxSpeed) {
    MinSpeed = MinMovementSpeed_;
    MaxSpeed = MaxMovementSpeed_;
}
void ERS_STRUCT_EditorCamera::SetMovementSpeed(float Speed, bool EnforceSpeedBoundries) {
    if (EnforceSpeedBoundries) {
        Speed = std::max(MinMovementSpeed_, Speed);
        Speed = std::min(MaxMovementSpeed_, Speed);
        MovementSpeed_ = Speed;
    } else {
        MovementSpeed_ = Speed;
    }
}
void ERS_STRUCT_EditorCamera::GetMouseSensitivity(float &Sensitivity) {
    Sensitivity = MouseSensitivity_;
}
void ERS_STRUCT_EditorCamera::SetMouseSensitivity(float Sensitivity) {
    MouseSensitivity_ = Sensitivity;
}
void ERS_STRUCT_EditorCamera::SetRotation(glm::vec3 Rotation) {
    Orientation_ = Rotation;
}
void ERS_STRUCT_EditorCamera::GetRotation(glm::vec3 &Rotation) {
    Rotation = Orientation_;
}
glm::vec3 ERS_STRUCT_EditorCamera::GetRotation() {
    return Orientation_;
}
void ERS_STRUCT_EditorCamera::SetPosition(glm::vec3 Position) {
    Position_ = Position;
}
void ERS_STRUCT_EditorCamera::GetPosition(glm::vec3 &Position) {
    Position = Position_;
}
glm::vec3 ERS_STRUCT_EditorCamera::GetPosition() {
    return Position_;
}

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
        Position_ += Up_ * Velocity;
    if (Direction == DOWN)
        Position_ -= Up_ * Velocity;

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
    
    // Recalculate Orientation Quat
    glm::quat QuatOrientation;
    QuatOrientation *= glm::angleAxis(glm::radians(Orientation_.r), glm::vec3(0, 0, 1) * QuatOrientation);
    QuatOrientation *= glm::angleAxis(glm::radians(Orientation_.y), glm::vec3(0, 1, 0) * QuatOrientation);
    QuatOrientation *= glm::angleAxis(glm::radians(Orientation_.p), glm::vec3(1, 0, 0) * QuatOrientation);
    QuatOrientation = glm::normalize(QuatOrientation);

    // Update Matricies
    PerspectiveMatrix_          = glm::perspective(glm::radians(FOV_), AspectRatio_, NearClip_, FarClip_);	
    glm::mat4 RotationMatrix    = glm::mat4_cast(QuatOrientation);
    glm::mat4 TranslationMatrix = glm::mat4(1.0f);
    TranslationMatrix           = glm::translate(TranslationMatrix, -Position_);
    ViewMatrix_                 = RotationMatrix * TranslationMatrix;

    // Calculate Movement Direction Vectors
    Right_  =  glm::normalize(glm::vec3(ViewMatrix_[0][0], ViewMatrix_[1][0], ViewMatrix_[2][0]));
    Up_     =  glm::normalize(glm::vec3(ViewMatrix_[0][1], ViewMatrix_[1][1], ViewMatrix_[2][1]));
    Front_  = -glm::normalize(glm::vec3(ViewMatrix_[0][2], ViewMatrix_[1][2], ViewMatrix_[2][2]));
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

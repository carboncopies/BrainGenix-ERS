//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_STRUCT_Camera.h>
#include <iostream>



ERS_STRUCT_Camera::ERS_STRUCT_Camera(glm::vec3 Position) {
    Position_ = Position;
}

ERS_STRUCT_Camera::~ERS_STRUCT_Camera() {

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
        Position_ += Up_ * Velocity;
    if (Direction == DOWN)
        Position_ -= Up_ * Velocity;

}


void ERS_STRUCT_Camera::ProcessMouseMovement(float XOffset, float YOffset, GLboolean ConstrainPitch) {

    // Change Offset By Sensitivity
    XOffset *= MouseSensitivity_;
    YOffset *= MouseSensitivity_;

    // Update Pitch/Yaw
    Orientation_.y   += XOffset;
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


void ERS_STRUCT_Camera::ProcessMouseScroll(float YOffset) {

    // Update Movement Speed
    MovementSpeed_ += (MovementSpeed_*(float)YOffset/10.0f);

    // Adjust Movement Speed
    if (MovementSpeed_ < MinMovementSpeed_)
        MovementSpeed_ = MinMovementSpeed_;
    if (MovementSpeed_ > MaxMovementSpeed_)
        MovementSpeed_ = MaxMovementSpeed_;

}

void ERS_STRUCT_Camera::Update() {
    
    // Recalculate Orientation Quat
    glm::quat QuatPitch  = glm::angleAxis(glm::radians(Orientation_.p), glm::vec3(1, 0, 0));
    glm::quat QuatYaw    = glm::angleAxis(glm::radians(Orientation_.y), glm::vec3(0, 1, 0));
    glm::quat QuatRoll   = glm::angleAxis(glm::radians(Orientation_.r), glm::vec3(0, 0, 1));
    glm::quat QuatOrientation = QuatPitch * QuatYaw * QuatRoll;
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
    Front_  = -glm::normalize(glm::cross(Right_, Up_));//-glm::normalize(glm::vec3(ViewMatrix_[0][2], ViewMatrix_[1][2], ViewMatrix_[2][2]));
}




void ERS_STRUCT_Camera::GetMatrices(glm::mat4& Perspective, glm::mat4& View){
    Perspective = PerspectiveMatrix_;
    View = ViewMatrix_;
}


// Camera Parameter Helper Functions
void ERS_STRUCT_Camera::SetClipBoundries(float NearClip, float FarClip) {
    NearClip_ = NearClip;
    FarClip_ = FarClip;
}
void ERS_STRUCT_Camera::GetClipBoundires(float &NearClip, float &FarClip) {
    NearClip = NearClip_;
    FarClip = FarClip_;
}
void ERS_STRUCT_Camera::SetMovementSpeedBoundries(float MinSpeed, float MaxSpeed) {
    MinMovementSpeed_ = MinSpeed;
    MaxMovementSpeed_ = MaxSpeed;
}
void ERS_STRUCT_Camera::GetMovementSpeedBoundries(float &MinSpeed, float &MaxSpeed) {
    MinSpeed = MinMovementSpeed_;
    MaxSpeed = MaxMovementSpeed_;
}
void ERS_STRUCT_Camera::SetMovementSpeed(float Speed, bool EnforceSpeedBoundries) {
    if (EnforceSpeedBoundries) {
        Speed = std::max(MinMovementSpeed_, Speed);
        Speed = std::min(MaxMovementSpeed_, Speed);
        MovementSpeed_ = Speed;
    } else {
        MovementSpeed_ = Speed;
    }
}
void ERS_STRUCT_Camera::SetFOV(float FOV) {
    FOV_ = FOV;
}
void ERS_STRUCT_Camera::GetFOV(float &FOV) {
    FOV = FOV_;
}
void ERS_STRUCT_Camera::GetMouseSensitivity(float &Sensitivity) {
    Sensitivity = MouseSensitivity_;
}
void ERS_STRUCT_Camera::SetMouseSensitivity(float Sensitivity) {
    MouseSensitivity_ = Sensitivity;
}
void ERS_STRUCT_Camera::SetRotation(glm::vec3 Rotation) {
    Orientation_ = Rotation;
}
void ERS_STRUCT_Camera::GetRotation(glm::vec3 &Rotation) {
    Rotation = Orientation_;
}
void ERS_STRUCT_Camera::SetPosition(glm::vec3 Position) {
    Position_ = Position;
}
void ERS_STRUCT_Camera::GetPosition(glm::vec3 &Position) {
    Position = Position_;
}
glm::vec3 ERS_STRUCT_Camera::GetPosition() {
    return Position_;
}
void ERS_STRUCT_Camera::GetStreamingPriority(int &StreamingPriority) {
    StreamingPriority = StreamingPriority_;
}
int ERS_STRUCT_Camera::GetStreamingPriority() {
    return StreamingPriority_;
}
void ERS_STRUCT_Camera::SetStreamingPriority(int StreamingPriority) {
    StreamingPriority_ = StreamingPriority;
}

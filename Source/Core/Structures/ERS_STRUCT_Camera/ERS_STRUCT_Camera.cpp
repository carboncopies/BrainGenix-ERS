//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_STRUCT_Camera.h>
#include <iostream>

//fixme: implement support for roll in the camera, currently it ignores this./
// suspects include GetViewMatrix or GetProjectionMatrix. These might be ignoring this, try googling it?





//todo: rever tto old camera system, try using the quaternion stuff learned from this system.




// // ctor
// ERS_STRUCT_Camera::ERS_STRUCT_Camera(float fov,  int width, int height, float nearClip, float farClip)  
// 	: ERS_STRUCT_Camera(fov, width, height, nearClip, farClip, glm::vec3(0.0f, 0.0f, 1.0f))
// {}
// ERS_STRUCT_Camera::ERS_STRUCT_Camera(float fov, int width, int height, float nearClip, float farClip, glm::vec3 Position)
// 	: FOV_(fov), zoom(fov), AspectRatio_(float(width)/float(height)), NearClip_(nearClip), FarClip_(farClip), Position_(Position){
	
// 	PerspectiveMatrix_ = glm::perspective(FOV_, AspectRatio_, nearClip, farClip);
// 	mousePosition.x = width / 2.0f;
// 	mousePosition.y = height / 2.0f;
// }
// ERS_STRUCT_Camera::ERS_STRUCT_Camera(glm::vec3 Position) {
//     ERS_STRUCT_Camera(70.0f, 128, 128, 0.01f, 100.0f, Position);
// }

// void ERS_STRUCT_Camera::Update(){		

    

//     orientation = glm::quat();

// 	if(Pitch_ != 0.0f)		Rotate(Pitch_, xAxis);
// 	if(Yaw_ != 0.0f)			Rotate(Yaw_, yAxis);
// 	if(Roll_ != 0.0f)		Rotate(Roll_, zAxis);
// 	//
// 	// //// instead of setting to zero immediately, we have the value eventually go to zero.
// 	// Pitch_	*= damp;
// 	// Yaw_		*= damp;
// 	// Roll_	*= rollDamp;


// 	PerspectiveMatrix_ = glm::perspective(FOV_, AspectRatio_, NearClip_, FarClip_);	
// 	ViewMatrix_ = glm::translate(glm::mat4_cast(orientation), Position_);;


// }


// void ERS_STRUCT_Camera::Rotate(float angle, const glm::vec3 &axis){
// 	orientation *= glm::angleAxis(glm::radians(angle), axis * orientation);
// }

// void ERS_STRUCT_Camera::SetRotation(glm::vec3 Rotation) {
//     Yaw_ = Rotation[0];
//     Pitch_ = Rotation[1];
//     Roll_ = Rotation[2];
// }

// void ERS_STRUCT_Camera::ProcessKeyboard(CameraMovement td, float DeltaTime){


// 	// basically, translating the Position_ vector
//     float Velocity = MovementSpeed_ * DeltaTime;

// 	glm::vec3 temp;
// 	switch(td){
// 		case CameraMovement::UP:
// 			Position_ -= glm::vec3(0.0f, Velocity, 0.0f) * orientation;
// 			break;
// 		case CameraMovement::DOWN:
// 			Position_ += glm::vec3(0.0f, Velocity, 0.0f) * orientation;
// 			break;
// 		case CameraMovement::LEFT:
// 			Position_ += glm::vec3(Velocity, 0.0f, 0.0f) * orientation;
// 			break;
// 		case CameraMovement::RIGHT:
// 			Position_ -= glm::vec3(Velocity, 0.0f, 0.0f) * orientation;
// 			break;
// 		case CameraMovement::FORWARD:
// 			Position_ += glm::vec3(0.0f, 0.0f, Velocity) * orientation;
// 			break;
// 		case CameraMovement::BACKWARD:
// 			Position_ -= glm::vec3(0.0f, 0.0f, Velocity) * orientation;
// 			break;
// 	}
// }

// void ERS_STRUCT_Camera::ProcessMouseMovement(float XOffset, float YOffset){
// 	// // updateing yaw
// 	// Yaw_ += (XOffset - mousePosition.x) * mouseSenstivitiy;
// 	// if(Yaw_ > twoPI) Yaw_ -= twoPI;
// 	// else if(Yaw_ < -twoPI) Yaw_ += twoPI;

// 	// // updateing Pitch_
// 	// Pitch_ += (YOffset - mousePosition.y) * mouseSenstivitiy;
// 	// if(Pitch_ > twoPI) Pitch_ -= twoPI;
// 	// else if(Pitch_ < -twoPI) Pitch_ += twoPI;


//     // Change Offset By Sensitivity
//     XOffset *= 0.1f;
//     YOffset *= 0.1f;

//     // Update Pitch/Yaw
//     Yaw_ += XOffset;
//     Pitch_ -= YOffset;


// 	mousePosition.x = XOffset;
// 	mousePosition.y = YOffset;


// }

// void ERS_STRUCT_Camera::ProcessMouseScroll(float YOffset){
// 	Roll_ -= YOffset * ROLL_ANGLE;	
// 	if(Roll_ > twoPI) Roll_ -= twoPI;
// 	else if(Roll_ < -twoPI) Roll_ += twoPI;
// }

// void ERS_STRUCT_Camera::Zoom(ZoomState z){
// 	// bool recalculatePerspective = true;
// 	// switch(z){
// 	// 	case ZoomState::_IN:
// 	// 		if((zoom -= zoomDelta) < 0){ 
// 	// 			zoom = 0;
// 	// 			recalculatePerspective = false;
// 	// 		}
// 	// 		break;
// 	// 	case ZoomState::_OUT:
// 	// 		if((zoom += zoomDelta) > FOV_){
// 	// 			zoom = FOV_;
// 	// 			recalculatePerspective = false;
// 	// 		}
// 	// 		break;
// 	// }
// 	// if(recalculatePerspective) PerspectiveMatrix_ = glm::perspective(zoom, aspect, nearClip, farClip);
// }

// void ERS_STRUCT_Camera::SetAspectRatio(float AspectRatio){ 
// 	AspectRatio_ = AspectRatio; 
// 	PerspectiveMatrix_ = glm::perspective(FOV_, AspectRatio, NearClip_, FarClip_);
// }


// // // ideally you want to set the mouse Position_ to the center of the scene
// // void ERS_STRUCT_Camera::SetMousePosition(float x, float y){ 
// // 	mousePosition.x = x;
// // 	mousePosition.y = y;
// // }

// void ERS_STRUCT_Camera::GetMatrices(glm::mat4& perspective, glm::mat4& view){
// 	// perspective = PerspectiveMatrix_;	
// 	// view = glm::translate(glm::mat4_cast(orientation), Position_);;
//     //Update();
//     perspective = PerspectiveMatrix_;
//     view = ViewMatrix_; 

// }

// // void ERS_STRUCT_Camera::GetDirectionVectors(glm::vec3 &Front, glm::vec3 &Right, glm::vec3 &Up) {

// //     // glm::mat4 RotMatrix;
// //     // RotMatrix = glm::rotate(RotMatrix, glm::radians(Rotation[0]), glm::vec3(1, 0, 0));
// //     // RotMatrix = glm::rotate(RotMatrix, glm::radians(Rotation[1]), glm::vec3(0, 1, 0));
// //     // RotMatrix = glm::rotate(RotMatrix, glm::radians(Rotation[2]), glm::vec3(0, 0, 1));
// //     // Front_ = glm::normalize(glm::vec3(RotMatrix[2]));

// //     // // Calculate Right, Up Vector
// //     // Right_ = glm::normalize(glm::cross(Front_, WorldUp_));
// //     // Up_ = glm::normalize(glm::cross(Right_, Front_));

// // }
























// glm::mat4 ERS_STRUCT_Camera::GetViewMatrix() {
//     glm::mat4 Output = glm::lookAt(Position_, Position_ + Front_, Up_);
//     std::cout<<glm::to_string(Output)<<std::endl;

//     return Output;
// }

// glm::mat4 ERS_STRUCT_Camera::GetProjectionMatrix() {
//     return glm::perspective(glm::radians(FOV_), AspectRatio_, 0.01f, 100.0f);
// }

// void ERS_STRUCT_Camera::Rotate(glm::vec3 Rotation) {


//     UpdateCamera();

//     // glm::mat4 RotMatrix;
//     // RotMatrix = glm::rotate(RotMatrix, glm::radians(Rotation[0]), glm::vec3(1, 0, 0));
//     // RotMatrix = glm::rotate(RotMatrix, glm::radians(Rotation[1]), glm::vec3(0, 1, 0));
//     // RotMatrix = glm::rotate(RotMatrix, glm::radians(Rotation[2]), glm::vec3(0, 0, 1));
//     // Front_ = glm::normalize(glm::vec3(RotMatrix[2]));

//     // // Calculate Right, Up Vector
//     // Right_ = glm::normalize(glm::cross(Front_, WorldUp_));
//     // Up_ = glm::normalize(glm::cross(Right_, Front_));
    
//     // glm::mat4 roll_mat = glm::rotate(glm::mat4(1.0f), glm::radians(Roll_), Front_);
//     // Up_ = glm::mat3(roll_mat) * Up_;
// }


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
    Rotation_.x += XOffset;
    Rotation_.y -= YOffset;



    // Bound Pitch
    if (ConstrainPitch) {

        if (Rotation_.y > 89.0f) {
            Rotation_.y = 89.0f;
        }
        if (Rotation_.y < -89.0f) {
            Rotation_.y = -89.0f;
        }
    }


    // Update Front, Right, Up Vectors
    Update();

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
    Rotate(Rotation_);

    // Update Matricies
    PerspectiveMatrix_ = glm::perspective(FOV_, AspectRatio_, NearClip_, FarClip_);	
 	ViewMatrix_ = glm::translate(glm::mat4_cast(Orientation_), Position_);;

    // Calculate Movement Direction Vectors
    Front_ = glm::vec3();
    Front_.x = cos(glm::radians(Rotation_.x)) * cos(glm::radians(Rotation_.y));
    Front_.y = sin(glm::radians(Rotation_.y));
    Front_.z = sin(glm::radians(Rotation_.x)) * cos(glm::radians(Rotation_.y));
    Front_ = glm::normalize(Front_);

    Right_ = glm::normalize(glm::cross(Front_, WorldUp_));
    Up_ = glm::normalize(glm::cross(Right_, Front_));

    glm::mat4 roll_mat = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation_.z), Front_);
    Up_ = glm::mat3(roll_mat) * Up_;

}

void ERS_STRUCT_Camera::Rotate(float Angle, glm::vec3 Axis) {
	Orientation_ *= glm::angleAxis(glm::radians(Angle), Axis * Orientation_);
}

void ERS_STRUCT_Camera::Rotate(glm::vec3 Rotation) {
    Orientation_ = glm::quat();
    Rotate(Rotation.x, glm::vec3(1, 0, 0));
    Rotate(Rotation.y, glm::vec3(0, 1, 0));
    Rotate(Rotation.z, glm::vec3(0, 0, 1));
}

void ERS_STRUCT_Camera::SetRotation(glm::vec3 Rotation) {
    Rotation_ = Rotation;
}

void ERS_STRUCT_Camera::GetMatrices(glm::mat4& Perspective, glm::mat4& View){
    Perspective = PerspectiveMatrix_;
    View = ViewMatrix_;
}

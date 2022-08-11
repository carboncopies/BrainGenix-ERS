//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#define GLM_FORCE_RADIANS	
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>





// FOV zooming
enum class ZoomState{
	_IN, _OUT
};

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};


// // Setup Camera Options
// class ERS_STRUCT_Camera_old {

// public:

//     // Camera Attributes
//     glm::vec3 Position_;
//     glm::vec3 Front_;
//     glm::vec3 Up_;
//     glm::vec3 Right_;
//     glm::vec3 WorldUp_;

//     // Asset Streaming Config
//     int Priority_ = 1; // Higher this is, the more the system will try and load assets for this camera. Should be in range (1-10)

//     glm::quat Orientation_; 

//     // Camera Options
//     double MovementSpeed_;
//     float MouseSensitivity_;
//     float FOV_;
//     float AspectRatio_;

//     // Config Params
//     float MinMovementSpeed_ = 0.0f;
//     float MaxMovementSpeed_ = 50.0f;

//     // Constructor With Vectors
//     ERS_STRUCT_Camera_old(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f),
//                                 glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f),
//                                 float Yaw = -90.0f,
//                                 float Pitch = 0.0f) : Front_(glm::vec3(0.0f, 0.0f, -1.0f)),
//                                 MovementSpeed_(1.0f),
//                                 MouseSensitivity_(0.1f),
//                                 FOV_(45.0f) {
        
//         // Set Params
//         Position = Position;
//         WorldUp_ = Up;
//         UpdateCameraVectors();
        
//     }


//     // Return View Matrix
//     glm::mat4 GetViewMatrix();
//     glm::mat4 GetProjectionMatrix();


//     // Proces Keyboard Input
//     void ProcessKeyboard(CameraMovement Direction, float DeltaTime);

//     // Process Mouse Input
//     void ProcessMouseMovement(float XOffset, float Yoffset, GLboolean ConstrainPitch = true);
//     void ProcessMouseScroll(float YOffset);

//     void SetAspectRatio(float AspectRatio);
//     void Rotate(glm::vec3 Rotation);

// private:

//     void UpdateCameraVectors();


// };








struct ERS_STRUCT_Camera {
    private:
		void Rotate(float angle, const glm::vec3 &axis);

	public:

        // Asset Streaming Config
        int Priority_ = 1; // Higher this is, the more the system will try and load assets for this camera. Should be in range (1-10)

		float FOV_;
		float zoom;
		float zoomDelta	= glm::radians(1.0f);	

		float aspect;
		float nearClip;
		float farClip;

		glm::vec3 Position_;
				
		glm::quat orientation;					// store rotation and orientation data

		glm::vec3 mousePosition;				// use to calculate the yaw and pitch rotation. 
		float mouseSenstivitiy	= 0.0009f;		// slow down the rate in which the camera rotate

		// play around with those two values until you get a roll speed that you like.
		const float ROLL_ANGLE	= 0.009f;		// we're using this because roll depends on the mouse scroll.
		float rollDamp			= 0.95f;		// we're using this because roll depends on the mouse scroll.
		
		float damp				= 0.8f;			// a value to damp the camera rotational speed

		// the angles to rotate the camera by.
		float Yaw_	= 0.0f;						// rotate about the y axis
		float Pitch_	= 0.0f;						// rotate about the x axis
		float Roll_	= 0.0f;						// rotate about the z axis
		float twoPI = glm::two_pi<float>();		// check radian bound

		float MovementSpeed_ = 0.2f;			// the linear travel speed of the camera

		glm::mat4 perspectiveMatrix;
		//glm::mat4 viewMatrix;	
		
		glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);


		//ERS_STRUCT_Camera() = delete;

		///<param name="FOV">The vertical Field of View. In radians</param>
		///<param name="windowWidth">The width of the display window</param>
		///<param name="windowHeight">The height of the display window</param>
		///<param name="near">The near-clipping plane</param>
		///<param name="far">The far-clipping plane</param>
		///<param name="Position_">The Position_ of the camera</param>
		ERS_STRUCT_Camera(float fov, int width, int height, float near, float far);
		ERS_STRUCT_Camera(float fov, int width, int height, float near, float far, glm::vec3 Position);
        ERS_STRUCT_Camera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f));
		
	
        // Done
		void ProcessKeyboard(CameraMovement Direction, float DeltaTime);
		void ProcessMouseMovement(float XOffset, float YOffset, GLboolean ConstrainPitch = true);		// control pitch and yaw
		void ProcessMouseScroll(float YOffset);		// control Roll_
        void Rotate(glm::vec3 Rotation);
		void SetAspectRatio(float AspectRatio);

        // Todo
		void Update(float delta = 1.0f);
		void Zoom(ZoomState z);		


		void SetMousePosition(float x, float y);
		void GetMatrices(glm::mat4& perspective, glm::mat4& view);
        //void GetDirectionVectors(glm::vec3 &Front, glm::vec3 &Right, glm::vec3 &Up);

};


// ctor
ERS_STRUCT_Camera::ERS_STRUCT_Camera(float fov,  int width, int height, float nearClip, float farClip)  
	: ERS_STRUCT_Camera(fov, width, height, nearClip, farClip, glm::vec3(0.0f, 0.0f, 1.0f))
{}
ERS_STRUCT_Camera::ERS_STRUCT_Camera(float fov, int width, int height, float nearClip, float farClip, glm::vec3 Position)
	: FOV_(fov), zoom(fov), aspect(float(width)/float(height)), nearClip(nearClip), farClip(farClip), Position_(Position){
	
	perspectiveMatrix = glm::perspective(FOV_, aspect, nearClip, farClip);
	mousePosition.x = width / 2.0f;
	mousePosition.y = height / 2.0f;
}
ERS_STRUCT_Camera::ERS_STRUCT_Camera(glm::vec3 Position) {
    ERS_STRUCT_Camera(70.0f, 128, 128, 0.01f, 100.0f, Position);
}

void ERS_STRUCT_Camera::Update(float delta){		
	if(Pitch_ != 0.0f)		Rotate(Pitch_, xAxis);
	if(Yaw_ != 0.0f)			Rotate(Yaw_, yAxis);
	if(Roll_ != 0.0f)		Rotate(Roll_, zAxis);
	//
	//// instead of setting to zero immediately, we have the value eventually go to zero.
	Pitch_	*= damp;
	Yaw_		*= damp;
	Roll_	*= rollDamp;
}


void ERS_STRUCT_Camera::Rotate(float angle, const glm::vec3 &axis){
	orientation *= glm::angleAxis(angle, axis * orientation);
}

void ERS_STRUCT_Camera::Rotate(glm::vec3 Rotation) {
    Rotate(Rotation[0], glm::vec3(1, 0, 0));
    Yaw_ = Rotation[0];
    Rotate(Rotation[1], glm::vec3(0, 1, 0));
    Pitch_ = Rotation[1];
    Rotate(Rotation[2], glm::vec3(0, 0, 1));
    Roll_ = Rotation[2];

}

void ERS_STRUCT_Camera::ProcessKeyboard(CameraMovement td, float DeltaTime){


	// basically, translating the Position_ vector
    float Velocity = MovementSpeed_ * DeltaTime;

	glm::vec3 temp;
	switch(td){
		case CameraMovement::UP:
			Position_ -= glm::vec3(0.0f, Velocity, 0.0f) * orientation;
			break;
		case CameraMovement::DOWN:
			Position_ += glm::vec3(0.0f, Velocity, 0.0f) * orientation;
			break;
		case CameraMovement::LEFT:
			Position_ += glm::vec3(Velocity, 0.0f, 0.0f) * orientation;
			break;
		case CameraMovement::RIGHT:
			Position_ -= glm::vec3(Velocity, 0.0f, 0.0f) * orientation;
			break;
		case CameraMovement::FORWARD:
			Position_ += glm::vec3(0.0f, 0.0f, Velocity) * orientation;
			break;
		case CameraMovement::BACKWARD:
			Position_ -= glm::vec3(0.0f, 0.0f, Velocity) * orientation;
			break;
	}
}

void ERS_STRUCT_Camera::ProcessMouseMovement(float XOffset, float YOffset, GLboolean ConstrainPitch){
	// updateing yaw
	Yaw_ += (XOffset - mousePosition.x) * mouseSenstivitiy;
	if(Yaw_ > twoPI) Yaw_ -= twoPI;
	else if(Yaw_ < -twoPI) Yaw_ += twoPI;

	// updateing Pitch_
	Pitch_ += (YOffset - mousePosition.y) * mouseSenstivitiy;
	if(Pitch_ > twoPI) Pitch_ -= twoPI;
	else if(Pitch_ < -twoPI) Pitch_ += twoPI;

	mousePosition.x = XOffset;
	mousePosition.y = YOffset;
}

void ERS_STRUCT_Camera::ProcessMouseScroll(float YOffset){
	Roll_ -= YOffset * ROLL_ANGLE;	
	if(Roll_ > twoPI) Roll_ -= twoPI;
	else if(Roll_ < -twoPI) Roll_ += twoPI;
}

void ERS_STRUCT_Camera::Zoom(ZoomState z){
	bool recalculatePerspective = true;
	switch(z){
		case ZoomState::_IN:
			if((zoom -= zoomDelta) < 0){ 
				zoom = 0;
				recalculatePerspective = false;
			}
			break;
		case ZoomState::_OUT:
			if((zoom += zoomDelta) > FOV_){
				zoom = FOV_;
				recalculatePerspective = false;
			}
			break;
	}
	if(recalculatePerspective) perspectiveMatrix = glm::perspective(zoom, aspect, nearClip, farClip);
}

void ERS_STRUCT_Camera::SetAspectRatio(float AspectRatio){ 
	this->aspect = AspectRatio; 
	perspectiveMatrix = glm::perspective(zoom, AspectRatio, nearClip, farClip);
}


// ideally you want to set the mouse Position_ to the center of the scene
void ERS_STRUCT_Camera::SetMousePosition(float x, float y){ 
	mousePosition.x = x;
	mousePosition.y = y;
}

void ERS_STRUCT_Camera::GetMatrices(glm::mat4& perspective, glm::mat4& view){
	perspective = perspectiveMatrix;	
	view = glm::translate(glm::mat4_cast(orientation), Position_);;
}

// void ERS_STRUCT_Camera::GetDirectionVectors(glm::vec3 &Front, glm::vec3 &Right, glm::vec3 &Up) {

//     // glm::mat4 RotMatrix;
//     // RotMatrix = glm::rotate(RotMatrix, glm::radians(Rotation[0]), glm::vec3(1, 0, 0));
//     // RotMatrix = glm::rotate(RotMatrix, glm::radians(Rotation[1]), glm::vec3(0, 1, 0));
//     // RotMatrix = glm::rotate(RotMatrix, glm::radians(Rotation[2]), glm::vec3(0, 0, 1));
//     // Front_ = glm::normalize(glm::vec3(RotMatrix[2]));

//     // // Calculate Right, Up Vector
//     // Right_ = glm::normalize(glm::cross(Front_, WorldUp_));
//     // Up_ = glm::normalize(glm::cross(Right_, Front_));

// }
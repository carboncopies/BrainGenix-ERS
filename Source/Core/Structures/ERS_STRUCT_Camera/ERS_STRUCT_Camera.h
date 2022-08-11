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


// Setup Camera Options
class ERS_STRUCT_Camera_old {

public:

    // Camera Attributes
    glm::vec3 Position_;
    glm::vec3 Front_;
    glm::vec3 Up_;
    glm::vec3 Right_;
    glm::vec3 WorldUp_;

    // Asset Streaming Config
    int Priority_ = 1; // Higher this is, the more the system will try and load assets for this camera. Should be in range (1-10)

    glm::quat Orientation_; 

    // Camera Options
    double MovementSpeed_;
    float MouseSensitivity_;
    float FOV_;
    float AspectRatio_;

    // Config Params
    float MinMovementSpeed_ = 0.0f;
    float MaxMovementSpeed_ = 50.0f;

    // Constructor With Vectors
    ERS_STRUCT_Camera_old(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f),
                                glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f),
                                float Yaw = -90.0f,
                                float Pitch = 0.0f) : Front_(glm::vec3(0.0f, 0.0f, -1.0f)),
                                MovementSpeed_(1.0f),
                                MouseSensitivity_(0.1f),
                                FOV_(45.0f) {
        
        // Set Params
        Position = Position;
        WorldUp_ = Up;
        UpdateCameraVectors();
        
    }


    // Return View Matrix
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();


    // Proces Keyboard Input
    void ProcessKeyboard(CameraMovement Direction, float DeltaTime);

    // Process Mouse Input
    void ProcessMouseMovement(float XOffset, float Yoffset, GLboolean ConstrainPitch = true);
    void ProcessMouseScroll(float YOffset);

    void SetAspectRatio(float AspectRatio);
    void Rotate(glm::vec3 Rotation);

private:

    void UpdateCameraVectors();


};








struct ERS_STRUCT_Camera {
	public:

        // Asset Streaming Config
        int Priority_ = 1; // Higher this is, the more the system will try and load assets for this camera. Should be in range (1-10)

		float FOV;
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
		float yaw	= 0.0f;						// rotate about the y axis
		float pitch	= 0.0f;						// rotate about the x axis
		float roll	= 0.0f;						// rotate about the z axis
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
		ERS_STRUCT_Camera(float fov, int width, int height, float near, float far, glm::vec3 Position_);
		
	
        // Done
		void ProcessKeyboard(CameraMovement Direction, float DeltaTime);
		void ProcessMouseMovement(float XOffset, float YOffset, GLboolean ConstrainPitch = true);		// control pitch and yaw
		void ProcessMouseScroll(float YOffset);		// control roll
		void Rotate(float angle, const glm::vec3 &axis);
        void Rotate(glm::vec3 Rotation);
		void SetAspectRatio(float AspectRatio);

        // Todo
		void Update(float delta = 1.0f);
		void Zoom(ZoomState z);		


		void SetMousePosition(float x, float y);
		void GetMatrices(glm::mat4& perspective, glm::mat4& view);

};


// ctor
ERS_STRUCT_Camera::ERS_STRUCT_Camera(float fov,  int width, int height, float nearClip, float farClip)  
	: ERS_STRUCT_Camera(fov, width, height, nearClip, farClip, glm::vec3(0.0f, 0.0f, 1.0f))
{}
ERS_STRUCT_Camera::ERS_STRUCT_Camera(float fov, int width, int height, float nearClip, float farClip, glm::vec3 Position_)
	: FOV(fov), zoom(fov), aspect(float(width)/float(height)), nearClip(nearClip), farClip(farClip), Position_(Position_){
	
	perspectiveMatrix = glm::perspective(FOV, aspect, nearClip, farClip);
	mousePosition.x = width / 2.0f;
	mousePosition.y = height / 2.0f;
}

void ERS_STRUCT_Camera::Update(float delta){		
	if(pitch != 0.0f)		Rotate(pitch, xAxis);
	if(yaw != 0.0f)			Rotate(yaw, yAxis);
	if(roll != 0.0f)		Rotate(roll, zAxis);
	//
	//// instead of setting to zero immediately, we have the value eventually go to zero.
	pitch	*= damp;
	yaw		*= damp;
	roll	*= rollDamp;
}


void ERS_STRUCT_Camera::Rotate(float angle, const glm::vec3 &axis){
	orientation *= glm::angleAxis(angle, axis * orientation);
}

void ERS_STRUCT_Camera::Rotate(glm::vec3 Rotation) {
    Rotate(Rotation[0], glm::vec3(1, 0, 0));
    Rotate(Rotation[1], glm::vec3(0, 1, 0));
    Rotate(Rotation[2], glm::vec3(0, 0, 1));
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
	yaw += (XOffset - mousePosition.x) * mouseSenstivitiy;
	if(yaw > twoPI) yaw -= twoPI;
	else if(yaw < -twoPI) yaw += twoPI;

	// updateing pitch
	pitch += (YOffset - mousePosition.y) * mouseSenstivitiy;
	if(pitch > twoPI) pitch -= twoPI;
	else if(pitch < -twoPI) pitch += twoPI;

	mousePosition.x = XOffset;
	mousePosition.y = YOffset;
}

void ERS_STRUCT_Camera::ProcessMouseScroll(float YOffset){
	roll -= YOffset * ROLL_ANGLE;	
	if(roll > twoPI) roll -= twoPI;
	else if(roll < -twoPI) roll += twoPI;
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
			if((zoom += zoomDelta) > FOV){
				zoom = FOV;
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

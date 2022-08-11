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




enum class TravelDirection{
	UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD
};

// FOV zooming
enum class ZoomState{
	_IN, _OUT
};




// Define Camera Directions
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
    ERS_STRUCT_Camera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f),
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








class ERS_STRUCT_Camera {
	private:
		float FOV;
		float zoom;
		float zoomDelta	= glm::radians(1.0f);	

		float aspect;
		float nearClip;
		float farClip;

		glm::vec3 position;
				
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

		float speed = 0.2f;						// the linear travel speed of the camera

		glm::mat4 perspectiveMatrix;
		//glm::mat4 viewMatrix;	
		
		glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

		void rotate(float angle, const glm::vec3 &axis);

	public:
		ERS_STRUCT_Camera() = delete;

		///<param name="FOV">The vertical Field of View. In radians</param>
		///<param name="windowWidth">The width of the display window</param>
		///<param name="windowHeight">The height of the display window</param>
		///<param name="near">The near-clipping plane</param>
		///<param name="far">The far-clipping plane</param>
		///<param name="position">The position of the camera</param>
		ERS_STRUCT_Camera(float fov, int width, int height, float near, float far);
		ERS_STRUCT_Camera(float fov, int width, int height, float near, float far, glm::vec3 position);
		
	
		void Update(float delta = 1.0f);
		void Move(TravelDirection td);
		void MouseMoveEvent(float x, float y);		// control pitch and yaw
		void MouseScrollEvent(float yOffset);		// control roll
		void Zoom(ZoomState z);		

		void SetAspect(float aspect);

		void SetMousePosition(float x, float y);
		void GetMatrices(glm::mat4& perspective, glm::mat4& view);
};


// ctor
ERS_STRUCT_Camera::Camera(float fov,  int width, int height, float nearClip, float farClip)  
	: Camera(fov, width, height, nearClip, farClip, glm::vec3(0.0f, 0.0f, 1.0f))
{}
ERS_STRUCT_Camera::Camera(float fov, int width, int height, float nearClip, float farClip, glm::vec3 position)
	: FOV(fov), zoom(fov), aspect(float(width)/float(height)), nearClip(nearClip), farClip(farClip), position(position){
	
	perspectiveMatrix = glm::perspective(FOV, aspect, nearClip, farClip);
	mousePosition.x = width / 2.0f;
	mousePosition.y = height / 2.0f;
}

void ERS_STRUCT_Camera::Update(float delta){		
	if(pitch != 0.0f)		rotate(pitch, xAxis);
	if(yaw != 0.0f)			rotate(yaw, yAxis);
	if(roll != 0.0f)		rotate(roll, zAxis);
	//
	//// instead of setting to zero immediately, we have the value eventually go to zero.
	pitch	*= damp;
	yaw		*= damp;
	roll	*= rollDamp;
}

void ERS_STRUCT_Camera::rotate(float angle, const glm::vec3 &axis){
	orientation *= glm::angleAxis(angle, axis * orientation);
}

void ERS_STRUCT_Camera::Move(TravelDirection td){

	// basically, translating the position vector

	glm::vec3 temp;
	switch(td){
		case TravelDirection::UP:
			position -= glm::vec3(0.0f, speed, 0.0f) * orientation;
			break;
		case TravelDirection::DOWN:
			position += glm::vec3(0.0f, speed, 0.0f) * orientation;
			break;
		case TravelDirection::LEFT:
			position += glm::vec3(speed, 0.0f, 0.0f) * orientation;
			break;
		case TravelDirection::RIGHT:
			position -= glm::vec3(speed, 0.0f, 0.0f) * orientation;
			break;
		case TravelDirection::FORWARD:
			position += glm::vec3(0.0f, 0.0f, speed) * orientation;
			break;
		case TravelDirection::BACKWARD:
			position -= glm::vec3(0.0f, 0.0f, speed) * orientation;
			break;
	}
}


void ERS_STRUCT_Camera::MouseMoveEvent(float x, float y){
	// updateing yaw
	yaw += (x - mousePosition.x) * mouseSenstivitiy;
	if(yaw > twoPI) yaw -= twoPI;
	else if(yaw < -twoPI) yaw += twoPI;

	// updateing pitch
	pitch += (y - mousePosition.y) * mouseSenstivitiy;
	if(pitch > twoPI) pitch -= twoPI;
	else if(pitch < -twoPI) pitch += twoPI;

	mousePosition.x = x;
	mousePosition.y = y;
}

void ERS_STRUCT_Camera::MouseScrollEvent(float yOffset){
	roll -= yOffset * ROLL_ANGLE;	
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

void ERS_STRUCT_Camera::SetAspect(float aspect){ 
	this->aspect = aspect; 
	perspectiveMatrix = glm::perspective(zoom, aspect, nearClip, farClip);
}


// ideally you want to set the mouse position to the center of the scene
void ERS_STRUCT_Camera::SetMousePosition(float x, float y){ 
	mousePosition.x = x;
	mousePosition.y = y;
}

void ERS_STRUCT_Camera::GetMatrices(glm::mat4& perspective, glm::mat4& view){
	perspective = perspectiveMatrix;	
	view = glm::translate(glm::mat4_cast(orientation), position);;
}

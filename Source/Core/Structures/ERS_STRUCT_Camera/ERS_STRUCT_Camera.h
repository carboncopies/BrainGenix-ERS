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

        glm::mat4 PerspectiveMatrix_;
        glm::mat4 ViewMatrix_;

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
		void ProcessMouseMovement(float XOffset, float YOffset);		// control pitch and yaw
		void ProcessMouseScroll(float YOffset);		// control Roll_
        void SetRotation(glm::vec3 Rotation);
		void SetAspectRatio(float AspectRatio);
		void Update();

        // Todo
		void Zoom(ZoomState z);		


		void SetMousePosition(float x, float y);
		void GetMatrices(glm::mat4& perspective, glm::mat4& view);
        //void GetDirectionVectors(glm::vec3 &Front, glm::vec3 &Right, glm::vec3 &Up);

};

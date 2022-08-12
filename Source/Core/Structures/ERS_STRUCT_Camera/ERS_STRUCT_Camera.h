//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

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
struct ERS_STRUCT_Camera {

public:






    // Internal Camera State Information
    float MovementSpeed_     = 0.2f; /**<Current Movement Speed*/
    float MouseSensitivity_  = 0.05f;
    float FOV_               = 50.0f;
    float AspectRatio_       = 1.25f;


    glm::vec3 Orientation_;    
    glm::vec3 Position_;
    
    glm::vec3 Front_;
    glm::vec3 Up_;
    glm::vec3 Right_;



    glm::mat4 PerspectiveMatrix_;
    glm::mat4 ViewMatrix_;




    // Asset Streaming Config
    int Priority_ = 1; // Higher this is, the more the system will try and load assets for this camera. Should be in range (1-10)


    // Constructor With Vectors
    ERS_STRUCT_Camera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f));
    ~ERS_STRUCT_Camera();

    // Proces Keyboard Input
    void ProcessKeyboard(CameraMovement Direction, float DeltaTime);

    // Process Mouse Input
    void ProcessMouseMovement(float XOffset, float Yoffset, GLboolean ConstrainPitch = true);
    void ProcessMouseScroll(float YOffset);

    void SetAspectRatio(float AspectRatio);
    void SetRotation(glm::vec3 Rotation);

    void GetMatrices(glm::mat4& perspective, glm::mat4& view);


    /**
     * @brief Updates The Following Camera Matricies/Vars:
     * View, Projection, Orientation Quat
     * 
     */
    void Update();


private:

    // Camea Configuration Information
    float NearClip_          = 0.01f; /**<Closest distance before geometry is culled.*/
    float FarClip_           = 100.0f; /**<Farthest distance before geometry is called*/
    float MinMovementSpeed_  = 0.01f; /**<Slowest movement speed allowed*/
    float MaxMovementSpeed_  = 50.0f; /**<Fastest movement speed allowed*/





};








// struct ERS_STRUCT_Camera {
//     private:
// 		void Rotate(float angle, const glm::vec3 &axis);

//         glm::mat4 PerspectiveMatrix_;
//         glm::mat4 ViewMatrix_;

//         float AspectRatio_;
// 		float NearClip_;
// 		float FarClip_;

// 	public:

//         // Asset Streaming Config
//         int Priority_ = 1; // Higher this is, the more the system will try and load assets for this camera. Should be in range (1-10)

// 		float FOV_;
// 		float zoom;
// 		float zoomDelta	= glm::radians(1.0f);	



// 		glm::vec3 Position_;
				
// 		glm::quat orientation;					// store rotation and orientation data

// 		glm::vec3 mousePosition;				// use to calculate the yaw and pitch rotation. 
// 		float mouseSenstivitiy	= 0.0009f;		// slow down the rate in which the camera rotate

// 		// play around with those two values until you get a roll speed that you like.
// 		const float ROLL_ANGLE	= 0.009f;		// we're using this because roll depends on the mouse scroll.
// 		float rollDamp			= 0.95f;		// we're using this because roll depends on the mouse scroll.
		
// 		float damp				= 0.8f;			// a value to damp the camera rotational speed

// 		// the angles to rotate the camera by.
// 		float Yaw_	 = 0.0f;						// rotate about the y axis
// 		float Pitch_ = 0.0f;						// rotate about the x axis
// 		float Roll_	 = 0.0f;						// rotate about the z axis
// 		float twoPI  = glm::two_pi<float>();		// check radian bound

// 		float MovementSpeed_ = 0.2f;			// the linear travel speed of the camera

		
// 		glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
// 		glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
// 		glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);


// 		//ERS_STRUCT_Camera() = delete;

// 		///<param name="FOV">The vertical Field of View. In radians</param>
// 		///<param name="windowWidth">The width of the display window</param>
// 		///<param name="windowHeight">The height of the display window</param>
// 		///<param name="near">The near-clipping plane</param>
// 		///<param name="far">The far-clipping plane</param>
// 		///<param name="Position_">The Position_ of the camera</param>
// 		ERS_STRUCT_Camera(float fov, int width, int height, float near, float far);
// 		ERS_STRUCT_Camera(float fov, int width, int height, float near, float far, glm::vec3 Position);
//         ERS_STRUCT_Camera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f));
		
	
//         // Done
// 		void ProcessKeyboard(CameraMovement Direction, float DeltaTime);
// 		void ProcessMouseMovement(float XOffset, float YOffset);		// control pitch and yaw
// 		void ProcessMouseScroll(float YOffset);		// control Roll_
//         void SetRotation(glm::vec3 Rotation);
// 		void SetAspectRatio(float AspectRatio);
// 		void Update();

//         // Todo
// 		void Zoom(ZoomState z);		


// 		void SetMousePosition(float x, float y);
// 		void GetMatrices(glm::mat4& perspective, glm::mat4& view);
//         //void GetDirectionVectors(glm::vec3 &Front, glm::vec3 &Right, glm::vec3 &Up);

// };

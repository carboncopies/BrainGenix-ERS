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



    /**
     * @brief Create the camera object.
     * 
     */
    ERS_STRUCT_Camera();

    /**
     * @brief Destroy the camera object.
     * 
     */
    ~ERS_STRUCT_Camera();



    /**
     * @brief Processes keyboard input for the camera.
     * 
     * @param Direction Direction currently being pressed.
     * @param DeltaTime Frame time used to ensure speed isn't tied to framerate
     */
    void ProcessKeyboard(CameraMovement Direction, float DeltaTime);

    /**
     * @brief Processed mouse movement across the camera's viewport.
     * 
     * @param XOffset Pixels moved in the x direction
     * @param Yoffset Pixels moved in the y direction
     * @param ConstrainPitch Stops the camera from turning above/bleow vertical
     */
    void ProcessMouseMovement(float XOffset, float Yoffset, GLboolean ConstrainPitch = true);

    /**
     * @brief Handles the mouse scrolling inputs
     * 
     * @param YOffset mouse scroll amount
     */
    void ProcessMouseScroll(float YOffset);


    


    /**
     * @brief Updates the camera's matricies, should be called once per frame.
     * 
     */
    void Update();


    /**
     * @brief Helper function, gets the projection/perspective matrix and the view matrix.
     * Note that if called before the update function, the values returned will be from the last frame.
     * 
     * @param Perspective 
     * @param View 
     */
    void GetMatrices(glm::mat4& Perspective, glm::mat4& View);

    /**
     * @brief Helper function, sets the camera's clipping distance.
     * 
     * @param NearClip Minimum distance in units for things to be rendered in.
     * @param FarClip Maximum distance in units for things to be rendered in.
     */
    void SetClipBoundries(float NearClip, float FarClip);

    /**
     * @brief Helper Function, gets the current camera clip distance.
     * 
     * @param NearClip Minimum distance in units for things to be rendered in.
     * @param FarClip Maximum distance in units for things to be rendered in.
     */
    void GetClipBoundires(float &NearClip, float &FarClip);

    /**
     * @brief Helper function, sets the camera's maximum and minimum freeflying movement speeds.
     * 
     * @param MinSpeed Slowest speed that the user can set the camera's keys to move in units per second.
     * @param MaxSpeed Fastest speed that the user can set the camera's keys to move in units per second.
     */
    void SetMovementSpeedBoundries(float MinSpeed, float MaxSpeed);

    /**
     * @brief Helper Function, gets the camera's maximum and minimum freeflying movement speeds.
     * 
     * @param MinSpeed Slowest speed that the user can set the camera's keys to move in units per second.
     * @param MaxSpeed Fastest speed that the user can set the camera's keys to move in units per second.
     */
    void GetMovementSpeedBoundries(float &MinSpeed, float &MaxSpeed);

    /**
     * @brief Helper function, Sets the speed of the camera.
     * 
     * @param Speed Desired speed in units per second.
     * @param EnforceSpeedBoundries Enable/disable hard boundry enforcement.
     */
    void SetMovementSpeed(float Speed, bool EnforceSpeedBoundries = true);
    
    /**
     * @brief Gets the mouse sensitivity multiplier.
     * 
     * @param Sensitivity Mouse sensitivity multiplier. 
     */
    void GetMouseSensitivity(float &Sensitivity);

    /**
     * @brief Sets the mouse sensitivity multiplier.
     * 
     * @param Sensitivity Mouse sensitivity multiplier.
     */
    void SetMouseSensitivity(float Sensitivity);

    /**
     * @brief Gets the current field of view angle.
     * 
     * @param FOV Field of view in degrees.
     */
    void GetFOV(float &FOV);

    /**
     * @brief Sets the field of view angle.
     * 
     * @param FOV Field of view in degrees.
     */
    void SetFOV(float FOV);

    /**
     * @brief Set the camera's aspect ratio (width/height)
     * 
     * @param AspectRatio Aspect ratio (width/height)
     */
    void SetAspectRatio(float AspectRatio);

    /**
     * @brief Sets the rotation of the camera.
     * 
     * @param Rotation Rotation in degrees (x,y,z) or (pitch, yaw, roll)
     */
    void SetRotation(glm::vec3 Rotation);

    /**
     * @brief Get the rotation 
     * 
     * @param Rotation Rotation in degrees (x,y,z) or (pitch, yaw, roll)
     */
    void GetRotation(glm::vec3 &Rotation);

    /**
     * @brief Set the position of the camera.
     * 
     * @param Position Position (x,y,z) in units relative to world origin.
     */
    void SetPosition(glm::vec3 Position);
    
    /**
     * @brief Get the position of the camera.
     * 
     * @param Position Position (x,y,z) in units relative to world origin.
     */
    void GetPosition(glm::vec3 &Position);

    /**
     * @brief Get the camera's streaming priority.
     * 
     * @param Priority Int between 1-10 setting the priority. 
     */
    void GetStreamingPriority(int &Priority);
    int GetStreamingPriority();
    
    /**
     * @brief Set the Streaming Priority int.
     * 
     * @param Priority Int between 1-10 setting the priority. 
     */
    void SetStreamingPriority(int Priority);

private:

    // Camea Configuration Information
    float NearClip_          = 0.01f;  /**<Closest distance before geometry is culled.*/
    float FarClip_           = 100.0f; /**<Farthest distance before geometry is called*/
    float MinMovementSpeed_  = 0.01f;  /**<Slowest movement speed allowed in units per second*/
    float MaxMovementSpeed_  = 50.0f;  /**<Fastest movement speed allowed in units per second*/


    // Internal Camera State Information
    float MovementSpeed_     = 0.2f;   /**<Current Movement Speed*/
    float MouseSensitivity_  = 0.05f;  /**<Mouse sensitivity multiplier*/
    float FOV_               = 50.0f;  /**<Field of view in degrees*/
    float AspectRatio_       = 1.25f;  /**<Internal variable used to setup the projection matrix*/

    glm::vec3 Orientation_;            /**<Rotation of the camera in degrees. */
    glm::vec3 Position_;               /**<Position of the camera in units */
    
    glm::vec3 Front_;                  /**<Unit vector facing out the front of the camera. (in local space)*/
    glm::vec3 Up_;                     /**<Unit vector facing out the top of the camera. (in local space)*/
    glm::vec3 Right_;                  /**<Unit vector facing to the right of the camera. (in local space)*/

    glm::mat4 PerspectiveMatrix_;      /**<Perspective/projection matrix, updated every time the Update function is called*/
    glm::mat4 ViewMatrix_;             /**<View matrix, updated every time the Update function is called*/


    // Asset Streaming Settings
    int Priority_ = 1;                 /**< Higher this is, the more the system will try and load assets for this camera. Should be in range (1-10)*/


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

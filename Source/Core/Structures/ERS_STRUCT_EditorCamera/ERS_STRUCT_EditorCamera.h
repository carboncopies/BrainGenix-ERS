//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <iostream>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_Camera.h>


// Camera Movement Controls
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};


// Setup Camera Options
struct ERS_STRUCT_EditorCamera {

public:



    /**
     * @brief Create the editor camera object.
     * 
     */
    ERS_STRUCT_EditorCamera();

    /**
     * @brief Destroy the editor camera object.
     * 
     */
    ~ERS_STRUCT_EditorCamera();



    /**
     * @brief Processes keyboard input for the editor camera.
     * 
     * @param Direction Direction currently being pressed.
     * @param DeltaTime Frame time used to ensure speed isn't tied to framerate
     */
    void ProcessKeyboard(CameraMovement Direction, float DeltaTime);

    /**
     * @brief Processed mouse movement across the editor camera's viewport.
     * 
     * @param XOffset Pixels moved in the x direction
     * @param Yoffset Pixels moved in the y direction
     * @param ConstrainPitch Stops the camera from turning above/bleow vertical
     */
    void ProcessMouseMovement(float XOffset, float Yoffset, GLboolean ConstrainPitch = true);

    /**
     * @brief Handles the mouse scrolling inputs on the editor camera.
     * 
     * @param YOffset mouse scroll amount
     */
    void ProcessMouseScroll(float YOffset);

    
    /**
     * @brief Updates the position and other information about the editor editor camera
     * 
     */
    void Update();



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
    glm::vec3 GetRotation();

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
    glm::vec3 GetPosition();

private:

    // Editor Camera Configuration Information
    float MinMovementSpeed_  = 0.01f;  /**<Slowest movement speed allowed in units per second */
    float MaxMovementSpeed_  = 50.0f;  /**<Fastest movement speed allowed in units per second */


    // Internal Camera State Information
    float MovementSpeed_     = 0.2f;   /**<Current Movement Speed       */
    float MouseSensitivity_  = 0.05f;  /**<Mouse sensitivity multiplier */

    glm::vec3 Orientation_;            /**<Rotation of the editor camera in degrees. */
    glm::vec3 Position_;               /**<Position of the editor camera in units    */
    

    // Camera Link Information
    bool HasCameraAttached_ = false;   /**<Indicates if the camera pointer has bee setup. */
    ERS_STRUCT_Camera* Camera_;        /**<Reference to a camera instance.                */

};


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



private:

    // Editor Camera Configuration Information
    float MinMovementSpeed_  = 0.01f;  /**<Slowest movement speed allowed in units per second*/
    float MaxMovementSpeed_  = 50.0f;  /**<Fastest movement speed allowed in units per second*/


    // Internal Camera State Information
    float MovementSpeed_     = 0.2f;   /**<Current Movement Speed*/
    float MouseSensitivity_  = 0.05f;  /**<Mouse sensitivity multiplier*/

    glm::vec3 Orientation_;            /**<Rotation of the editor camera in degrees. */
    glm::vec3 Position_;               /**<Position of the editor camera in units */
    
};


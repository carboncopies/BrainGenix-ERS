//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the Noclip camera.
    Additonal Notes: None
    Date Created: 2021-11-05
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



// Define Camera Directions
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Set Default Attributes
const float DefaultYaw = -90.0f;
const float DefaultPitch = 0.0f;
const float DefaultSpeed = 2.5f;
const float DefaultSensitivity = 0.1f;
const float DefaultZoom = 45.0f;

// Set Bounding Attributes
const float MaxZoom = 45.0f;
const float MinZoom = 1.0f;


// Setup Camera Options
class ERS_OBJECT_CAMERA_NOCLIP {

    public:

        // Camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        // Euler Angles
        float Yaw;
        float Pitch;

        // Camera Options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        // Constructor With Vectors
        ERS_OBJECT_CAMERA_NOCLIP(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f), float Yaw = DefaultYaw, float Pitch = DefaultPitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(DefaultSpeed), MouseSensitivity(DefaultSensitivity), Zoom(DefaultZoom) {
            
            // Set Params
            Position = Position;
            WorldUp = Up;
            Yaw = Yaw;
            Pitch = Pitch;
            UpdateCameraVectors();
            
        }

        // Constructor With Scalar Values
        ERS_OBJECT_CAMERA_NOCLIP(float PosX, float PosY, float PosZ, float UpX, float UpY, float UpZ, float Yaw, float Pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(DefaultSpeed), MouseSensitivity(DefaultSensitivity), Zoom(DefaultZoom) {
            Position = glm::vec3(PosX, PosY, PosZ);
            WorldUp = glm::vec3(UpX, UpY, UpZ);
            Yaw = Yaw;
            Pitch = Pitch;
            UpdateCameraVectors();
        }

        // Return View Matrix
        glm::mat4 GetViewMatrix();

        // Proces Keyboard Input
        void ProcessKeyboard(CameraMovement Direction, float DeltaTime);

        // Process Mouse Input
        void ProcessMouseMovement(float XOffset, float Yoffset, GLboolean ConstrainPitch = true);
        void ProcessMouseScroll(float YOffset);


    private:

        void UpdateCameraVectors();


};


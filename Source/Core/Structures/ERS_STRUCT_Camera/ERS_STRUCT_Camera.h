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
    RIGHT,
    UP,
    DOWN
};


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
        double MovementSpeed;
        float MouseSensitivity;
        float Zoom;
        float AspectRatio_;

        // Config Params
        float MinMovementSpeed = 0.0f;
        float MaxMovementSpeed = 50.0f;

        // Constructor With Vectors
        ERS_OBJECT_CAMERA_NOCLIP(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f),
                                 float Yaw = -90.0f,
                                 float Pitch = 0.0f) : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                 MovementSpeed(6.0f),
                                 MouseSensitivity(0.1f),
                                 Zoom(45.0f) {
            
            // Set Params
            Position = Position;
            WorldUp = Up;
            Yaw = Yaw;
            Pitch = Pitch;
            UpdateCameraVectors();
            
        }

        // Constructor With Scalar Values
        ERS_OBJECT_CAMERA_NOCLIP(float PosX,
                                 float PosY,
                                 float PosZ,
                                 float UpX,
                                 float UpY,
                                 float UpZ,
                                 float Yaw,
                                 float Pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                 MovementSpeed(6.0f),
                                 MouseSensitivity(0.1f),
                                 Zoom(45.0f) {
            Position = glm::vec3(PosX, PosY, PosZ);
            WorldUp = glm::vec3(UpX, UpY, UpZ);
            Yaw = Yaw;
            Pitch = Pitch;
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

    private:

        void UpdateCameraVectors();


};


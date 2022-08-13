//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>

#include <glm/glm.hpp>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>

#include <ERS_STRUCT_Camera.h>


/**
 * @brief The input processor reads keystrokes and mouse movement and sends them to the EditorCamera struct.
 * 
 */
class ERS_CLASS_InputProcessor {

private:

    // Internal Vars
    bool FirstMouse          = true;   /**<Checks if the mouse is just being enabled. */
    float LastX              = 400;    /**<Location Of Last Mouse Position. (X coord) */
    float LastY              = 400;    /**<Location Of Last Mouse Position. (Y Coord) */

    float MinMovementSpeed_  = 0.01f;  /**<Slowest movement speed allowed in units per second */
    float MaxMovementSpeed_  = 50.0f;  /**<Fastest movement speed allowed in units per second */
    
    float MovementSpeed_     = 0.2f;   /**<Current Movement Speed            */
    float MouseSensitivity_  = 0.05f;  /**<Mouse sensitivity multiplier      */
    bool  ConstrainPitch_    = true;   /**<Limit the camera to +- 89 degrees */

    glm::vec3 Orientation_;            /**<Rotation of the editor camera in degrees. */
    glm::vec3 Position_;               /**<Position of the editor camera in units    */


    ERS_STRUCT_Camera* Camera_; /**<Pointer To EditorCamera Instance */
    GLFWwindow*        Window_; /**<Pointer To Window Surface        */


    /**
     * @brief Callback for the framebuffer size (window resize events)
     * 
     * @param Width 
     * @param Height 
     */
    void FramebufferSizeCallback(int Width, int Height);

    /**
     * @brief Callback for mouse position (X,Y)
     * 
     * @param XPos 
     * @param YPos 
     */
    void MouseCallback(double XPos, double YPos);

    /**
     * @brief Callback for Mouse Scroll (!!!DOESN'T WORK RIGHT NOW, NEED TO BE FIXED!!!)
     * 
     * @param YOffset 
     */
    void ScrollCallback(double YOffset);

public:


    /**
     * @brief Construct a new Input Processor object
     * 
     * @param Camera 
     */
    ERS_CLASS_InputProcessor(ERS_STRUCT_Camera* Camera, GLFWwindow* Window);

    /**
     * @brief Destroy the Input Processor object
     * 
     */
    ~ERS_CLASS_InputProcessor();



    /**
     * @brief Update the framebuffer size.
     * 
     * @param Window 
     */
    void UpdateFramebuffer();

    /**
     * @brief Update the mouse info.
     * 
     * @param Window 
     * @param WindowMouseCaptureEnabled 
     */
    void UpdateMouse(bool WindowMouseCaptureEnabled);

    /**
     * @brief Processes mouse scroll wheel input.
     * 
     * @param CaptureEnabled 
     */
    void ProcessMouseScroll(bool CaptureEnabled);

    /**
     * @brief Processes keyboard input for the editor camera.
     * 
     * @param Logger_ 
     * @param DeltaTime 
     */
    void ProcessKeyboardInput(float DeltaTime, bool WindowCaptureEnabled);

    /**
     * @brief Processes key input for the editor camera.
     * 
     * @param Direction Direction currently being pressed.
     * @param DeltaTime Frame time used to ensure speed isn't tied to framerate
     */
    void ProcessKey(CameraMovement Direction, float DeltaTime);



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

    /**
     * @brief Check if pitch constraint is enabled or disabled
     * 
     * @param ConstrainEnabled 
     */
    void GetPitchConstraint(bool &ConstrainEnabled);
    bool GetPitchConstraint();

    /**
     * @brief Enable or Disable Pitch Constraint
     * 
     * @param ConstrainEnabled 
     */
    void SetPitchConstraint(bool ConstrainEnabled);

};
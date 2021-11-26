//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the visual renderer callback functions.
    Documentation Status: Done
    Additonal Notes: None
    Date Created: 2021-11-16
*/

#pragma once

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <NoClip.h>
#include <LoggingSystem.h>


/**
 * @brief The input processor class handles processing window input and converting that into usable information.
 * 
 */
class InputProcessor {

    private:

        // Internal Vars
        bool FirstMouse = true;
        float LastX = 400;
        float LastY = 400;
        ERS_OBJECT_CAMERA_NOCLIP *Camera_;

        GLFWwindow *Window_;


        // Internal Functions
        void FramebufferSizeCallback(int Width, int Height);
        void MouseCallback(double XPos, double YPos);

        // FIXME: NO FUNCTION EXISTS TO GET SCROLL INPUT WITHOUT CALLBACK
        void ScrollCallback(double YOffset);

    public:

        /**
         * @brief Construct a new Input Processor object
         * 
         * @param Camera 
         */
        InputProcessor(ERS_OBJECT_CAMERA_NOCLIP *Camera, GLFWwindow* Window);

        /**
         * @brief Destroy the Input Processor object
         * 
         */
        ~InputProcessor();



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
         * @brief Process keyboard input
         * 
         * @param Logger_ 
         * @param DeltaTime 
         */
        void ProcessKeyboardInput(LoggerClass *Logger_, float DeltaTime, bool WindowCaptureEnabled);



};
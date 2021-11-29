//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the visual renderer callback functions.
    Documentation Status: Complete
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
#include <Framebuffer.h>


/**
 * @brief The input processor class handles processing window input and converting that into usable information.
 * 
 */
class InputProcessor {

    private:

        // Internal Vars
        bool FirstMouse = true; /**<Checks if the mouse is just being enabled.*/
        float LastX = 400; /**<Location Of Last Mouse Position. (X coord) */
        float LastY = 400; /**<Location Of Last Mouse Position. (Y Coord) */ 
        ERS_OBJECT_CAMERA_NOCLIP *Camera_; /**<Pointer To Camera Instance */
        FramebufferManager *FramebufferManager_; /**<Pointer To Framebuffer Manager Instance For Resizing The Framebuffer*/

        GLFWwindow *Window_; /**<Pointer To Window Surface */


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

        // FIXME: NO FUNCTION EXISTS TO GET SCROLL INPUT WITHOUT CALLBACK
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
        InputProcessor(ERS_OBJECT_CAMERA_NOCLIP *Camera, GLFWwindow* Window, FramebufferManager *FramebufferManager);

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
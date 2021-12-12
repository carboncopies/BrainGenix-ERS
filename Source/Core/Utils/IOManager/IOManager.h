//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides IOManager functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-29
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")


// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <InputProcessor.h>




/**
 * @brief The IOManager Class Gets All User Input And Provides It To The Rest Of The System
 * 
 */
class IOManager {

    private:

        // Class Instances
        std::shared_ptr<LoggerClass> Logger_; /**<Logging System Instance Pointer*/
        std::shared_ptr<InputProcessor> InputProcessor_; /**<Pointer to input processor instance*/
        std::shared_ptr<ERS_OBJECT_CAMERA_NOCLIP> Camera_; /**<Pointer To Camera Instance*/
        //FramebufferManager *FramebufferManager_; /**<Pointer To Framebuffer Manager Instance*/

        // Objects
        GLFWwindow *Window_; /**<Pointer To GLFW Window */

        // Parameters
        int WindowWidth_; /**<Window Width*/
        int WindowHeight_; /**<Window Height*/





    public:

        /**
         * @brief Construct a new IOManager object
         * 
         * @param Logger 
         * @param Camera 
         * @param FramebufferManager 
         */
        IOManager(std::shared_ptr<LoggerClass> Logger, GLFWwindow *Window, std::shared_ptr<ERS_OBJECT_CAMERA_NOCLIP> Camera);

        /**
         * @brief Destroy the IOManager object
         * 
         */
        ~IOManager();


        /**
         * @brief Update the input for this frame.
         * 
         * @param DeltaTime 
         */
        void UpdateFrame(float DeltaTime);

};
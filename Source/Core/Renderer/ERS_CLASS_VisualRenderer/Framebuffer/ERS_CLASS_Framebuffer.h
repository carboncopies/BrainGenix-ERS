//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")


// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>
#include <ERS_STRUCT_Shader.h>
#include <ERS_CLASS_ShaderLoader.h>



/**
 * @brief Class to create/renderto/destruy framebuffer object.
 * 
 */
class ERS_CLASS_Framebuffer {


    private:

        std::shared_ptr<ERS_CLASS_LoggingSystem> Logger_; /**<Pointer to instance of Logger Class*/
        unsigned int FramebufferObject_; /**<Framebuffer OpenGL Handle (Used to Render Inside IMGUI Window Or On Screen Directly)*/
        unsigned int RenderTexture_; /**<OpenGL Renderes To This Texture, Then It's Displayed. (OpenGL Handle)*/
        unsigned int RenderBufferObject_; /**<RenderBuffer Object Handle.*/

        std::shared_ptr<ERS_CLASS_ShaderLoader> ShaderLoader_; /**<Pointer To Shader Loader Instance*/
        ERS_STRUCT_Shader ScreenShader_; /**<Screen Shader Instance, Used To Display Framebuffer To Screen*/


        unsigned int ScreenQuadVAO_; /**<Screen Quad VAO Reference*/
        unsigned int ScreenQuadVBO_; /**<Screen Quad VBO Reference*/


    public:


        /**
         * @brief Construct a new Framebuffer Manager object.
         * 
         * @param Logger ERS_CLASS_LoggingSystem Instance Pointer
         * @param Width Width In Pixels
         * @param Height Height In Pixels
         */
        ERS_CLASS_Framebuffer(std::shared_ptr<ERS_CLASS_LoggingSystem> Logger, std::shared_ptr<ERS_CLASS_ShaderLoader> ShaderLoader, float Width = 800.0f, float Height = 600.0f);

        /**
         * @brief Destroy the Framebuffer Manager object.
         * 
         */
        ~ERS_CLASS_Framebuffer();



        /**
         * @brief Start The renderpass On The Framebuffer Object.
         * 
         */
        void StartFramebufferRenderPass();

        /**
         * @brief Start Renderpass To Screen (GUI Rendering Goes AFter This).
         * 
         */
        void StartScreenRenderPass();

        /**
         * @brief Resizes the framebuffer to allow for proper scaling.
         * 
         * @param Width 
         * @param Height 
         */
        void ResizeFramebuffer(int Width, int Height);

};
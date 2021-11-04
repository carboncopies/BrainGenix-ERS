//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the openGL Renderer.
    Additonal Notes: None
    Date Created: 2021-11-01
*/


void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height) {

    // Update Viewport
    glViewport(0,0, Width, Height);

}

class Renderer {

    private:

        // Member Variables
        YAML::Node *SystemConfiguration_;
        LoggerClass *Logger_;
        ShaderObject Shader_;
        ERSTexture Texture1;
        ERSTexture Texture2;
        TextureManager TextureManager_;



        GLFWwindow* Window_;
        int WindowWidth_;
        int WindowHeight_;
        const char* WindowTitle_;

        int RenderWidth_;
        int RenderHeight_;


        unsigned int VBO, VAO, EBO;
        unsigned int shaderProgram;


        // Member Functions
        void InitializeGLFW();
        void InitializeOpenGL();



    public:

        void InitializeRenderer(YAML::Node *SystemConfiguration, LoggerClass *Logger);

        bool UpdateLoop();

        void CleanUp();


};
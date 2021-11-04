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

        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;

        unsigned int VBO, VAO;
        unsigned int shaderProgram;
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };


        // Member Functions
        void InitializeGLFW();
        void InitializeOpenGL();



    public:

        void InitializeRenderer(YAML::Node *SystemConfiguration, LoggerClass *Logger);

        bool UpdateLoop();

        void CleanUp();


};
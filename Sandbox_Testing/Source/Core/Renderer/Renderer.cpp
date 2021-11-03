//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the openGL Renderer.
    Additonal Notes: None
    Date Created: 2021-11-01
*/

#include <glad/glad.h>
#include <glad.c>
#include <GLFW/glfw3.h>

#include <stb_image.h> // deleteme after implementing ersimage

#include "Core/Renderer/VisualRenderer/WindowInputProcessor.cpp"
#include "Core/Renderer/VisualRenderer/ShaderManager.cpp"
#include "Core/Renderer/VisualRenderer/TextureManager.cpp"

#include "Core/Renderer/Renderer.h"


void Renderer::InitializeRenderer(YAML::Node *SystemConfiguration, LoggerClass *Logger) {

    // Create Pointers
    Logger->Log("Populating Renderer Member Pointers", 5);
    SystemConfiguration_ = SystemConfiguration;
    Logger_ = Logger;

    // Initialize Systems

    Logger_->Log("Initializing TextureManager", 5);
    TextureManager_.Initialize(Logger_);
    Logger_->Log("Initialized TextureManager", 4);

    Logger_->Log("Initializing GLFW", 5);
    InitializeGLFW();

    Logger_->Log("Initializing OpenGL", 5);
    InitializeOpenGL();

}

void Renderer::InitializeGLFW() {

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Read Out Width, Height
    Logger_->Log("Read Configuration File For 'WindowWidth' Parameter", 1);
    WindowWidth_ = (*SystemConfiguration_)["WindowWidth"].as<int>();
    Logger_->Log("Read Configuration File For 'WindowHeight' Parameter", 1);
    WindowHeight_ = (*SystemConfiguration_)["WindowHeight"].as<int>();
    Logger_->Log("Read Configuration File For 'WindowTitle' Parameter", 1);
    WindowTitle_ = (*SystemConfiguration_)["WindowTitle"].as<std::string>().c_str();


    // Create Window Object
    Window_ = glfwCreateWindow(WindowWidth_, WindowHeight_, WindowTitle_, NULL, NULL);
    if (Window_ == NULL) {
        glfwTerminate();
    }

    glfwMakeContextCurrent(Window_);

}

void Renderer::InitializeOpenGL() {

    // Setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger_->Log("Failed To Initialize GLAD", 10);
    }

    // Setup Viewport
    Logger_->Log("Read Configuration File For 'RenderWidth' Parameter", 1);
    RenderWidth_ = (*SystemConfiguration_)["RenderWidth"].as<int>();
    Logger_->Log("Read Configuration File For 'RenderHeight' Parameter", 1);
    RenderHeight_ = (*SystemConfiguration_)["RenderHeight"].as<int>();

    glViewport(0, 0, RenderWidth_, RenderHeight_);

    // Register Callback
    glfwSetFramebufferSizeCallback(Window_, FramebufferSizeCallback);

    // Setup Shaders
    Shader_ = LoadShaderFromFile("Shaders/Main.vert", "Shaders/Main.frag", Logger_);

    // Setup Textures
    Texture_ = TextureManager_.CreateTextureFromFile("Assets/container.jpg");



    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);






    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);






    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



}

bool Renderer::UpdateLoop() {

    // Process Window Input
    ProcessInput(Window_, Logger_);

    // Rendering Commands Here
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    // Bind Texture
    Texture_.BindTexture();


    Shader_.MakeActive();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    // Update Window Stuff
    glfwSwapBuffers(Window_);
    glfwPollEvents();


    // Check If System Should Shutdown
    if (glfwWindowShouldClose(Window_)) {
        Logger_->Log("System Shutdown Invoked By LocalWindow", 2);
        return false;
    }

    // System Should Not Shutdown
    return true;

}


void Renderer::CleanUp() {

    // Cleanup
    Logger_->Log("Cleaning Up OpenGL/GLFW", 0);
    glfwTerminate();

}
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for the main render loop
    Additonal Notes: None
    Date Created: 2021-09-22
*/   

#include "Core/SystemInput/WindowInput/WindowInputModule.cpp"
#include "Core/Renderer/ShaderProcessor/ShaderProcessor.h"
#include "Core/AssetLoader/TextureLoaderModule.cpp"
#include "Core/Renderer/Camera/Noclip/NoclipCameraModule.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;



// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// light pos
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);



void MainRenderLoop(GLFWwindow* Window, LoggerClass Logger) {

    // Create Bool Variables //
    bool SystemShutdownInvoked = false;
    bool bWireframeMode = false;

    // Enable Depth-Based Draw Ordering
    glEnable(GL_DEPTH_TEST); 


    // build and compile our shader program
    // ------------------------------------
    //Shader ourShader(Logger, "Shaders/shader.vs", "Shaders/shader.fs"); // you can name your shader files however you like




    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader(Logger, "Shaders/colors.vs", "Shaders/colors.fs");
    Shader lightCubeShader(Logger, "Shaders/light_cube.vs", "Shaders/light_cube.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 

        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 

         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture Load
    //unsigned int texture = LoadTexture("container.jpg", Logger);

    // Window Input Setup
    WindowInputClass WindowInputManager(SCR_WIDTH, SCR_HEIGHT, Window, camera);

    // Set Window Callbacks
    //glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(Window, WindowInputManager.ProcessMouseButtonWindowInput);
    //glfwSetScrollCallback(Window, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);





    // Main Render Loop //
    while(!SystemShutdownInvoked)
    {

        // Clear Screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // Set Drawing Mode
        if (bWireframeMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }    

        // Update Draw Order Based On Depth
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


        // bind Texture
        //glBindTexture(GL_TEXTURE_2D, texture);

        ////-------- RENDERING CODE HERE --------////

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // render the cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // also draw the lamp object
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        ////-------- END RENDERING CODE --------////


        // If The GLFW Window Exists //
        if (Window != nullptr) {

            // Update Window User Input //
            WindowInputManager.ProcessKeyboardWindowInput(1.0);

            // Check For Shutdown Events //
            SystemShutdownInvoked = glfwWindowShouldClose(Window);


            // GLFW Window Update //
            glfwSwapBuffers(Window);
            glfwPollEvents(); 


            if (glfwGetKey(Window, GLFW_KEY_1) == GLFW_PRESS) {
            bWireframeMode = false;
            }
            if (glfwGetKey(Window, GLFW_KEY_2) == GLFW_PRESS) {
            bWireframeMode = true;
            }



        }
    }
}

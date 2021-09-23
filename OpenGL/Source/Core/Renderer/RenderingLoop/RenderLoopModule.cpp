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


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void MainRenderLoop(GLFWwindow* Window, LoggerClass Logger) {

    // Create Bool Variables //
    bool SystemShutdownInvoked = false;
    bool bWireframeMode = false;




    // build and compile our shader program
    // ------------------------------------
    Shader ourShader(Logger, "Shaders/3.3.shader.vs", "Shaders/3.3.shader.fs"); // you can name your shader files however you like



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
    unsigned int VBO, VAO, EBO;
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


    unsigned int texture = LoadTexture("container.jpg", Logger);









    // Main Render Loop //
    while(!SystemShutdownInvoked)
    {

        // Rendering Commands Here //
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // Set Drawing Mode
        if (bWireframeMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }    


        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);






        // If The GLFW Window Exists //
        if (Window != nullptr) {

            // Update Window User Input //
            ProcessWindowInput(Window);

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
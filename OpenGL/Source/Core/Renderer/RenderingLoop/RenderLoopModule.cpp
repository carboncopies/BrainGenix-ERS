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



// CameraInstance
Camera CameraInstance(glm::vec3(0.0f, 0.0f, 3.0f));

// Initialization Parameters
bool firstMouse = true;
float lastX = 0;
float lastY = 0;

void ProcessMouseButtonWindowInput(GLFWwindow* Window, double xpos, double ypos);
void ProcessMouseScrollWindowInput(GLFWwindow* window, double xoffset, double yoffset);





// timing
float DeltaTime = 0.0f;	// time between current frame and last frame
float LastFrame = 0.0f;

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
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };


    /// first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Texture Load
    //unsigned int texture = LoadTexture("container.jpg", Logger);


    if (Window != nullptr) {

        // Set Window Callbacks
        //glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
        glfwSetCursorPosCallback(Window, ProcessMouseButtonWindowInput);
        glfwSetScrollCallback(Window, ProcessMouseScrollWindowInput);

        // tell GLFW to capture our mouse
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    }




    // Main Render Loop //
    while(!SystemShutdownInvoked) {

        // Update DeltaTime
        float CurrentFrame = glfwGetTime();
        DeltaTime = CurrentFrame - LastFrame;
        LastFrame = CurrentFrame;


        // Clear Screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

        glm::vec4 LIGHTCOL = glm::vec4(1.0f);//, cos(glfwGetTime()), sin(glfwGetTime()), 0.0f);

// be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("light.position", lightPos);
        lightingShader.setVec3("viewPos", CameraInstance.Position);

        // light properties
        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
        lightingShader.setVec3("light.ambient", ambientColor);
        lightingShader.setVec3("light.diffuse", diffuseColor);
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // material properties
        lightingShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        lightingShader.setFloat("material.shininess", 32.0f); 

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(CameraInstance.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = CameraInstance.GetViewMatrix();
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


        lightCubeShader.setVec4("LightColor", LIGHTCOL);


        //lightPos.x = sin(glfwGetTime()) * 2;
        //lightPos.z = cos(glfwGetTime()) * 2;
        //lightPos.y = cos(glfwGetTime()/3);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        ////-------- END RENDERING CODE --------////


        // If The GLFW Window Exists //
        if (Window != nullptr) {

            if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {        
                glfwSetWindowShouldClose(Window, true);
            }

            if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS) 
                CameraInstance.ProcessKeyboard("FORWARD", DeltaTime);
            if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
                CameraInstance.ProcessKeyboard("BACKWARD", DeltaTime);
            if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
                CameraInstance.ProcessKeyboard("LEFT", DeltaTime);
            if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
                CameraInstance.ProcessKeyboard("RIGHT", DeltaTime);
            

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


//glfw: whenever the mouse moves, this callback is called
//-------------------------------------------------------
void ProcessMouseButtonWindowInput(GLFWwindow* Window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    CameraInstance.ProcessMouseMovement(xoffset, yoffset);

}



//glfw: whenever the mouse scroll wheel scrolls, this callback is called
//----------------------------------------------------------------------
void ProcessMouseScrollWindowInput(GLFWwindow* window, double xoffset, double yoffset)
{
    CameraInstance.ProcessMouseScroll(yoffset);
}
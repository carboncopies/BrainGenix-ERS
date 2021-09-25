//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for the main render loop
    Additonal Notes: None
    Date Created: 2021-09-22
*/   

#include "Core/SystemInput/WindowInput/WindowInputModule.cpp"

#include "Core/AssetLoader/TextureLoaderModule.cpp"
#include "Core/Renderer/Camera/Noclip/NoclipCameraModule.h"
#include "Core/AssetLoader/Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


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
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);






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
    Shader ourShader(Logger, "Shaders/Model.vs", "Shaders/Model.fs");
    
    Model ourModel(Logger, "Assets/backpack.obj");



    if (Window != nullptr) {

        // Set Window Callbacks
        glfwSetFramebufferSizeCallback(Window, FramebufferSizeCallback);
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




        ////-------- RENDERING CODE HERE --------////

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(CameraInstance.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = CameraInstance.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Render(ourShader);


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



void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
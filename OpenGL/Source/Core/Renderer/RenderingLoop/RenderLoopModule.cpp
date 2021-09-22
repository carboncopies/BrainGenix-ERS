//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for the main render loop
    Additonal Notes: None
    Date Created: 2021-09-22
*/   

#include "Core/SystemInput/WindowInput/WindowInputModule.cpp"

void MainRenderLoop(GLFWwindow* Window) {

    // Create System Shutdown Variable //
    bool SystemShutdownInvoked = false;

    // Main Render Loop //
    while(!SystemShutdownInvoked)
    {

        // Rendering Commands Here //
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // If The GLFW Window Exists //
        if (Window != nullptr) {

            // Update Window User Input //
            ProcessWindowInput(Window);

            // Check For Shutdown Events //
            SystemShutdownInvoked = glfwWindowShouldClose(Window);


            // GLFW Window Update //
            glfwSwapBuffers(Window);
            glfwPollEvents(); 

        }

   
    }

}
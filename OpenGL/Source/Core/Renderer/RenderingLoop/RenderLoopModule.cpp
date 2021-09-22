//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for the main render loop
    Additonal Notes: None
    Date Created: 2021-09-22
*/   

void MainRenderLoop(GLFWwindow* Window) {

    // Create System Shutdown Variable //
    bool SystemShutdownInvoked = false;

    // Main Render Loop //
    while(!SystemShutdownInvoked)
    {

        // If The GLFW Window Exists //
        if (Window != nullptr) {

            // Check For Shutdown Events //
            SystemShutdownInvoked = glfwWindowShouldClose(Window);


            // GLFW Window Update //
            glfwSwapBuffers(Window);
            glfwPollEvents(); 

        }

   
    }

}
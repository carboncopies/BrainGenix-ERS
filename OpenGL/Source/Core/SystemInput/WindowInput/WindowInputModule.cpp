//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for the main render loop
    Additonal Notes: None
    Date Created: 2021-09-22
*/

void ProcessWindowInput(GLFWwindow *Window) {

    // Set Escape Key To Exit
    if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        
        glfwSetWindowShouldClose(Window, true);

    }

}

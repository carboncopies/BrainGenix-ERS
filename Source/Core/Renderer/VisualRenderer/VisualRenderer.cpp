//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the visual renderer.
    Additonal Notes: None
    Date Created: 2021-11-20
*/

#include <VisualRenderer.h>



// Visual Rendere constructor
VisualRenderer::VisualRenderer (YAML::Node *SystemConfiguration, LoggerClass *Logger) {

    // Create Pointers
    Logger->Log("Populating Renderer Member Pointers", 5);
    SystemConfiguration_ = SystemConfiguration;
    Logger_ = Logger;

    // Initialize OpenGL
    Logger_->Log("Initializing OpenGL", 5);
    InitializeOpenGL();

}

VisualRenderer::~VisualRenderer() {

    // Cleanup
    Logger_->Log("Cleaning Up OpenGL/GLFW", 0);
    glfwTerminate();

}

void VisualRenderer::InitializeOpenGL() {


    // Setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger_->Log("Failed To Initialize GLAD", 10);
    }

}

void VisualRenderer::UpdateViewports(float DeltaTime, SceneManager *SceneManager) {


    // Iterate Through Viewports
    for (int i = 0; i<Shaders_.size(); i++) {

        UpdateViewport(i, SceneManager, DeltaTime, 400, 200);

    }


}


void VisualRenderer::UpdateViewport(int Index, SceneManager *SceneManager, float DeltaTime, float RenderWidth, float RenderHeight) {



    // Rendering Commands Here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Use Shader
    Shaders_[Index]->MakeActive();


    // Update Camera
    float AspectRatio = (float)RenderWidth / (float)RenderHeight;
    glm::mat4 projection = glm::perspective(glm::radians(Cameras_[Index]->Zoom), AspectRatio, 0.1f, 100.0f);
    glm::mat4 view = Cameras_[Index]->GetViewMatrix();
    Shaders_[Index]->SetMat4("projection", projection);
    Shaders_[Index]->SetMat4("view", view);


    // Draw Models
    SceneManager->Render(Shaders_[Index]);

}

// Create Viewport
void VisualRenderer::CreateViewport(ERS_OBJECT_SHADER *Shader, ERS_OBJECT_CAMERA_NOCLIP *Camera) {

    // Append To Pointers List
    Shaders_.push_back(Shader);
    Cameras_.push_back(Camera);


}
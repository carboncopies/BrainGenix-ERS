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
VisualRenderer::VisualRenderer (YAML::Node *SystemConfiguration, LoggerClass *Logger, bool *SystemShouldRun) {

    // Create Pointers
    Logger->Log("Populating Renderer Member Pointers", 5);
    SystemConfiguration_ = SystemConfiguration;
    Logger_ = Logger;
    SystemShouldRun_ = SystemShouldRun;

    // Initialize Texture Loader
    TextureLoader_ = new TextureLoader(Logger_);



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


    // Load Model
    ModelLoader MLoader(Logger_, TextureLoader_);

    SceneLoader SLoader(Logger_, &MLoader);
    SceneManager_ = new SceneManager(Logger_);

    // Test Scene
    YAML::Node TestScene = YAML::LoadFile("Assets/Scene.yaml");
    SceneManager_->AddScene(SLoader.ProcessScene(TestScene));

}

void VisualRenderer::UpdateViewport(float DeltaTime, float RenderWidth, float RenderHeight) {



    // Rendering Commands Here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Use Shader
    Shader->MakeActive();


    // Update Camera
    float AspectRatio = (float)RenderWidth / (float)RenderHeight;
    glm::mat4 projection = glm::perspective(glm::radians(Camera->Zoom), AspectRatio, 0.1f, 100.0f);
    glm::mat4 view = Camera->GetViewMatrix();
    Shader->SetMat4("projection", projection);
    Shader->SetMat4("view", view);


    // Draw Models
    SceneManager_->Render(Shader);

}

// Create Viewport
void VisualRenderer::CreateViewport(ERS_OBJECT_SHADER *Shader, ERS_OBJECT_CAMERA_NOCLIP *Camera) {

    // Append To Pointers List
    Shaders_.push_back(Shader);
    Cameras_.push_back(Camera);


}
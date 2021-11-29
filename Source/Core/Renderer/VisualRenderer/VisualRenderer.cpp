//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the visual renderer.
    Additonal Notes: None
    Date Created: 2021-11-20
*/

#include <VisualRenderer.h>









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

    Logger_->Log("Setting Up Window Input Processor", 5);
    InputProcessor_ = new InputProcessor(&Camera_, Window_, FramebufferManager_);


}

VisualRenderer::~VisualRenderer() {

    // Cleanup
    Logger_->Log("Cleaning Up OpenGL/GLFW", 0);
    glfwTerminate();

}





void VisualRenderer::InitializeOpenGL() {

    // Setup GUI
    GuiSystem_ = new GUISystem(Logger_, Window_);

    // Setup Viewport
    Logger_->Log("Read Configuration File For 'RenderWidth' Parameter", 1);
    RenderWidth_ = (*SystemConfiguration_)["RenderWidth"].as<int>();
    Logger_->Log("Read Configuration File For 'RenderHeight' Parameter", 1);
    RenderHeight_ = (*SystemConfiguration_)["RenderHeight"].as<int>();

    // Register Callback
    glfwMakeContextCurrent(Window_);
    //glfwSwapInterval(0);

    // Disable Mouse Capture By Default
    CaptureMouseCursor_ = false;

    // Setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger_->Log("Failed To Initialize GLAD", 10);
    }


    // Enable Scissor Test
    //glEnable(GL_SCISSOR_TEST);
    glEnable(GL_DEBUG_OUTPUT);


    // Setup Shaders
    ShaderLoader_ = new ShaderLoader(Logger_);
    Shader_ = ShaderLoader_->LoadShaderFromFile("Shaders/Main.vert", "Shaders/Main.frag");

    // Setup Framebuffer
    FramebufferManager_ = new FramebufferManager(Logger_, ShaderLoader_, WindowWidth_, WindowHeight_);


    // Load Model
    ModelLoader MLoader(Logger_, TextureLoader_);

    SceneLoader SLoader(Logger_, &MLoader);
    SceneManager_ = new SceneManager(Logger_);

    // Test Scene
    YAML::Node TestScene = YAML::LoadFile("Assets/Scene.yaml");
    SceneManager_->AddScene(SLoader.ProcessScene(TestScene));


    



    Shader_.MakeActive();
    Shader_.SetInt("texture_diffuse1", 0);





}

void VisualRenderer::UpdateLoop(float DeltaTime) {



    // Start Framebuffer Render Pass
    FramebufferManager_->StartFramebufferRenderPass();

    // Update GUI
    GuiSystem_->UpdateGUI();

    // Rendering Commands Here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use Shader
    Shader_.MakeActive();

    // Update Camera
    glfwGetFramebufferSize(Window_, &RenderWidth_, &RenderHeight_);
    float AspectRatio = (float)RenderWidth_ / (float)RenderHeight_;


    glm::mat4 projection = glm::perspective(glm::radians(Camera_.Zoom), AspectRatio, 0.1f, 100.0f);
    glm::mat4 view = Camera_.GetViewMatrix();
    Shader_.SetMat4("projection", projection);
    Shader_.SetMat4("view", view);

    // Draw Grid
    //DrawGrid();

    // Draw Models
    SceneManager_->Render(&Shader_);


    


    // Start Screen Render Pass
    FramebufferManager_->StartScreenRenderPass(true);
    


    // Update GUI Frame
    GuiSystem_->UpdateFrame();
    

    // Update Window Stuff
    glfwSwapBuffers(Window_);



    // Check If System Should Shutdown
    if (glfwWindowShouldClose(Window_)) {
        Logger_->Log("System Shutdown Invoked By LocalWindow", 2);
        *SystemShouldRun_ = false;
    }

}
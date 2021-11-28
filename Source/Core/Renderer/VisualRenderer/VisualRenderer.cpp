//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the visual renderer.
    Additonal Notes: None
    Date Created: 2021-11-20
*/

#include <VisualRenderer.h>





void ErrorCallback(int, const char* ErrorString) {
    std::cout<<"GLFW ERROR: " << ErrorString << std::endl;
}




VisualRenderer::VisualRenderer (YAML::Node *SystemConfiguration, LoggerClass *Logger, bool *SystemShouldRun) {

    // Create Pointers
    Logger->Log("Populating Renderer Member Pointers", 5);
    SystemConfiguration_ = SystemConfiguration;
    Logger_ = Logger;
    SystemShouldRun_ = SystemShouldRun;

    // Initialize Texture Loader
    TextureLoader_ = new TextureLoader(Logger_);

    // Initialize Systems
    Logger_->Log("Initializing GLFW", 5);
    InitializeGLFW();

    Logger_->Log("Setting Up Window Input Processor", 5);
    InputProcessor_ = new InputProcessor(&Camera_, Window_);

    Logger_->Log("Initializing OpenGL", 5);
    InitializeOpenGL();

}

VisualRenderer::~VisualRenderer() {

    // Cleanup
    Logger_->Log("Cleaning Up OpenGL/GLFW", 0);
    glfwTerminate();

}



void VisualRenderer::InitializeGLFW() {

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Read Out Width, Height
    Logger_->Log("Read Configuration File For 'WindowWidth' Parameter", 1);
    WindowWidth_ = (*SystemConfiguration_)["WindowWidth"].as<int>();
    Logger_->Log("Read Configuration File For 'WindowHeight' Parameter", 1);
    WindowHeight_ = (*SystemConfiguration_)["WindowHeight"].as<int>();
    Logger_->Log("Read Configuration File For 'WindowTitle' Parameter", 1);
    WindowTitle_ = (*SystemConfiguration_)["WindowTitle"].as<std::string>().c_str();

    //glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

    // Create Window Object
    glfwSetErrorCallback(ErrorCallback);
    Window_ = glfwCreateWindow(WindowWidth_, WindowHeight_, WindowTitle_, NULL, NULL);
    if (Window_ == NULL) {
        glfwTerminate();
    }

    glfwMakeContextCurrent(Window_);

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


    // Draw Faces In Front First
    glEnable(GL_DEPTH_TEST);

    // Enable Scissor Test
    glEnable(GL_SCISSOR_TEST);

    // Setup Shaders
    ShaderLoader_ = new ShaderLoader(Logger_);
    Shader_ = ShaderLoader_->LoadShaderFromFile("Shaders/Main.vert", "Shaders/Main.frag");




    // Load Model
    ModelLoader MLoader(Logger_, TextureLoader_);

    SceneLoader SLoader(Logger_, &MLoader);
    SceneManager_ = new SceneManager(Logger_);

    // Test Scene
    YAML::Node TestScene = YAML::LoadFile("Assets/Scene.yaml");
    SceneManager_->AddScene(SLoader.ProcessScene(TestScene));


    



    Shader_.MakeActive();





}

void VisualRenderer::UpdateLoop() {



    // Update DeltaTime
    float CurrentTime = glfwGetTime();
    DeltaTime = CurrentTime - LastFrame;
    LastFrame = CurrentTime;

    // Process Window Input
    glfwPollEvents();

    // Get IMGUI IO State
    auto Io = &ImGui::GetIO();
    //&& (Io->WantCaptureKeyboard)

    // Enable/Disable Mouse Capture
    if ((glfwGetMouseButton(Window_, 0) == GLFW_PRESS) && (!Io->WantCaptureMouse) ){
        CaptureMouseCursor_ = true;
    } else {
        CaptureMouseCursor_ = false;
    }


    InputProcessor_->ProcessKeyboardInput(Logger_, DeltaTime, CaptureMouseCursor_);
    InputProcessor_->UpdateFramebuffer();
    InputProcessor_->UpdateMouse(CaptureMouseCursor_);


    // Update Mouse Capture State
    if (CaptureMouseCursor_) {
        glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }





    // Update GUI
    GuiSystem_->UpdateGUI();

    // Rendering Commands Here
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





    // Use Shader
    Shader_.MakeActive();


    // Initialize Camera
    glm::mat4 projection = glm::perspective(glm::radians(Camera_.Zoom), (float)RenderWidth_ / (float)RenderHeight_, 0.1f, 100.0f);
    glm::mat4 view = Camera_.GetViewMatrix();
    Shader_.SetMat4("projection", projection);
    Shader_.SetMat4("view", view);

    // Draw Grid
    DrawGrid();

    // Draw Models
    SceneManager_->Render(&Shader_);


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
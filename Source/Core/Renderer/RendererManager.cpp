//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the renderer manager.
    Additonal Notes: None
    Date Created: 2021-11-01
*/

#include "RendererManager.h"


// FIXME! MAKE MORE CLEAN LOOKING OR SOMETHING
void ErrorCallback(int, const char* ErrorString) {
    std::cout<<"GLFW ERROR: " << ErrorString << std::endl;
}



// RendererManager Constructor
RendererManager::RendererManager(YAML::Node *SystemConfiguration, LoggerClass *Logger, bool *SystemShouldRun) {

    // Create Pointers
    Logger->Log("Populating RendererManager Member Pointers", 5);
    SystemConfiguration_ = SystemConfiguration;
    Logger_ = Logger;
    SystemShouldRun_ = SystemShouldRun;

    // Setup 3D Cursor
    Cursors3D_ = new Cursors3D();


    // Initialize Systems
    Logger_->Log("Initializing GLFW", 5);
    InitializeGLFW();

    // Instantiate Renderers
    Logger_->Log("Instantiating Renderers", 5);
    VisualRenderer_ = new VisualRenderer(SystemConfiguration, Window_, Logger, Cursors3D_);

    // Setup Shaders
    ShaderLoader_ = new ShaderLoader(Logger_);
    Shader_ = ShaderLoader_->LoadShaderFromFile("Shaders/Main.vert", "Shaders/Main.frag");

    Shader_.MakeActive();
    Shader_.SetInt("texture_diffuse1", 0);

    // Setup GUI
    GuiSystem_ = new GUISystem(Logger_, Window_, SystemShouldRun_, Cursors3D_, SceneManager_);

    // Setup IOManager
    Logger_->Log("Initializing Input/Output Manager", 5);
    IOManager_ = new IOManager(Logger_, Window_, &Camera_);

    // Make Viewport
    VisualRenderer_->CreateViewport(&Shader_, "Viewport", Window_, &Camera_);
    //VisualRenderer_->CreateViewport(&Shader_, "Viewport 2", Window_, &Camera_);

    // Initialize Texture Loader
    TextureLoader_ = new TextureLoader(Logger_);


    // Load Scene
    ModelLoader MLoader(Logger_, TextureLoader_);
    SceneLoader SLoader(Logger_, &MLoader);
    SceneManager_ = new SceneManager(Logger_);


    // Test Scene
    YAML::Node TestScene = YAML::LoadFile("Assets/Scene.yaml");
    SceneManager_->AddScene(SLoader.ProcessScene(TestScene));


}

// RendererManager Destructor
RendererManager::~RendererManager() {

    // Log Destructor Call
    Logger_->Log("RendererManager Destructor Called", 6);

}


// Initialize Window
void RendererManager::InitializeGLFW() {

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

    // Create Window Object
    glfwSetErrorCallback(ErrorCallback);
    Window_ = glfwCreateWindow(WindowWidth_, WindowHeight_, WindowTitle_, NULL, NULL);
    if (Window_ == NULL) {
        glfwTerminate();
    }

    // Bring Window To Front
    glfwMakeContextCurrent(Window_);

}



void RendererManager::UpdateLoop(float DeltaTime) { 


    // Update IO
    IOManager_->UpdateFrame(DeltaTime);

    // Update GUI
    GuiSystem_->UpdateGUI();

    // Call Updates
    VisualRenderer_->UpdateViewports(DeltaTime, SceneManager_);

    // Deferred GUI
    GuiSystem_->DeferredFrameUpdate();


    // Update GUI Frame
    ImVec4 Color = GuiSystem_->ThemeManager_->ClearColor_;
    glClearColor(Color.x, Color.y, Color.z, Color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    GuiSystem_->UpdateFrame();
    

    // Update Window Stuff
    glfwSwapBuffers(Window_);

    // Check If System Should Shutdown
    if (glfwWindowShouldClose(Window_)) {
        Logger_->Log("System Shutdown Invoked By LocalWindow", 2);
        *SystemShouldRun_ = false;
    }


}





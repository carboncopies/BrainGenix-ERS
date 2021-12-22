//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the renderer manager.
    Additonal Notes: None
    Date Created: 2021-11-01
*/

#include <RendererManager.h>


// FIXME! MAKE MORE CLEAN LOOKING OR SOMETHING
void ErrorCallback(int, const char* ErrorString) {
    std::cout<<"GLFW ERROR: " << ErrorString << std::endl;
}



// RendererManager Constructor
RendererManager::RendererManager(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Create Pointers
    SystemUtils->Logger_->Log("Populating RendererManager Member Pointers", 5);
    SystemUtils_ = SystemUtils;

    // Setup 3D Cursor
    Cursors3D_ = std::make_shared<Cursors3D>();


    // Initialize Texture Loader
    TextureLoader_ = std::make_shared<TextureLoader>(SystemUtils_->Logger_);


    // Load Scene
    ModelLoader MLoader(SystemUtils_->Logger_, TextureLoader_);
    SceneLoader SLoader(SystemUtils_->Logger_, std::make_shared<ModelLoader>(MLoader));
    SceneManager_ = std::make_shared<SceneManager>(SystemUtils_->Logger_);


    // Initialize Systems
    SystemUtils_->Logger_->Log("Initializing GLFW", 5);
    InitializeGLFW();

    // Instantiate Renderers
    SystemUtils_->Logger_->Log("Instantiating Renderers", 5);
    VisualRenderer_ = std::make_shared<VisualRenderer>(SystemUtils_, Window_, Cursors3D_);

    // Setup Shaders
    ShaderLoader_ = std::make_shared<ShaderLoader>(SystemUtils_->Logger_);
    Shader_ = ShaderLoader_->LoadShaderFromFile("Shaders/Main.vert", "Shaders/Main.frag");

    Shader_.MakeActive();
    Shader_.SetInt("texture_diffuse1", 0);

    // Setup GUI
    GuiSystem_ = std::make_shared<GUISystem>(SystemUtils_, Window_, Cursors3D_, SceneManager_);

    // Setup IOManager
    SystemUtils_->Logger_->Log("Initializing Input/Output Manager", 5);
    IOManager_ = std::make_shared<IOManager>(SystemUtils_->Logger_, Window_, std::make_shared<ERS_OBJECT_CAMERA_NOCLIP>(Camera_));

    // Setup Loading Subsystem
    ModelLoader_ = std::make_unique<ERS_CLASS_ModelLoader>(SystemUtils_);

    std::shared_ptr<ERS_OBJECT_MODEL> Test2 = std::make_shared<ERS_OBJECT_MODEL>();
    ModelLoader_->LoadModel(6, Test2);
    ModelLoader_->ProcessGPU(Test2);

    // Make Viewport
    VisualRenderer_->CreateViewport(std::make_shared<ERS_OBJECT_SHADER>(Shader_), "Viewport", Window_, std::make_shared<ERS_OBJECT_CAMERA_NOCLIP>(Camera_));
    //VisualRenderer_->CreateViewport(&Shader_, "Viewport 2", Window_, &Camera_);


    // Test Scene
    YAML::Node TestScene = YAML::LoadFile("Assets/Scene.yaml");
    YAML::Node TestScene2 = YAML::LoadFile("Assets/Scene2.yaml");
    YAML::Node TestScene3 = YAML::LoadFile("Assets/Scene3.yaml");
    
    SceneManager_->AddScene(SLoader.ProcessScene(TestScene, "Assets/Scene.yaml", false));
    SceneManager_->AddScene(SLoader.ProcessScene(TestScene2, "Assets/Scene2.yaml", false));
    SceneManager_->AddScene(SLoader.ProcessScene(TestScene3, "Assets/Scene3.yaml", false));




}

// RendererManager Destructor
RendererManager::~RendererManager() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("RendererManager Destructor Called", 6);

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
    SystemUtils_->Logger_->Log("Read Configuration File For 'WindowWidth' Parameter", 1);
    WindowWidth_ = (*SystemUtils_->LocalSystemConfiguration_)["WindowWidth"].as<int>();
    SystemUtils_->Logger_->Log("Read Configuration File For 'WindowHeight' Parameter", 1);
    WindowHeight_ = (*SystemUtils_->LocalSystemConfiguration_)["WindowHeight"].as<int>();
    SystemUtils_->Logger_->Log("Read Configuration File For 'WindowTitle' Parameter", 1);
    WindowTitle_ = (*SystemUtils_->LocalSystemConfiguration_)["WindowTitle"].as<std::string>().c_str();

    // Create Window Object
    glfwSetErrorCallback(ErrorCallback);
    Window_ = glfwCreateWindow(WindowWidth_, WindowHeight_, WindowTitle_, NULL, NULL);
    if (Window_ == NULL) {
        glfwTerminate();
    }


    // Load Icon
    SystemUtils_->Logger_->Log("Loading System Icon From EditorAssets", 3);
    FreeImage_Initialise();

    // Load Image
    FREE_IMAGE_FORMAT Format = FreeImage_GetFileType("EditorAssets/Icons/ProgramIcon/Icon.png", 0);
    FIBITMAP* ImageData = FreeImage_Load(Format, "EditorAssets/Icons/ProgramIcon/Icon.png");

    // Apply Icon
    SystemUtils_->Logger_->Log("Applying System Icon", 4);
    GLFWimage Icon[1];
    FreeImage_FlipVertical(ImageData);
    Icon[0].pixels = FreeImage_GetBits(ImageData);
    Icon[0].width = (int)FreeImage_GetWidth(ImageData);
    Icon[0].height = (int)FreeImage_GetHeight(ImageData);
    glfwSetWindowIcon(Window_, 1, Icon);

    FreeImage_DeInitialise();


    // Bring Window To Front
    glfwMakeContextCurrent(Window_);

}



void RendererManager::UpdateLoop(float DeltaTime) { 

    // Update Scene
    //ModelLoader_->ProcessNewModels(std::make_shared<ERS_OBJECT_SCENE>(SceneManager_->Scenes_[SceneManager_->ActiveScene_]));

    // Update IO
    IOManager_->UpdateFrame(DeltaTime);
    int Width, Height;
    glfwGetWindowSize(Window_, &Width, &Height);
    SystemUtils_->RenderWidth_ = Width;
    SystemUtils_->RenderHeight_ = Height;

    // Update GUI
    GuiSystem_->UpdateGUI();

    // Call Updates
    VisualRenderer_->UpdateViewports(DeltaTime, SceneManager_);


    // Update GUI Frame
    ImVec4 Color = GuiSystem_->ThemeManager_->ClearColor_;
    glClearColor(Color.x, Color.y, Color.z, Color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    GuiSystem_->UpdateFrame();
    

    // Update Window Stuff
    glfwSwapBuffers(Window_);

    // Check If System Should Shutdown
    if (glfwWindowShouldClose(Window_)) {
        SystemUtils_->Logger_->Log("System Shutdown Invoked By LocalWindow", 2);
        *SystemUtils_->SystemShouldRun_ = false;
    }


}





//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <RendererManager.h>


// FIXME! MAKE MORE CLEAN LOOKING OR SOMETHING
void ErrorCallback(int, const char* ErrorString) {
    std::cout<<"GLFW ERROR: " << ErrorString << std::endl;
}



RendererManager::RendererManager(ERS_STRUCT_SystemUtils* SystemUtils, std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils, std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils) {

    SystemUtils->Logger_->Log("Populating RendererManager Member Pointers", 5);
    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    HIDUtils_ = HIDUtils;

    Cursors3D_ = std::make_shared<Cursors3D>();


    SystemUtils_->Logger_->Log("Initializing GLFW", 5);
    InitializeGLFW();

    SystemUtils_->Logger_->Log("Instantiating Renderers", 5);
    VisualRenderer_ = std::make_shared<ERS_CLASS_VisualRenderer>(SystemUtils_, Window_, Cursors3D_);

    // Setup Shaders
    ShaderLoader_ = std::make_shared<ERS_CLASS_ShaderLoader>(SystemUtils_);
    for (int i = 0; i < ProjectUtils_->ProjectManager_->Project_.ShaderPrograms.size(); i++) {
        long VertexShaderID = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[i].VertexID;
        long FragmentShaderID = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[i].FragmentID;
        std::string ShaderName = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[i].Name;
        Shader_ = ShaderLoader_->LoadShaderFromAsset(VertexShaderID, FragmentShaderID, ShaderName);
        Shader_->MakeActive(SystemUtils_->Logger_);
        Shader_->SetInt("texture_diffuse1", 0);
        VisualRenderer_->SetShader(Shader_, i);
    }
    int DefaultShader = ProjectUtils_->ProjectManager_->Project_.DefaultShaderProgram;
    VisualRenderer_->SetDefaultShader(DefaultShader);

    GuiSystem_ = std::make_shared<GUISystem>(SystemUtils_, Window_, Cursors3D_, ProjectUtils_->SceneManager_, ProjectUtils_, VisualRenderer_, HIDUtils_);

    VisualRenderer_->CreateViewport();

}


RendererManager::~RendererManager() {

    SystemUtils_->Logger_->Log("RendererManager Destructor Called", 6);

}


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



    // Create Default Texture
    SystemUtils_->Logger_->Log("Loading System Default Texture From EditorAssets", 3);
    FREE_IMAGE_FORMAT DefaultTexFormat = FreeImage_GetFileType("EditorAssets/Icons/DefaultTexture/DefaultTexture1024.png", 0);
    FIBITMAP* DefaulTexImageData = FreeImage_Load(DefaultTexFormat, "EditorAssets/Icons/DefaultTexture/DefaultTexture1024.png");
    unsigned char* RawImageData = FreeImage_GetBits(DefaulTexImageData);
    int Width = FreeImage_GetWidth(DefaulTexImageData);
    int Height = FreeImage_GetHeight(DefaulTexImageData);
    int Channels = FreeImage_GetLine(DefaulTexImageData) / FreeImage_GetWidth(DefaulTexImageData);
    FreeImage_Unload(DefaulTexImageData);


    glGenTextures(1, &DefaultTextureID_);
    glBindTexture(GL_TEXTURE_2D, DefaultTextureID_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    if (Channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, RawImageData);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_BGR, GL_UNSIGNED_BYTE, RawImageData);
    }
    glGenerateMipmap(GL_TEXTURE_2D);




    FreeImage_DeInitialise();


    // Bring Window To Front, Unlock Framerate So Our Framerate System Is Used
    glfwMakeContextCurrent(Window_);
    glfwSwapInterval(0);

}



void RendererManager::UpdateLoop(float DeltaTime) { 

    // Update Window Title
    std::string SceneTitle = ProjectUtils_->ProjectManager_->Project_.ProjectName + std::string(" - BrainGenix-ERS");
    glfwSetWindowTitle(Window_, SceneTitle.c_str());

    // Update Scene
    ProjectUtils_->ModelLoader_->ProcessNewModels(ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]);

    // Update IO
    // Process Window Input
    glfwGetWindowSize(Window_, &WindowWidth_, &WindowHeight_);
    glfwPollEvents();
    //IOManager_->UpdateFrame(DeltaTime);

    int Width, Height;
    glfwGetWindowSize(Window_, &Width, &Height);
    SystemUtils_->RenderWidth_ = Width;
    SystemUtils_->RenderHeight_ = Height;

    // Update GUI
    GuiSystem_->UpdateGUI();

    // Call Updates
    VisualRenderer_->UpdateViewports(DeltaTime, ProjectUtils_->SceneManager_);


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
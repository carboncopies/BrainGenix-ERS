//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <RendererManager.h>
// cppcheck-suppress missingIncludeSystem
#include <Profiling.h>

// cppcheck-suppress missingIncludeSystem
#include <algorithm>
// cppcheck-suppress missingIncludeSystem
#include <cctype>
// cppcheck-suppress missingIncludeSystem
#include <cstdio>
// cppcheck-suppress missingIncludeSystem
#include <cstdlib>
// cppcheck-suppress missingIncludeSystem
#include <cstring>

#if defined(__unix__) && !defined(__APPLE__)
// cppcheck-suppress missingIncludeSystem
#include <EGL/egl.h>
// cppcheck-suppress missingIncludeSystem
#include <EGL/eglext.h>
#define ERS_RENDERERMANAGER_HAS_EGL 1
#endif


// In display-free offscreen mode GLFW is intentionally left uninitialized, so GLFW_NOT_INITIALIZED
// complaints from timer/input stubs are expected and are filtered out to keep the logs readable.
static bool SuppressGLFWNotInitializedErrors_ = false;

void ErrorCallback(int ErrorCode, const char* ErrorString) {
    if (SuppressGLFWNotInitializedErrors_ && ErrorCode == GLFW_NOT_INITIALIZED) {
        return;
    }
    const char* Message = ErrorString != nullptr ? ErrorString : "No error message provided";
    std::cerr<<"GLFW ERROR (" << ErrorCode << "): " << Message << std::endl;
}

#if defined(ERS_RENDERERMANAGER_HAS_EGL)
// Formats The Current EGL Error Code As A Hexadecimal String (eglGetError Returns Codes In The 0x3000 Range)
static std::string FormatEGLError() {
    char ErrorBuffer[16];
    std::snprintf(ErrorBuffer, sizeof(ErrorBuffer), "0x%04X", (int)eglGetError());
    return std::string(ErrorBuffer);
}
#endif



RendererManager::RendererManager(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_STRUCT_HumanInputDeviceUtils* HIDUtils) {

    SystemUtils->Logger_->Log("Populating RendererManager Member Pointers", 5);
    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    HIDUtils_ = HIDUtils;

    Cursors3D_ = std::make_unique<Cursors3D>();


    SystemUtils_->Logger_->Log("Initializing GLFW", 5);
    InitializeGLFW();

    SystemUtils_->Logger_->Log("Instantiating Renderers", 5);
    ERS_CLASS_ControllerInputManager* ControllerInputManager = nullptr;
    if (HIDUtils_ != nullptr) {
        ControllerInputManager = HIDUtils_->ControllerInputManager.get();
    }
    VisualRenderer_ = std::make_unique<ERS_CLASS_VisualRenderer>(SystemUtils_, ProjectUtils_, Window_, Cursors3D_.get(), ControllerInputManager);
    LoadEditorData();
    VisualRenderer_->SetOpenGLDefaults(OpenGLDefaults_.get());




    // Setup Shaders
    ShaderLoader_ = std::make_unique<ERS_CLASS_ShaderLoader>(SystemUtils_);
    for (int i = 0; (long)i < (long)ProjectUtils_->ProjectManager_->Project_.ShaderPrograms.size(); i++) {
        VisualRenderer_->Shaders_.push_back(std::make_unique<ERS_STRUCT_Shader>());
        ERS_STRUCT_Shader* Shader = VisualRenderer_->Shaders_[VisualRenderer_->Shaders_.size()-1].get();

        long VertexShaderID = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[i].VertexID;
        long FragmentShaderID = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[i].FragmentID;
        long GeometryShaderID = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[i].GeometryID;
        long ComputeShaderID = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[i].ComputeID;
        long TCShaderID = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[i].TCID;
        long TEShaderID = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[i].TEID;
        
        std::string ShaderName = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[i].Name;
        ShaderLoader_->LoadShaderFromAsset(Shader, VertexShaderID, FragmentShaderID, GeometryShaderID, ComputeShaderID, TCShaderID, TEShaderID, ShaderName);

    }
    int DefaultShader = ProjectUtils_->ProjectManager_->Project_.DefaultShaderProgram;
    VisualRenderer_->SetDefaultShader(DefaultShader);

    GuiSystem_ = std::make_shared<GUISystem>(SystemUtils_, Window_, Cursors3D_.get(), ProjectUtils_->SceneManager_.get(), ProjectUtils_, VisualRenderer_.get(), HIDUtils_);

    VisualRenderer_->CreateViewport();
    VisualRenderer_->IsEditorMode_ = !ProjectUtils_->ProjectManager_->Project_.StartPlayingOnLoad;

}


RendererManager::~RendererManager() {

    SystemUtils_->Logger_->Log("RendererManager Destructor Called", 6);

}

void RendererManager::LoadEditorData() {

    OpenGLDefaults_ = std::make_unique<ERS_STRUCT_OpenGLDefaults>();
    FreeImage_Initialise();
    

    // Load Program GLFW Icon
    SystemUtils_->Logger_->Log("Loading System Icon From EditorAssets", 3);
    FREE_IMAGE_FORMAT Format = FreeImage_GetFileType("EditorAssets/Icons/ProgramIcon/Icon.png", 0);
    FIBITMAP* ImageData = FreeImage_Load(Format, "EditorAssets/Icons/ProgramIcon/Icon.png");
    SystemUtils_->Logger_->Log("Applying System Icon", 4);
    GLFWimage Icon[1];
    FreeImage_FlipVertical(ImageData);
    Icon[0].pixels = FreeImage_GetBits(ImageData);
    Icon[0].width = (int)FreeImage_GetWidth(ImageData);
    Icon[0].height = (int)FreeImage_GetHeight(ImageData);
    if (Window_ != nullptr) {
        glfwSetWindowIcon(Window_, 1, Icon);
    }


    // Load Default Textures
    OpenGLDefaults_->DefaultTexture_ = LoadEditorIcon("EditorAssets/Icons/DefaultTexture/8x8/DefaultTexture1024.png");
    OpenGLDefaults_->Loadingtexture_ = LoadEditorIcon("EditorAssets/Icons/LoadingTexture/8x8/LoadingTexture1024.png");
    OpenGLDefaults_->AllBlackTexture_ = LoadEditorIcon("EditorAssets/Icons/AllBlackTexture/AllBlackTexture2.png");
    OpenGLDefaults_->AllWhiteTexture_ = LoadEditorIcon("EditorAssets/Icons/AllWhiteTexture/AllWhiteTexture2.png");
    OpenGLDefaults_->TransparentTexture_ = LoadEditorIcon("EditorAssets/Icons/TransparentTexture/TransparentTexture.png");

    // Load Editor Texture Icons
    OpenGLDefaults_->PointLightTexture_ = LoadEditorIcon("EditorAssets/Icons/LightingIcons/PointLight.png");
    OpenGLDefaults_->DirectionalLightTexture_ = LoadEditorIcon("EditorAssets/Icons/LightingIcons/DirectionalLight.png");
    OpenGLDefaults_->SpotLightTexture_ = LoadEditorIcon("EditorAssets/Icons/LightingIcons/SpotLight.png");

    OpenGLDefaults_->SceneCameraTexture_ = LoadEditorIcon("EditorAssets/Icons/CameraIcon/CameraIcon.png");


    FreeImage_DeInitialise();

}

unsigned int RendererManager::LoadEditorIcon(const char* Path) {


    SystemUtils_->Logger_->Log(std::string("Loading Editor Texture '") + std::string(Path) + std::string("'"), 3);

    FREE_IMAGE_FORMAT TexFormat = FreeImage_GetFileType(Path, 0);
    FIBITMAP* TexImageData = FreeImage_Load(TexFormat, Path);
    unsigned char* RawImageData = FreeImage_GetBits(TexImageData);
    int Width = FreeImage_GetWidth(TexImageData);
    int Height = FreeImage_GetHeight(TexImageData);
    int Channels = FreeImage_GetLine(TexImageData) / Width;

    unsigned int OpenGLTextureID;
    glGenTextures(1, &OpenGLTextureID);
    glBindTexture(GL_TEXTURE_2D, OpenGLTextureID);
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

    FreeImage_Unload(TexImageData);

    return OpenGLTextureID;

}

void RendererManager::InitializeGLFW() {

    // Read Out Width, Height
    SystemUtils_->Logger_->Log("Read Configuration File For 'WindowWidth' Parameter", 1);
    WindowWidth_ = (*SystemUtils_->LocalSystemConfiguration_)["WindowWidth"].as<int>();
    SystemUtils_->Logger_->Log("Read Configuration File For 'WindowHeight' Parameter", 1);
    WindowHeight_ = (*SystemUtils_->LocalSystemConfiguration_)["WindowHeight"].as<int>();
    SystemUtils_->Logger_->Log("Read Configuration File For 'WindowTitle' Parameter", 1);
    WindowTitle_ = (*SystemUtils_->LocalSystemConfiguration_)["WindowTitle"].as<std::string>();

    // Check If Display-Free Offscreen Mode Requested (No Window, No Display Connection At All)
    bool HeadlessOffscreenMode = false;
    for (std::pair<std::string, std::string>& Argument : SystemUtils_->Arguments_) {
        if (Argument.first == "Headless" && Argument.second == "offscreen") {
            HeadlessOffscreenMode = true;
            break;
        }
    }
    const char* OffscreenEnvironmentVariable = std::getenv("ERS_HEADLESS");
    if (OffscreenEnvironmentVariable != nullptr && std::string(OffscreenEnvironmentVariable) == "offscreen") {
        HeadlessOffscreenMode = true;
    }

    if (HeadlessOffscreenMode) {

        // Optional Explicit EGL Device Selection For Machines With Multiple Renderable Devices/GPUs
        // ('-EGLDeviceIndex <N>' Command Line Argument Or 'ERS_EGL_DEVICE_INDEX' Environment Variable)
        for (std::pair<std::string, std::string>& Argument : SystemUtils_->Arguments_) {
            if (Argument.first == "EGLDeviceIndex") {
                try {
                    OffscreenEGLDeviceIndex_ = std::stoi(Argument.second);
                } catch (...) {
                    SystemUtils_->Logger_->Log(std::string("Invalid EGLDeviceIndex Argument '") + Argument.second + std::string("', Ignoring"), 7);
                }
            }
        }
        const char* DeviceIndexEnvironmentVariable = std::getenv("ERS_EGL_DEVICE_INDEX");
        if (DeviceIndexEnvironmentVariable != nullptr) {
            OffscreenEGLDeviceIndex_ = std::atoi(DeviceIndexEnvironmentVariable);
        }

        InitializeEGLOffscreen();
        return;
    }

    // Initialize GLFW
    if (!glfwInit()) {
        SystemUtils_->Logger_->Log("Failed To Initialize GLFW (No Display Available?) - Cannot Create The Render Pipeline, Aborting ERS Startup", 10);
        std::exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    YAML::Node OffscreenRenderingNode = (*SystemUtils_->LocalSystemConfiguration_)["OffscreenRendering"];
    OffscreenRendering_ = OffscreenRenderingNode ? OffscreenRenderingNode.as<bool>() : false;

    YAML::Node OffscreenContextAPINode = (*SystemUtils_->LocalSystemConfiguration_)["OffscreenContextAPI"];
    std::string OffscreenContextAPI = OffscreenContextAPINode ? OffscreenContextAPINode.as<std::string>() : std::string("Native");
    std::transform(OffscreenContextAPI.begin(), OffscreenContextAPI.end(), OffscreenContextAPI.begin(), [](unsigned char Character) {
        return static_cast<char>(std::tolower(Character));
    });
    UseEGLContext_ = OffscreenRendering_ && (OffscreenContextAPI == "egl");

    if (OffscreenRendering_) {
        SystemUtils_->Logger_->Log("Offscreen rendering enabled, creating the main GLFW context as a hidden window", 3);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);

        if (UseEGLContext_) {
#ifdef GLFW_EGL_CONTEXT_API
            glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
            SystemUtils_->Logger_->Log("Requesting an EGL OpenGL context for off-screen rendering", 3);
#else
            UseEGLContext_ = false;
            SystemUtils_->Logger_->Log("This GLFW build does not expose GLFW_EGL_CONTEXT_API; falling back to the native OpenGL context API", 7);
#endif
        }
    }

    // Check If Headless Mode Requested (Hides The Window, But Keeps The GL Context And Render Pipeline Running)
    bool HeadlessMode = false;
    for (std::pair<std::string, std::string>& Argument : SystemUtils_->Arguments_) {
        if (Argument.first == "Headless" && Argument.second == "true") {
            HeadlessMode = true;
            break;
        }
    }
    const char* HeadlessEnvironmentVariable = std::getenv("ERS_HEADLESS");
    if (HeadlessEnvironmentVariable != nullptr && std::string(HeadlessEnvironmentVariable) == "1") {
        HeadlessMode = true;
    }

    if (HeadlessMode) {
        SystemUtils_->Logger_->Log("Headless Mode Enabled: Window Will Be Hidden", 5);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    }

    // Create Window Object
    glfwSetErrorCallback(ErrorCallback);
    Window_ = glfwCreateWindow(WindowWidth_, WindowHeight_, WindowTitle_.c_str(), NULL, NULL);
    if (Window_ == NULL) {
        SystemUtils_->Logger_->Log("Failed To Create GLFW Window (No Display Available?) - Cannot Continue Without A Valid OpenGL Context, Aborting ERS Startup", 10);
        glfwTerminate();
        std::exit(1);
    }


    // Bring Window To Front, Unlock Framerate So Our Framerate System Is Used
    glfwMakeContextCurrent(Window_);
    if (OffscreenRendering_) {
        glfwSwapInterval(0);
        std::string ContextMessage = UseEGLContext_
            ? std::string("Running renderer without presenting a visible GLFW window using an EGL context")
            : std::string("Running renderer without presenting a visible GLFW window using the native context API");
        SystemUtils_->Logger_->Log(ContextMessage.c_str(), 3);
    } else {
        glfwSwapInterval(1);
    }



    // Setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SystemUtils_->Logger_->Log("Failed To Initialize GLAD", 10);
    }

    // Setup OpenGL For Blending (For Transparency Issues)
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


    // Setup Texture Streamer
    SystemUtils_->Logger_->Log("Initializing Texture Streaming Subsystem", 5);
    ProjectUtils_->ModelLoader_->AssetStreamingManager_->SetupTextureStreamer(Window_);
    SystemUtils_->Logger_->Log("Finished Initializing Texture Streaming Subsystem", 4);



}

void RendererManager::InitializeEGLOffscreen() {

#if defined(ERS_RENDERERMANAGER_HAS_EGL)

    // Announce Display-Free Offscreen Mode
    SystemUtils_->Logger_->Log("Headless Offscreen Mode Enabled: Creating Display-Free EGL OpenGL Context (No Window, No Display Connection)", 5);
    HeadlessOffscreenMode_ = true;
    SuppressGLFWNotInitializedErrors_ = true;
    glfwSetErrorCallback(ErrorCallback);

    // Attempt GLFW Initialization Anyway For Timer/Input Stubs; Failure Without A Display Is Expected And Safe Here
    if (!glfwInit()) {
        SystemUtils_->Logger_->Log("GLFW Initialization Failed (Expected Without A Display) - Timing And Input Stubs Will Be Inactive In Offscreen Mode", 6);
    }


    // Enumerate EGL Devices And Try The EGL_EXT_platform_device Platform First (Works On NVIDIA Proprietary Drivers)
    PFNEGLGETPLATFORMDISPLAYEXTPROC GetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
    PFNEGLQUERYDEVICESEXTPROC QueryDevicesEXT = (PFNEGLQUERYDEVICESEXTPROC)eglGetProcAddress("eglQueryDevicesEXT");
    const char* ClientExtensions = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
    bool HasPlatformDeviceExtension = (ClientExtensions != nullptr) && (std::strstr(ClientExtensions, "EGL_EXT_platform_device") != nullptr);

    EGLDisplay DisplayHandle = EGL_NO_DISPLAY;
    std::string PlatformDescription;
    std::string AttemptSummary;

    if (HasPlatformDeviceExtension && GetPlatformDisplayEXT != nullptr && QueryDevicesEXT != nullptr) {
        EGLDeviceEXT Devices[16];
        EGLint NumDevices = 0;
        if (QueryDevicesEXT(16, Devices, &NumDevices) == EGL_TRUE) {
            SystemUtils_->Logger_->Log(std::string("EGL Enumerated ") + std::to_string((int)NumDevices) + std::string(" Device(s) For Offscreen Rendering"), 3);
            if (OffscreenEGLDeviceIndex_ >= 0) {
                SystemUtils_->Logger_->Log(std::string("Using Explicitly Requested EGL Device Index ") + std::to_string(OffscreenEGLDeviceIndex_), 5);
                if (OffscreenEGLDeviceIndex_ >= (int)NumDevices) {
                    SystemUtils_->Logger_->Log(std::string("Requested EGL Device Index ") + std::to_string(OffscreenEGLDeviceIndex_)
                        + std::string(" But EGL Only Enumerated ") + std::to_string((int)NumDevices) + std::string(" Device(s)"), 10);
                    std::exit(1);
                }
            }
            int FirstDeviceIndex = (OffscreenEGLDeviceIndex_ >= 0) ? OffscreenEGLDeviceIndex_ : 0;
            int LastDeviceIndexExclusive = (OffscreenEGLDeviceIndex_ >= 0) ? OffscreenEGLDeviceIndex_ + 1 : (int)NumDevices;
            for (int i = FirstDeviceIndex; i < LastDeviceIndexExclusive; i++) {
                EGLDisplay CandidateDisplay = GetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, Devices[i], NULL);
                if (CandidateDisplay == EGL_NO_DISPLAY) {
                    AttemptSummary += std::string(" device[") + std::to_string(i) + std::string("]: eglGetPlatformDisplay failed;");
                    continue;
                }
                EGLint MajorVersion = 0;
                EGLint MinorVersion = 0;
                if (eglInitialize(CandidateDisplay, &MajorVersion, &MinorVersion) == EGL_TRUE) {
                    DisplayHandle = CandidateDisplay;
                    PlatformDescription = std::string("EGL_EXT_platform_device, device ") + std::to_string(i)
                        + std::string(", EGL ") + std::to_string((int)MajorVersion) + std::string(".") + std::to_string((int)MinorVersion);
                    break;
                }
                AttemptSummary += std::string(" device[") + std::to_string(i) + std::string("]: eglInitialize failed (error ")
                    + FormatEGLError() + std::string(");");
            }
        } else {
            AttemptSummary += std::string(" EGL_EXT_device_enumeration: eglQueryDevicesEXT failed (error ") + FormatEGLError() + std::string(");");
        }
    } else {
        AttemptSummary += " EGL_EXT_platform_device unavailable;";
    }


    // Fallback To The Surfaceless Mesa Platform (Works On Mesa And Some Other Drivers)
    if (DisplayHandle == EGL_NO_DISPLAY) {
        bool HasSurfacelessExtension = (ClientExtensions != nullptr) && (std::strstr(ClientExtensions, "EGL_MESA_platform_surfaceless") != nullptr);
        if (HasSurfacelessExtension) {
#ifdef EGL_PLATFORM_SURFACELESS_MESA
            EGLDisplay CandidateDisplay = EGL_NO_DISPLAY;
            if (GetPlatformDisplayEXT != nullptr) {
                CandidateDisplay = GetPlatformDisplayEXT(EGL_PLATFORM_SURFACELESS_MESA, EGL_DEFAULT_DISPLAY, NULL);
            } else {
                CandidateDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
            }
            if (CandidateDisplay != EGL_NO_DISPLAY) {
                EGLint MajorVersion = 0;
                EGLint MinorVersion = 0;
                if (eglInitialize(CandidateDisplay, &MajorVersion, &MinorVersion) == EGL_TRUE) {
                    DisplayHandle = CandidateDisplay;
                    PlatformDescription = std::string("EGL_MESA_platform_surfaceless, EGL ") + std::to_string((int)MajorVersion)
                        + std::string(".") + std::to_string((int)MinorVersion);
                } else {
                    AttemptSummary += std::string(" surfaceless: eglInitialize failed (error ") + FormatEGLError() + std::string(");");
                }
            } else {
                AttemptSummary += " surfaceless: no display handle;";
            }
#else
            AttemptSummary += " surfaceless platform constant unavailable in EGL headers;";
#endif
        } else {
            AttemptSummary += " EGL_MESA_platform_surfaceless unavailable;";
        }
    }

    if (DisplayHandle == EGL_NO_DISPLAY) {
        SystemUtils_->Logger_->Log(std::string("Failed To Initialize Any EGL Platform For Display-Free Offscreen Rendering. Attempts:") + AttemptSummary, 10);
        std::exit(1);
    }
    SystemUtils_->Logger_->Log(std::string("Selected EGL Platform For Offscreen Rendering: ") + PlatformDescription, 5);


    // Bind The OpenGL API (Not OpenGL ES)
    if (eglBindAPI(EGL_OPENGL_API) != EGL_TRUE) {
        SystemUtils_->Logger_->Log("EGL Failed To Bind The Desktop OpenGL API For Offscreen Rendering", 10);
        std::exit(1);
    }


    // Choose An Offscreen Config: Pbuffer+OpenGL-Renderable Config Preferred, Minimal Config As Fallback
    EGLint PreferredConfigAttributes[] = {
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };
    EGLint MinimalConfigAttributes[] = {
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_NONE
    };
    EGLConfig ChosenConfig = nullptr;
    EGLint NumConfigs = 0;
    if (eglChooseConfig(DisplayHandle, PreferredConfigAttributes, &ChosenConfig, 1, &NumConfigs) != EGL_TRUE || NumConfigs < 1) {
        SystemUtils_->Logger_->Log("Preferred EGL Pbuffer Config Unavailable, Retrying With Minimal Attributes", 6);
        if (eglChooseConfig(DisplayHandle, MinimalConfigAttributes, &ChosenConfig, 1, &NumConfigs) != EGL_TRUE || NumConfigs < 1) {
            SystemUtils_->Logger_->Log(std::string("Failed To Find Any EGL Pbuffer Config For Offscreen Rendering (error ") + FormatEGLError() + std::string(")"), 10);
            std::exit(1);
        }
    }


    // Create The Offscreen OpenGL Core Context. The GLX/GLFW Path Hands Out The Highest Core Version The Driver
    // Offers (4.6 On Current NVIDIA Drivers), So Request 4.6 Down To 4.1 - 4.1 Remains The Minimum Acceptable
    // Version And Matches The GLFW Context Hints Used In Windowed Mode.
    EGLContext ContextHandle = EGL_NO_CONTEXT;
    for (int MinorVersion = 6; ContextHandle == EGL_NO_CONTEXT && MinorVersion >= 1; MinorVersion--) {
        EGLint ContextAttributes[] = {
            EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
            EGL_CONTEXT_MAJOR_VERSION_KHR, 4,
            EGL_CONTEXT_MINOR_VERSION_KHR, MinorVersion,
            EGL_NONE
        };
        ContextHandle = eglCreateContext(DisplayHandle, ChosenConfig, EGL_NO_CONTEXT, ContextAttributes);
    }
    if (ContextHandle == EGL_NO_CONTEXT) {
        SystemUtils_->Logger_->Log(std::string("EGL Failed To Create Any OpenGL Core Context (Tried 4.6 Down To 4.1) For Offscreen Rendering (error ") + FormatEGLError() + std::string(")"), 10);
        std::exit(1);
    }


    // Create A Tiny Pbuffer Surface (The Render Pipeline Outputs To Its Own Framebuffer Objects, So Size Is Irrelevant) Or Go Surfaceless If Supported
    const char* DisplayExtensions = eglQueryString(DisplayHandle, EGL_EXTENSIONS);
    bool HasSurfacelessContext = (DisplayExtensions != nullptr) && (std::strstr(DisplayExtensions, "EGL_KHR_surfaceless_context") != nullptr);
    EGLint PbufferAttributes[] = {
        EGL_WIDTH, 1,
        EGL_HEIGHT, 1,
        EGL_NONE
    };
    EGLSurface SurfaceHandle = eglCreatePbufferSurface(DisplayHandle, ChosenConfig, PbufferAttributes);
    if (SurfaceHandle == EGL_NO_SURFACE) {
        if (HasSurfacelessContext) {
            SystemUtils_->Logger_->Log("EGL Pbuffer Creation Failed, Falling Back To Surfaceless Context Via EGL_KHR_surfaceless_context", 6);
            SurfaceHandle = EGL_NO_SURFACE;
        } else {
            SystemUtils_->Logger_->Log(std::string("EGL Failed To Create An Offscreen Pbuffer Surface (error ") + FormatEGLError() + std::string(")"), 10);
            std::exit(1);
        }
    }

    if (eglMakeCurrent(DisplayHandle, SurfaceHandle, SurfaceHandle, ContextHandle) != EGL_TRUE) {
        SystemUtils_->Logger_->Log(std::string("EGL Failed To Make The Offscreen Context Current (error ") + FormatEGLError() + std::string(")"), 10);
        std::exit(1);
    }

    EGLOffscreenDisplay_ = (void*)DisplayHandle;
    EGLOffscreenConfig_  = (void*)ChosenConfig;
    EGLOffscreenContext_ = (void*)ContextHandle;
    EGLOffscreenSurface_ = (void*)SurfaceHandle;
    SystemUtils_->Logger_->Log("EGL Offscreen OpenGL Context Created Successfully", 5);


    // Setup GLAD Through The EGL Loader (Symbol Queries Must Resolve Via eglGetProcAddress In Offscreen Mode)
    if (!gladLoadGLLoader((GLADloadproc)eglGetProcAddress)) {
        SystemUtils_->Logger_->Log("Failed To Initialize GLAD", 10);
        std::exit(1);
    }
    const GLubyte* GLVersionString = glGetString(GL_VERSION);
    const GLubyte* GLRendererString = glGetString(GL_RENDERER);
    std::string GLInfoMessage = std::string("EGL Offscreen OpenGL Context Reporting Version '")
        + std::string(GLVersionString != nullptr ? (const char*)GLVersionString : "Unknown")
        + std::string("' On Renderer '")
        + std::string(GLRendererString != nullptr ? (const char*)GLRendererString : "Unknown")
        + std::string("'");
    SystemUtils_->Logger_->Log(GLInfoMessage, 3);



    // Setup OpenGL For Blending (For Transparency Issues)
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


    // Setup Texture Streamer (Shared EGL Pbuffer Contexts Replace The Hidden GLFW Windows In Offscreen Mode)
    SystemUtils_->Logger_->Log("Initializing Texture Streaming Subsystem", 5);
    ProjectUtils_->ModelLoader_->AssetStreamingManager_->SetupTextureStreamer(Window_, EGLOffscreenDisplay_, EGLOffscreenConfig_, EGLOffscreenContext_, EGLOffscreenSurface_);
    SystemUtils_->Logger_->Log("Finished Initializing Texture Streaming Subsystem", 4);

#else

    SystemUtils_->Logger_->Log("Headless Offscreen Mode (Display-Free EGL Rendering) Is Only Supported On POSIX Platforms With EGL Support, Aborting ERS Startup", 10);
    std::exit(1);

#endif

}

void RendererManager::UpdateLoop(float DeltaTime) { 
    ERS_PROFILE_NAMED_SCOPE("RendererManager::UpdateLoop");

    // Log Any Issues
    ReportOpenGLErrors();



    ERS_STRUCT_Scene* TargetScene = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get();
    ProjectUtils_->ModelLoader_->AssetStreamingManager_->AsyncTextureUpdater_->SortModels(TargetScene);

    std::vector<ERS_STRUCT_Camera*> Cameras;
    for (unsigned int i = 0; i < VisualRenderer_->Viewports_.size(); i++) {
        Cameras.push_back(VisualRenderer_->Viewports_[i]->Camera.get());
    }
    ProjectUtils_->ModelLoader_->AssetStreamingManager_->UpdateSceneStreamingQueue(ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get(), Cameras);
    



    // Update Window Title
    if (Window_ != nullptr) {
        std::string SceneTitle = ProjectUtils_->ProjectManager_->Project_.ProjectName + std::string(" - BrainGenix-ERS ") + ERS_VERSION;
        glfwSetWindowTitle(Window_, SceneTitle.c_str());
    }

    // Update Scene
    ProjectUtils_->ModelLoader_->ProcessNewModels(ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get());

    // Update IO
    if (Window_ != nullptr) {
        glfwGetWindowSize(Window_, &WindowWidth_, &WindowHeight_);
        glfwPollEvents();

        int Width, Height;
        glfwGetWindowSize(Window_, &Width, &Height);
        SystemUtils_->RenderWidth_ = Width;
        SystemUtils_->RenderHeight_ = Height;
    } else {
        // Display-Free Offscreen Mode: No Window To Query, Use The Configured Dimensions
        SystemUtils_->RenderWidth_ = WindowWidth_;
        SystemUtils_->RenderHeight_ = WindowHeight_;
    }


    ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->IndexSceneObjects();


    // Update GUI
    GuiSystem_->UpdateGUI();

    // Call Updates
    VisualRenderer_->UpdateViewports(DeltaTime, ProjectUtils_->SceneManager_.get());


    // Update GUI Frame
    ImVec4 Color = GuiSystem_->ThemeManager_->ClearColor_;
    glClearColor(Color.x, Color.y, Color.z, Color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    GuiSystem_->UpdateFrame();
    

    // Update Window Stuff
    if (Window_ != nullptr) {
        glfwSwapBuffers(Window_);

        // Check If System Should Shutdown
        if (glfwWindowShouldClose(Window_)) {
            SystemUtils_->Logger_->Log("System Shutdown Invoked By LocalWindow", 2);
            *SystemUtils_->SystemShouldRun_ = false;
        }
    }


}

void RendererManager::ReportOpenGLErrors() {

    // Get Current Errors
    GLint GLErrorStatus = glGetError();

    if (GLErrorStatus != GL_NO_ERROR) {

        std::string ErrorMeaning = "Unknown";
        if (GLErrorStatus == GL_INVALID_ENUM) {
            ErrorMeaning = "GL_INVALID_ENUM";
        } else if (GLErrorStatus == GL_INVALID_VALUE) {
            ErrorMeaning = "GL_INVALID_VALUE";
        } else if (GLErrorStatus == GL_INVALID_OPERATION) {
            ErrorMeaning = "GL_INVALID_OPERATION";
        } else if (GLErrorStatus == GL_STACK_OVERFLOW) {
            ErrorMeaning = "GL_STACK_OVERFLOW";
        } else if (GLErrorStatus == GL_STACK_UNDERFLOW) {
            ErrorMeaning = "GL_STACK_UNDERFLOW";
        } else if (GLErrorStatus == GL_OUT_OF_MEMORY) {
            ErrorMeaning = "GL_OUT_OF_MEMORY";
        } else if (GLErrorStatus == GL_INVALID_FRAMEBUFFER_OPERATION) {
            ErrorMeaning = "GL_INVALID_FRAMEBUFFER_OPERATION";
        }

        std::string ErrorMessage = std::string("OpenGL Context Reporting Error '") + std::to_string(GLErrorStatus) + std::string("' (") + ErrorMeaning + std::string(")");
        SystemUtils_->Logger_->Log(ErrorMessage, 9);

    }

}

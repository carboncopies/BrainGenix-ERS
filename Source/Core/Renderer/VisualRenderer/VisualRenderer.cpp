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
VisualRenderer::VisualRenderer(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, GLFWwindow* Window, std::shared_ptr<Cursors3D> Cursors3D) {

    // Create Pointers
    SystemUtils->Logger_->Log("Populating Renderer Member Pointers", 5);
    SystemUtils_ = SystemUtils;
    Window_ = Window;
    Cursors3D_ = Cursors3D;

    // Initialize OpenGL
    SystemUtils_->Logger_->Log("Initializing OpenGL", 5);
    InitializeOpenGL();



}

VisualRenderer::~VisualRenderer() {

    // Destroy Framebuffers
    for (int i = 0; i < FramebufferObjects_.size(); i++) {

        glDeleteFramebuffers(1, &FramebufferObjects_[i]);
        glDeleteTextures(1, &FramebufferColorObjects_[i]);
        glDeleteRenderbuffers(1, &RenderbufferObjects_[i]);

    }


    // Cleanup
    SystemUtils_->Logger_->Log("Cleaning Up OpenGL/GLFW", 0);
    glfwTerminate();

}

void VisualRenderer::InitializeOpenGL() {

    // Setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SystemUtils_->Logger_->Log("Failed To Initialize GLAD", 10);
    }

}

void VisualRenderer::UpdateViewports(float DeltaTime, std::shared_ptr<SceneManager> SceneManager) {

    // Enable Depth Test
    glEnable(GL_DEPTH_TEST);

    // Iterate Through Viewports
    for (int i = 0; i<Shaders_.size(); i++) {

        UpdateViewport(i, SceneManager, DeltaTime);

    }


    // BIND To Default Framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void VisualRenderer::UpdateViewport(int Index, std::shared_ptr<SceneManager>SceneManager, float DeltaTime) {

    // Render To ImGui
    ImGui::Begin(ViewportNames_[Index].c_str());

    // Get Window Input
    int RenderWidth = ImGui::GetWindowSize().x;
    int RenderHeight = ImGui::GetWindowSize().y;


    // Check If Input Enabled
    bool CaptureMouseCursor = false;
    if (!Cursors3D_->DisableCameraMovement() && ImGui::IsWindowFocused() && (glfwGetMouseButton(Window_, 0) == GLFW_PRESS)) {
        CaptureMouseCursor = true;
    } 
        

    // Get Input Processor
    std::shared_ptr<InputProcessor> InputProcessor = InputProcessors_[Index];


    // Update Mouse Capture State
    if (CaptureMouseCursor) {
        glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    // Update Viewport Camera/Position/Etc.
    InputProcessor->ProcessKeyboardInput(SystemUtils_->Logger_, DeltaTime, CaptureMouseCursor);
    InputProcessor->UpdateFramebuffer();
    InputProcessor->UpdateMouse(CaptureMouseCursor);
    InputProcessor->ProcessMouseScroll(CaptureMouseCursor);



    glViewport(0, 0, RenderWidth, RenderHeight);
    glScissor(0, 0, RenderWidth, RenderHeight);


    // Resize Viewport If Needed
    if ((RenderWidth != ViewportWidths_[Index]) || (RenderHeight != ViewportHeights_[Index])) {
        ResizeViewport(Index, RenderWidth, RenderHeight);
    }


    // Bind To Framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferObjects_[Index]);

    // Rendering Commands Here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use Shader
    Shaders_[Index]->MakeActive();


    // Update Camera
    float AspectRatio = (float)RenderWidth / (float)RenderHeight;
    Cameras_[Index]->SetAspectRatio(AspectRatio);
    glm::mat4 projection = Cameras_[Index]->GetProjectionMatrix();
    glm::mat4 view = Cameras_[Index]->GetViewMatrix();
    Shaders_[Index]->SetMat4("projection", projection);
    Shaders_[Index]->SetMat4("view", view);


    // Update Cursor If Selection Changed
    if (SceneManager->Scenes_[SceneManager->ActiveScene_].HasSelectionChanged) {

        // Get Selected Model
        int SelectedModel = SceneManager->Scenes_[SceneManager->ActiveScene_].SelectedModel;

        // Get LocRotScale
        glm::vec3 Position = SceneManager->Scenes_[SceneManager->ActiveScene_].Models[SelectedModel]->ModelPosition;        
        glm::vec3 Rotation = SceneManager->Scenes_[SceneManager->ActiveScene_].Models[SelectedModel]->ModelRotation;        
        glm::vec3 Scale = SceneManager->Scenes_[SceneManager->ActiveScene_].Models[SelectedModel]->ModelScale;

        // Set Cursor Position        
        Cursors3D_->SetLocRotScale(Position, Rotation, Scale);

        // Indicate Selection Hasn't Changed
        SceneManager->Scenes_[SceneManager->ActiveScene_].HasSelectionChanged = false;
    }


    // Start To Draw 3D Cursor
    Cursors3D_->BeginRenderpass(Cameras_[Index], (float*)glm::value_ptr(view), (float*)glm::value_ptr(projection), CaptureMouseCursor);


    // Update Selected Model(s) If Needed
    if (Cursors3D_->HasLocRotScaleChanged()) {
        SceneManager->UpdateLocRotScale(Cursors3D_->GetLocRotScale());
    }

    // Draw Models
    SceneManager->Render(Shaders_[Index]);


    // Render Framebuffer To Window
    ImTextureID Texture = (void*)(intptr_t)FramebufferObjects_[Index];
    ImGui::ImageButton(Texture, ImGui::GetContentRegionAvail(), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f), 0);
    // ImGui::GetWindowDrawList()->AddImage(
    //     (void*)(intptr_t)FramebufferObjects_[Index],
    //     ImVec2(ImGui::GetCursorScreenPos()),
    //     ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowSize().x,
    //         ImGui::GetCursorScreenPos().y + ImGui::GetWindowSize().y),
    //     ImVec2(0, 1),
    //     ImVec2(1, 0)        
    // );






    // Finish 3D Cursor
    Cursors3D_->EndRenderpass();






    ImGui::End();

}

void VisualRenderer::ResizeViewport(int Index, int Width, int Height) {

    // Update Render Color Buffer Size
    glBindTexture(GL_TEXTURE_2D, FramebufferColorObjects_[Index]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    // Update RBO Size
    glBindRenderbuffer(GL_RENDERBUFFER, RenderbufferObjects_[Index]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);

}

// ADD DESTROY VIEWPORT FUNCTION!

void VisualRenderer::CreateViewport(std::shared_ptr<ERS_OBJECT_SHADER> Shader, std::string ViewportName, GLFWwindow* Window, std::shared_ptr<ERS_OBJECT_CAMERA_NOCLIP> Camera) {

    // Append To Vectors
    Shaders_.push_back(Shader);
    Cameras_.push_back(Camera);
    ViewportNames_.push_back(ViewportName);
    ViewportWidths_.push_back(1);
    ViewportHeights_.push_back(1);

    // Create IOManager
    SystemUtils_->Logger_->Log("Creating New Input Processor", 4);
    std::shared_ptr<InputProcessor> InProc = std::make_shared<InputProcessor>(Camera, Window);
    InputProcessors_.push_back(InProc);

    // Create Framebuffer
    unsigned int FramebufferObject;
    SystemUtils_->Logger_->Log("Creating Framebuffer Object", 4);
    glGenFramebuffers(1, &FramebufferObject);

    // Bind To Framebuffer
    SystemUtils_->Logger_->Log("Binding To Framebuffer Object", 4);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferObject);
    FramebufferObjects_.push_back(FramebufferObject);


    // Create RenderTexture
    unsigned int FramebufferColorObject;
    SystemUtils_->Logger_->Log("Creating Render Texture", 4);
    glGenTextures(1, &FramebufferColorObject);
    glBindTexture(GL_TEXTURE_2D, FramebufferColorObject);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 400, 200, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // NOTE: THIS MUST HAPPEN ON RESIZE!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    FramebufferColorObjects_.push_back(FramebufferColorObject);

    // Attach Texture To Framebuffer
    SystemUtils_->Logger_->Log("Attaching Texture To Framebuffer", 4);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FramebufferColorObject, 0);

    // Create Render Buffer
    unsigned int RenderbufferObject;
    SystemUtils_->Logger_->Log("Creating Render Buffer Object", 5);
    glGenRenderbuffers(1, &RenderbufferObject);
    glBindRenderbuffer(GL_RENDERBUFFER, RenderbufferObject);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 400, 200); // RESIZE THIS WITH THE WINDOW!

    // Attach Renderbuffer to Depth And Stencil Attachment
    SystemUtils_->Logger_->Log("Attaching Render Buffer Object To Depth Stencil", 5);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RenderbufferObject);
    RenderbufferObjects_.push_back(RenderbufferObject);

    // Check Framebuffer Status
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {

        // Log Error
        SystemUtils_->Logger_->Log("Failed To Initialize Framebuffer", 9);
    }


}
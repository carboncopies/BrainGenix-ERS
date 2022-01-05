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

void VisualRenderer::SetShader(std::shared_ptr<ERS_OBJECT_SHADER> Shader) {
    Shader_ = Shader;
}

void VisualRenderer::InitializeOpenGL() {

    // Setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SystemUtils_->Logger_->Log("Failed To Initialize GLAD", 10);
    }

}

void VisualRenderer::UpdateViewports(float DeltaTime, std::shared_ptr<ERS_CLASS_SceneManager> SceneManager) {

    // Close Any Viewports Thar Aren't All Open
    int ViewportsToClose = -1;
    for (int i = 0; i < ViewportEnabled_.size(); i++) {
        if (!*ViewportEnabled_[i]) {
            ViewportsToClose = i;
        }
    }
    if (ViewportsToClose != -1) {
        DeleteViewport(ViewportsToClose);
    }


    // Setup Vars
    glEnable(GL_DEPTH_TEST);
    CaptureCursor_ = false;
    CaptureIndex_ = -1;

    // Iterate Through Viewports
    for (int i = 0; i<Shaders_.size(); i++) {
        UpdateViewport(i, SceneManager, DeltaTime);
    }

    // Update Mouse Capture State
    if (CaptureCursor_) {
        glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }


    // Handle Window Input
    for (int i = 0; i < InputProcessors_.size(); i++) {

        // Get Input Processor
        std::shared_ptr<InputProcessor> InputProcessor = InputProcessors_[i];

        bool CaptureEnabled = false;
        if ((CaptureIndex_ == i) && (CaptureCursor_)) {
            CaptureEnabled = true;
        }

        // Update Viewport Camera/Position/Etc.
        InputProcessor->ProcessKeyboardInput(SystemUtils_->Logger_, DeltaTime, CaptureEnabled);
        InputProcessor->UpdateFramebuffer();
        InputProcessor->UpdateMouse(CaptureEnabled);
        InputProcessor->ProcessMouseScroll(CaptureEnabled);

    }

    // BIND To Default Framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void VisualRenderer::UpdateViewport(int Index, std::shared_ptr<ERS_CLASS_SceneManager>SceneManager, float DeltaTime) {

    // Render To ImGui
    ImGui::Begin(ViewportNames_[Index].c_str(), ViewportEnabled_[Index].get());

    // Get Window Input
    int RenderWidth = ImGui::GetWindowSize().x;
    int RenderHeight = ImGui::GetWindowSize().y;


    // Calculate Window Position
    int WindowTopLeftCornerX = ImGui::GetWindowPos().x;
    int WindowTopLeftCornerY = ImGui::GetWindowPos().y;
    int WindowBottomRightCornerX = ImGui::GetWindowSize().x + WindowTopLeftCornerX;
    int WindowBottomRightCornerY = ImGui::GetWindowSize().y + WindowTopLeftCornerY;

    // Get Mouse Pos
    int MousePositionX = ImGui::GetMousePos().x;
    int MousePositionY = ImGui::GetMousePos().y;

    // Check If In Bounding Box
    bool MouseXInRange = (MousePositionX >= WindowTopLeftCornerX) && (MousePositionX < WindowBottomRightCornerX);
    bool MouseYInRange = (MousePositionY >= WindowTopLeftCornerY) && (MousePositionY < WindowBottomRightCornerY);
    bool MouseInRange = MouseXInRange && MouseYInRange;
    

    // Check If Input Enabled
    if (!Cursors3D_->DisableCameraMovement() && ImGui::IsWindowFocused() && (MouseInRange | WasSelected_[Index]) && (glfwGetMouseButton(Window_, 0) == GLFW_PRESS)) {
        CaptureCursor_ = true;
        CaptureIndex_ = Index;
        WasSelected_[Index] = true;
    } else {
        WasSelected_[Index] = false;
    }


    glViewport(0, 0, RenderWidth, RenderHeight);
    glScissor(0, 0, RenderWidth, RenderHeight);


    // Resize Viewport If Needed
    if ((RenderWidth != ViewportWidths_[Index]) || (RenderHeight != ViewportHeights_[Index])) {
        ResizeViewport(Index, RenderWidth, RenderHeight);
    }


    // Bind To Framebuffer
    std::cout<<FramebufferObjects_[Index]<<std::endl;
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
    Cursors3D_->BeginRenderpass(Cameras_[Index], (float*)glm::value_ptr(view), (float*)glm::value_ptr(projection), CaptureCursor_);


    // Update Selected Model(s) If Needed
    if (Cursors3D_->HasLocRotScaleChanged()) {
        SceneManager->UpdateLocRotScale(Cursors3D_->GetLocRotScale());
    }

    // Draw Models
    SceneManager->Render(Shaders_[Index]);


    // Render Framebuffer To Window
    ImGui::GetWindowDrawList()->AddImage(
        (void*)(intptr_t)FramebufferObjects_[Index],
        ImVec2(ImGui::GetCursorScreenPos()),
        ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowSize().x,
            ImGui::GetCursorScreenPos().y + ImGui::GetWindowSize().y),
        ImVec2(0, 1),
        ImVec2(1, 0)        
    );


    // Finish 3D Cursor
    Cursors3D_->EndRenderpass();





    ImGui::End();

}

void VisualRenderer::ResizeViewport(int Index, int Width, int Height) {

    // Update Render Color Buffer Size
    glBindTexture(GL_TEXTURE_2D, FramebufferColorObjects_[Index]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    std::cout<<FramebufferColorObjects_[Index]<<std::endl;

    // Update RBO Size
    glBindRenderbuffer(GL_RENDERBUFFER, RenderbufferObjects_[Index]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);

}

void VisualRenderer::DeleteViewport(int Index) {

    // Log Deletion
    SystemUtils_->Logger_->Log(std::string(std::string("Destroying Viewport '") + ViewportNames_[Index] + std::string("'")).c_str(), 5);

    // Delete From Vectors
    Shaders_.erase(Shaders_.begin() + Index);
    Cameras_.erase(Cameras_.begin() + Index);
    ViewportNames_.erase(ViewportNames_.begin() + Index);
    ViewportWidths_.erase(ViewportWidths_.begin() + Index);
    ViewportHeights_.erase(ViewportHeights_.begin() + Index);
    WasSelected_.erase(WasSelected_.begin() + Index);
    InputProcessors_.erase(InputProcessors_.begin() + Index);
    FramebufferObjects_.erase(FramebufferObjects_.begin() + Index);
    FramebufferColorObjects_.erase(FramebufferColorObjects_.begin() + Index);
    RenderbufferObjects_.erase(RenderbufferObjects_.begin() + Index);
    ViewportEnabled_.erase(ViewportEnabled_.begin() + Index);

}

void VisualRenderer::CreateViewport() {

    // Generate Name
    std::string Name = std::string("Viewport ") + std::to_string(ViewportNames_.size() + 1);

    // Create Viewport
    CreateViewport(Name);

}

void VisualRenderer::CreateViewport(std::string ViewportName) {

    // Log Creation
    SystemUtils_->Logger_->Log(std::string(std::string("Creating New Viewport '") + ViewportName + std::string("'")).c_str(), 5);

    // Reset Shader
    Shader_->MakeActive();
    Shader_->SetInt("texture_diffuse1", 0);


    // Create Camera
    std::shared_ptr<ERS_OBJECT_CAMERA_NOCLIP> Camera = std::make_shared<ERS_OBJECT_CAMERA_NOCLIP>();

    // Append To Vectors
    Shaders_.push_back(Shader_);
    Cameras_.push_back(Camera);
    ViewportNames_.push_back(ViewportName);
    ViewportWidths_.push_back(1);
    ViewportHeights_.push_back(1);
    WasSelected_.push_back(false);
    ViewportEnabled_.push_back(std::make_shared<bool>(true));

    // Create IOManager
    SystemUtils_->Logger_->Log("Creating New Input Processor", 4);
    std::shared_ptr<InputProcessor> InProc = std::make_shared<InputProcessor>(Camera, Window_);
    InputProcessors_.push_back(InProc);

    // Create Framebuffer
    unsigned int FramebufferObject;
    SystemUtils_->Logger_->Log("Creating Framebuffer Object", 4);
    glGenFramebuffers(1, &FramebufferObject);

    std::cout<<FramebufferObject<<std::endl;
    // Bind To Framebuffer
    SystemUtils_->Logger_->Log("Binding To Framebuffer Object", 4);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferObject);
    FramebufferObjects_.push_back(FramebufferObject);


    // Create RenderTexture
    unsigned int FramebufferColorObject;
    SystemUtils_->Logger_->Log("Creating Render Texture", 4);
    glGenTextures(1, &FramebufferColorObject);
    glBindTexture(GL_TEXTURE_2D, FramebufferColorObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 800, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // NOTE: THIS MUST HAPPEN ON RESIZE!
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

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 800); // RESIZE THIS WITH THE WINDOW!

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
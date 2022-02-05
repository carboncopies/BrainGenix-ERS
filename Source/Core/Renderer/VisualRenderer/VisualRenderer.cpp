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
    for (int i = 0; i < Viewports_.size(); i++) {

        glDeleteFramebuffers(1, &Viewports_[i]->FramebufferObject);
        glDeleteTextures(1, &Viewports_[i]->FramebufferColorObject);
        glDeleteRenderbuffers(1, &Viewports_[i]->RenderbufferObject);

    }


    // Cleanup
    SystemUtils_->Logger_->Log("Cleaning Up OpenGL/GLFW", 6);
    glfwTerminate();

}

void VisualRenderer::SetShader(std::shared_ptr<ERS_STRUCT_Shader> Shader, int ID) {

    Shaders_[ID] = Shader;

}

void VisualRenderer::SetDefaultShader(int ShaderID) {
    
    DefaultShader_ = ShaderID;
}

void VisualRenderer::InitializeOpenGL() {

    // Setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SystemUtils_->Logger_->Log("Failed To Initialize GLAD", 10);
    }

}

void VisualRenderer::UpdateViewports(float DeltaTime, std::shared_ptr<ERS_CLASS_SceneManager> SceneManager) {

    // Close Any Viewports That Aren't All Open
    int ViewportsToClose = -1;
    for (int i = 0; i < Viewports_.size(); i++) {
        if (!*Viewports_[i]->Enabled) {
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
    FrameNumber_++;

    // Iterate Through Viewports
    for (int i = 0; i<Viewports_.size(); i++) {
        UpdateViewport(i, SceneManager, DeltaTime);
    }

    // Update Mouse Capture State
    if (CaptureCursor_) {
        glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }



    // Handle Window Input
    for (int i = 0; i < Viewports_.size(); i++) {

        // Get Input Processor
        std::shared_ptr<InputProcessor> InputProcessor = Viewports_[i]->Processor;

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
    ImGuiWindowFlags Flags;
    if (Viewports_[Index]->MenuEnabled) {
        Flags |= ImGuiWindowFlags_MenuBar;
    }
    ImGui::Begin(Viewports_[Index]->Name.c_str(), Viewports_[Index]->Enabled.get(), Flags);

    // Set Default Window Size
    ImGui::SetWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);



    // Handle Viewport Menu
    if (ImGui::IsKeyPressed(GLFW_KEY_GRAVE_ACCENT)) {
        Viewports_[Index]->MenuEnabled = !Viewports_[Index]->MenuEnabled;
    }
    DrawViewportMenu(Index);



    // Calculate Window Position
    ImVec2 vMin = ImGui::GetWindowContentRegionMin();
    ImVec2 vMax = ImGui::GetWindowContentRegionMax();

    vMin.x += ImGui::GetWindowPos().x;
    vMin.y += ImGui::GetWindowPos().y;
    vMax.x += ImGui::GetWindowPos().x;
    vMax.y += ImGui::GetWindowPos().y;

    int WindowTopLeftCornerX = vMin.x;
    int WindowTopLeftCornerY = vMin.y;
    int WindowBottomRightCornerX = vMax.x;
    int WindowBottomRightCornerY = vMax.y;


    // Get Window Input
    int RenderWidth  WindowBottomRightCornerX - WindowTopLeftCornerX;
    int RenderHeight = WindowBottomRightCornerY - WindowTopLeftCornerY;

    std::cout<<RenderWidth<<" "<<RenderWidth<<std::endl;

    // Get Mouse Pos
    int MousePositionX = ImGui::GetMousePos().x;
    int MousePositionY = ImGui::GetMousePos().y;

    // Check If In Bounding Box
    bool MouseXInRange = (MousePositionX >= WindowTopLeftCornerX) && (MousePositionX < WindowBottomRightCornerX);
    bool MouseYInRange = (MousePositionY >= WindowTopLeftCornerY) && (MousePositionY < WindowBottomRightCornerY);
    bool MouseInRange = MouseXInRange && MouseYInRange;
    

    // Check If Input Enabled
    bool EnableCameraMovement = !Cursors3D_->IsUsing();
    if (ImGui::IsKeyDown(341)) { // Bind to left control key
        EnableCameraMovement = true;
    }
    if (EnableCameraMovement && ImGui::IsWindowFocused() && (MouseInRange | Viewports_[Index]->WasSelected) && (glfwGetMouseButton(Window_, 0) == GLFW_PRESS)) {
        CaptureCursor_ = true;
        CaptureIndex_ = Index;
        Viewports_[Index]->WasSelected = true;
    } else {
        CaptureCursor_ = false;
        Viewports_[Index]->WasSelected = false;
    }


    glViewport(0, 0, RenderWidth, RenderHeight);
    glScissor(0, 0, RenderWidth, RenderHeight);


    // Resize Viewport If Needed
    if ((RenderWidth != Viewports_[Index]->Width) || (RenderHeight != Viewports_[Index]->Height)) {
        ResizeViewport(Index, RenderWidth, RenderHeight);
    }


    // Bind To Framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, Viewports_[Index]->FramebufferObject);

    // Rendering Commands Here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use Shader
    int ShaderIndex = Viewports_[Index]->ShaderIndex;
    Shaders_[ShaderIndex]->MakeActive();


    // Update Camera
    float AspectRatio = (float)RenderWidth / (float)RenderHeight;
    Viewports_[Index]->Camera->SetAspectRatio(AspectRatio);
    glm::mat4 projection = Viewports_[Index]->Camera->GetProjectionMatrix();
    glm::mat4 view = Viewports_[Index]->Camera->GetViewMatrix();

    // Update Shaders
    UpdateShader(ShaderIndex, DeltaTime, RenderWidth, RenderHeight);
    Shaders_[ShaderIndex]->SetMat4("projection", projection);
    Shaders_[ShaderIndex]->SetMat4("view", view);


    // Update Cursor If Selection Changed
    if (SceneManager->Scenes_[SceneManager->ActiveScene_]->HasSelectionChanged) {

        // Get Selected Model
        int SelectedModel = SceneManager->Scenes_[SceneManager->ActiveScene_]->SelectedModel;

        // Get LocRotScale
        glm::vec3 Position = SceneManager->Scenes_[SceneManager->ActiveScene_]->Models[SelectedModel]->ModelPosition;        
        glm::vec3 Rotation = SceneManager->Scenes_[SceneManager->ActiveScene_]->Models[SelectedModel]->ModelRotation;        
        glm::vec3 Scale = SceneManager->Scenes_[SceneManager->ActiveScene_]->Models[SelectedModel]->ModelScale;

        // Set Cursor Position        
        Cursors3D_->SetLocRotScale(Position, Rotation, Scale);

        // Indicate Selection Hasn't Changed
        SceneManager->Scenes_[SceneManager->ActiveScene_]->HasSelectionChanged = false;
    }


    // Update Selected Object
    SceneManager->UpdateLocRotScale(Cursors3D_->Pos_, Cursors3D_->Rot_, Cursors3D_->Scale_);
    

    // Draw Models
    SceneManager->Render(Shaders_[ShaderIndex]);


    // Render Framebuffer To Window
    ImGui::GetWindowDrawList()->AddImage(
        (void*)(intptr_t)Viewports_[Index]->FramebufferColorObject,
        ImGui::GetCursorScreenPos(),
        ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowSize().x, ImGui::GetCursorScreenPos().y + ImGui::GetWindowSize().y),
        ImVec2(0, 1),
        ImVec2(1, 0)        
    );


    // Draw 3D Cursor
    Cursors3D_->Draw(Viewports_[Index]->Camera, CaptureCursor_);


    ImGui::End();
}

void VisualRenderer::ResizeViewport(int Index, int Width, int Height) {

    // Update Render Color Buffer Size
    glBindTexture(GL_TEXTURE_2D, Viewports_[Index]->FramebufferColorObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);


    // Update RBO Size
    glBindRenderbuffer(GL_RENDERBUFFER, Viewports_[Index]->RenderbufferObject);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);

}

void VisualRenderer::DeleteViewport(int Index) {

    // Log Deletion
    SystemUtils_->Logger_->Log(std::string(std::string("Destroying Viewport '") + Viewports_[Index]->Name + std::string("'")).c_str(), 5);

    // Cleanup OpenGL Objects
    glDeleteFramebuffers(1, &Viewports_[Index]->FramebufferObject);
    glDeleteTextures(1, &Viewports_[Index]->FramebufferColorObject);
    glDeleteRenderbuffers(1, &Viewports_[Index]->RenderbufferObject);

    // Delete Viewport Struct
    Viewports_.erase(Viewports_.begin() + Index);

}

void VisualRenderer::CreateViewport() {

    // Generate Name
    std::string Name = std::string("Viewport ") + std::to_string(Viewports_.size() + 1);

    // Create Viewport
    CreateViewport(Name);

}

void VisualRenderer::CreateViewport(std::string ViewportName) {


    // Log Creation
    SystemUtils_->Logger_->Log(std::string(std::string("Creating New Viewport '") + ViewportName + std::string("'")).c_str(), 5);


    // Create Viewport Struct
    std::shared_ptr<ERS_STRUCT_Viewport> Viewport = std::make_shared<ERS_STRUCT_Viewport>();


    // Populate Viewport Struct
    Viewport->ShaderIndex = DefaultShader_;
    Viewport->Camera = std::make_shared<ERS_STRUCT_Camera>();
    Viewport->Name = ViewportName;
    
    Viewport->Width = 1;
    Viewport->Height = 1;

    Viewport->WasSelected = false;
    Viewport->Enabled = std::make_shared<bool>(true);


    // Create IOManager
    SystemUtils_->Logger_->Log("Creating New Input Processor", 4);
    Viewport->Processor = std::make_shared<InputProcessor>(Viewport->Camera, Window_);


    // Create Framebuffer
    unsigned int FramebufferObject;
    SystemUtils_->Logger_->Log("Creating Framebuffer Object", 4);
    glGenFramebuffers(1, &FramebufferObject);


    // Bind To Framebuffer
    SystemUtils_->Logger_->Log("Binding To Framebuffer Object", 4);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferObject);
    Viewport->FramebufferObject = FramebufferObject;


    // Create RenderTexture
    unsigned int FramebufferColorObject;
    SystemUtils_->Logger_->Log("Creating Render Texture", 4);
    glGenTextures(1, &FramebufferColorObject);
    glBindTexture(GL_TEXTURE_2D, FramebufferColorObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 800, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // NOTE: THIS MUST HAPPEN ON RESIZE!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Viewport->FramebufferColorObject = FramebufferColorObject;


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
    Viewport->RenderbufferObject = RenderbufferObject;


    // Check Framebuffer Status
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {

        // Log Error
        SystemUtils_->Logger_->Log("Failed To Initialize Framebuffer", 9);
    }


    // Add To Viewports Vector
    Viewports_.push_back(Viewport);

}

void VisualRenderer::UpdateShader(int ShaderIndex, float DeltaTime, int RenderWidth, int RenderHeight) {

    /**

    -- Current list of supported shader params: 

    uniform float Time; // Time since program started in seconds
    uniform float FrameTime; // Render Time Of The Frame
    uniform int FrameNumber; // Number of the frame, counts up from zero
    uniform vec2 ViewportRes; // XY Resolution of the viewport

     */


    // Get Pointer to Shader
    std::shared_ptr<ERS_STRUCT_Shader> ActiveShader = Shaders_[ShaderIndex];

    // Set Current Time
    float Time = glfwGetTime();
    ActiveShader->SetFloat("Time", Time);

    // Set Delta Time
    ActiveShader->SetFloat("FrameTime", DeltaTime);

    // Set Frame Number
    ActiveShader->SetInt("FrameNumber", FrameNumber_);

    // Set Viewport Resolution
    ActiveShader->SetVec2("ViewportRes", RenderWidth, RenderHeight);



}

void VisualRenderer::DrawViewportMenu(int Index) {

    // Menu Bar
    if (ImGui::BeginMenuBar()) {

        // Shader Control Menu
        if(ImGui::BeginMenu("Shader")) {

            // Draw Selectable Menu Showing Active Viewport Shader
            for (int i = 0; i < Shaders_.size(); i++) { 
                if (ImGui::Selectable(Shaders_[i]->DisplayName.c_str(), i == Viewports_[Index]->ShaderIndex)) {
                    Viewports_[Index]->ShaderIndex = i;
                }
            }

        ImGui::EndMenu();
        }


    ImGui::EndMenuBar();
    }

}
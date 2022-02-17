//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_VisualRenderer.h>



ERS_CLASS_VisualRenderer::ERS_CLASS_VisualRenderer(ERS_STRUCT_SystemUtils* SystemUtils, GLFWwindow* Window, std::shared_ptr<Cursors3D> Cursors3D) {

    SystemUtils->Logger_->Log("Populating Renderer Member Pointers", 5);
    SystemUtils_ = SystemUtils;
    Window_ = Window;
    Cursors3D_ = Cursors3D;

    SystemUtils_->Logger_->Log("Initializing OpenGL", 5);
    InitializeOpenGL();

}

ERS_CLASS_VisualRenderer::~ERS_CLASS_VisualRenderer() {

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

void ERS_CLASS_VisualRenderer::SetShader(std::shared_ptr<ERS_STRUCT_Shader> Shader, int ID) {

    Shaders_[ID] = Shader;

}

void ERS_CLASS_VisualRenderer::SetDefaultShader(int ShaderID) {
    
    DefaultShader_ = ShaderID;
}

void ERS_CLASS_VisualRenderer::InitializeOpenGL() {

    // Setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SystemUtils_->Logger_->Log("Failed To Initialize GLAD", 10);
    }

}

void ERS_CLASS_VisualRenderer::UpdateViewports(float DeltaTime, std::shared_ptr<ERS_CLASS_SceneManager> SceneManager) {

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
        std::shared_ptr<ERS_CLASS_InputProcessor> InputProcessorInstance = Viewports_[i]->Processor;

        bool CaptureEnabled = false;
        if ((CaptureIndex_ == i) && (CaptureCursor_)) {
            CaptureEnabled = true;
        }

        // Update Viewport Camera/Position/Etc.
        InputProcessorInstance->ProcessKeyboardInput(SystemUtils_->Logger_, DeltaTime, CaptureEnabled);
        InputProcessorInstance->UpdateFramebuffer();
        InputProcessorInstance->UpdateMouse(CaptureEnabled);
        InputProcessorInstance->ProcessMouseScroll(CaptureEnabled);

    }

    // BIND To Default Framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void ERS_CLASS_VisualRenderer::UpdateViewport(int Index, std::shared_ptr<ERS_CLASS_SceneManager>SceneManager, float DeltaTime) {


    // Render To ImGui
    ImGuiWindowFlags Flags;
    if (Viewports_[Index]->MenuEnabled) {
        Flags |= ImGuiWindowFlags_MenuBar;
    }
    bool Visible = ImGui::Begin(Viewports_[Index]->Name.c_str(), Viewports_[Index]->Enabled.get(), Flags);
    

    // Set Default Window Size
    ImGui::SetWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);


    // Check If Window Visible
    if (Visible) {

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
        int RenderWidth = WindowBottomRightCornerX - WindowTopLeftCornerX;
        int RenderHeight = WindowBottomRightCornerY - WindowTopLeftCornerY;


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

        // Update Camera
        float AspectRatio = (float)RenderWidth / (float)RenderHeight;
        Viewports_[Index]->Camera->SetAspectRatio(AspectRatio);
        glm::mat4 projection = Viewports_[Index]->Camera->GetProjectionMatrix();
        glm::mat4 view = Viewports_[Index]->Camera->GetViewMatrix();
        



        // Use Shader
        int ShaderIndex = Viewports_[Index]->ShaderIndex;
        Shaders_[ShaderIndex]->MakeActive();

        // Update Shaders
        UpdateShader(ShaderIndex, DeltaTime, RenderWidth, RenderHeight, SceneManager, Viewports_[Index]->Camera->Position);
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

        // Check If Grid Enabled
        if (Viewports_[Index]->GridEnabled) {
            Viewports_[Index]->Grid->DrawGrid(view, projection, Viewports_[Index]->Camera->Position);
        }

        //*******************************************************************************
        // Something here to render the foreground ui elements (such as the light icons)
        //*******************************************************************************



        // Render Framebuffer To Window
        ImGui::GetWindowDrawList()->AddImage(
            (void*)(intptr_t)Viewports_[Index]->FramebufferColorObject,
            ImGui::GetCursorScreenPos(),
            ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowSize().x, ImGui::GetCursorScreenPos().y + ImGui::GetWindowSize().y),
            ImVec2(0, 1),
            ImVec2(1, 0)        
        );


        // Draw 3D Cursor
        Cursors3D_->Draw(Viewports_[Index]->Camera, CaptureCursor_, Viewports_[Index]->ShowCube, Viewports_[Index]->GizmoEnabled);

    }


    ImGui::End();
}

void ERS_CLASS_VisualRenderer::ResizeViewport(int Index, int Width, int Height) {

    // Update Render Color Buffer Size
    glBindTexture(GL_TEXTURE_2D, Viewports_[Index]->FramebufferColorObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);


    // Update RBO Size
    glBindRenderbuffer(GL_RENDERBUFFER, Viewports_[Index]->RenderbufferObject);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);

}

void ERS_CLASS_VisualRenderer::DeleteViewport(int Index) {

    // Log Deletion
    SystemUtils_->Logger_->Log(std::string(std::string("Destroying Viewport '") + Viewports_[Index]->Name + std::string("'")).c_str(), 5);

    // Cleanup OpenGL Objects
    glDeleteFramebuffers(1, &Viewports_[Index]->FramebufferObject);
    glDeleteTextures(1, &Viewports_[Index]->FramebufferColorObject);
    glDeleteRenderbuffers(1, &Viewports_[Index]->RenderbufferObject);

    // Delete Viewport Struct
    Viewports_.erase(Viewports_.begin() + Index);

}

void ERS_CLASS_VisualRenderer::CreateViewport() {

    // Generate Name
    std::string Name = std::string("Viewport ") + std::to_string(Viewports_.size() + 1);

    // Create Viewport
    CreateViewport(Name);

}

void ERS_CLASS_VisualRenderer::CreateViewport(std::string ViewportName) {


    // Log Creation
    SystemUtils_->Logger_->Log(std::string(std::string("Creating New Viewport '") + ViewportName + std::string("'")).c_str(), 5);


    // Create Viewport Struct
    std::shared_ptr<ERS_STRUCT_Viewport> Viewport = std::make_shared<ERS_STRUCT_Viewport>();


    // Populate Viewport Struct
    Viewport->ShaderIndex = DefaultShader_;
    Viewport->Camera = std::make_shared<ERS_STRUCT_Camera>();
    Viewport->Grid = std::make_shared<ERS_CLASS_Grid>(SystemUtils_, Shaders_[0]);
    Viewport->Name = ViewportName;
    
    Viewport->Width = 1;
    Viewport->Height = 1;

    Viewport->WasSelected = false;
    Viewport->Enabled = std::make_shared<bool>(true);


    // Create IOManager
    SystemUtils_->Logger_->Log("Creating New Input Processor", 4);
    Viewport->Processor = std::make_shared<ERS_CLASS_InputProcessor>(Viewport->Camera, Window_);


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

void ERS_CLASS_VisualRenderer::UpdateShader(int ShaderIndex, float DeltaTime, int RenderWidth, int RenderHeight, std::shared_ptr<ERS_CLASS_SceneManager>SceneManager, glm::vec3 CameraPosition) {

    /**

    -- Current list of supported shader params: 

    uniform float Time; // Time since program started in seconds
    uniform float FrameTime; // Render Time Of The Frame
    uniform int FrameNumber; // Number of the frame, counts up from zero
    uniform vec2 ViewportRes; // XY Resolution of the viewport

     */


    // Get Pointer to Shader
    std::shared_ptr<ERS_STRUCT_Shader> ActiveShader = Shaders_[ShaderIndex];

    // Set Metadata Params
    float Time = glfwGetTime();
    ActiveShader->SetFloat("Time", Time);

    ActiveShader->SetFloat("FrameTime", DeltaTime);
    ActiveShader->SetInt("FrameNumber", FrameNumber_);
    ActiveShader->SetVec2("ViewportRes", RenderWidth, RenderHeight);
    ActiveShader->SetVec3("CameraPosition", CameraPosition);



    std::shared_ptr<ERS_STRUCT_Scene> ActiveScene = SceneManager->Scenes_[SceneManager->ActiveScene_];

    // // Preprocess Lighting Info
    // glm::vec3 AmbientColor = glm::vec3(0.0f);
    // for (int i = 0; i < ActiveScene->Lights.size(); i++) {

    //     // If Ambient Light, Add Contribution
    //     if (ActiveScene->Lights[i]->LightType == "Ambient") {
    //         float R, G, B;
    //         R = ActiveScene->Lights[i]->ColorRed;
    //         G = ActiveScene->Lights[i]->ColorGreen;
    //         B = ActiveScene->Lights[i]->ColorBlue;
    //         glm::vec3 LightColor = glm::vec3(R,G,B);
    //         AmbientColor += LightColor * ActiveScene->Lights[i]->Intensity;
    //     }

    // }

    // // Set Lighting Params
    // ActiveShader->SetVec3("Light_Ambient_Color", AmbientColor);
    // ActiveShader->SetVec3("Light_Position", glm::vec3(3.0f));
    // ActiveShader->SetVec3("Light_Diffuse_Color", glm::vec3(1.0f));
    // ActiveShader->SetVec3("Light_Specular_Color", glm::vec3(1.0f));

    // Cheaty Lighting Setup

    // Diffuse Lamp
    ActiveShader->SetInt("NumberDirectionalLights", 0);
    ActiveShader->SetInt("NumberPointLights", 1);
    ActiveShader->SetInt("NumberSpotLights", 0);
    

    ActiveShader->SetVec3("DirectionalLights[0].Direction", glm::vec3(0.0f));
    ActiveShader->SetVec3("DirectionalLights[0].Ambient", glm::vec3(1.0f));
    ActiveShader->SetVec3("DirectionalLights[0].Diffuse", glm::vec3(1.0f));
    ActiveShader->SetVec3("DirectionalLights[0].Specular", glm::vec3(1.0f));


    ActiveShader->SetVec3("PointLights[0].Position", glm::vec3(0.0f));
    ActiveShader->SetFloat("PointLights[0].ConstantRolloff", 1.0f);
    ActiveShader->SetFloat("PointLights[0].LinearRolloff", 0.09f);
    ActiveShader->SetFloat("PointLights[0].QuadraticRolloff", 0.032f);
    
    ActiveShader->SetVec3("PointLights[0].Ambient", glm::vec3(1.0f));
    ActiveShader->SetVec3("PointLights[0].Diffuse", glm::vec3(1.0f));
    ActiveShader->SetVec3("PointLights[0].Specular", glm::vec3(1.0f));

    ActiveShader->SetFloat("Shinyness", 32.0f);
    
    


}

void ERS_CLASS_VisualRenderer::DrawViewportMenu(int Index) {

    // Menu Bar
    if (ImGui::BeginMenuBar()) {


        // Viewport Cube Controls
        if (ImGui::BeginMenu("Controls")) {

            // Draw Controls
            ImGui::MenuItem("Rotation Indicator", nullptr, &Viewports_[Index]->ShowCube);
            ImGui::MenuItem("Gizmo", nullptr, &Viewports_[Index]->GizmoEnabled);
            ImGui::MenuItem("Grid", nullptr, &Viewports_[Index]->GridEnabled);


        ImGui::EndMenu();
        }


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

        // Grid Control Menu
        if (ImGui::BeginMenu("Grid")) {

            // Grid Scale Submenu
            if (ImGui::BeginMenu("Scale")) {

                if (ImGui::MenuItem("0.0625 Units", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.00125f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.00125f;
                }

                if (ImGui::MenuItem("0.125 Units", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.0025f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.0025f;
                }

                if (ImGui::MenuItem("0.25 Units", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.005f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.005f;
                }

                if (ImGui::MenuItem("0.5 Units", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.01f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.01f;
                }

                if (ImGui::MenuItem("1 Unit", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.02f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.02f;
                }

                if (ImGui::MenuItem("2.5 Units", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.05f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.05f;
                }

                if (ImGui::MenuItem("5 Units", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.1f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.1f;
                }
                
            ImGui::EndMenu();
            }

            // Line Thickness Submenu
            if (ImGui::BeginMenu("Line Thickness")) {

                if (ImGui::MenuItem("0.5%", nullptr, (Viewports_[Index]->Grid->GridLineThickness_ == 0.005f))) {
                    Viewports_[Index]->Grid->GridLineThickness_ = 0.005f;
                }

                if (ImGui::MenuItem("1%", nullptr, (Viewports_[Index]->Grid->GridLineThickness_ == 0.01f))) {
                    Viewports_[Index]->Grid->GridLineThickness_ = 0.01f;
                }

                if (ImGui::MenuItem("2%", nullptr, (Viewports_[Index]->Grid->GridLineThickness_ == 0.02f))) {
                    Viewports_[Index]->Grid->GridLineThickness_ = 0.02f;
                }

                if (ImGui::MenuItem("3%", nullptr, (Viewports_[Index]->Grid->GridLineThickness_ == 0.03f))) {
                    Viewports_[Index]->Grid->GridLineThickness_ = 0.03f;
                }

                if (ImGui::MenuItem("4%", nullptr, (Viewports_[Index]->Grid->GridLineThickness_ == 0.04f))) {
                    Viewports_[Index]->Grid->GridLineThickness_ = 0.04f;
                }
                
            ImGui::EndMenu();
            }

            // Color Scheme
            if (ImGui::BeginMenu("Colors")) {

                // Base Color
                if (ImGui::BeginMenu("Base")) {


                    if (ImGui::MenuItem("White")) {
                        Viewports_[Index]->Grid->GridColor_ = glm::vec3(1.0f);
                    }

                    if (ImGui::MenuItem("Light Grey")) {
                        Viewports_[Index]->Grid->GridColor_ = glm::vec3(0.75f);
                    }

                    if (ImGui::MenuItem("Grey")) {
                        Viewports_[Index]->Grid->GridColor_ = glm::vec3(0.5f);
                    }

                    if (ImGui::MenuItem("Dark Grey")) {
                        Viewports_[Index]->Grid->GridColor_ = glm::vec3(0.25f);
                    }

                    if (ImGui::MenuItem("Very Dark Grey")) {
                        Viewports_[Index]->Grid->GridColor_ = glm::vec3(0.1f);
                    }

                    if (ImGui::MenuItem("Black")) {
                        Viewports_[Index]->Grid->GridColor_ = glm::vec3(0.0f);
                    }

                ImGui::EndMenu();
                }

                // X Axis Color
                if (ImGui::BeginMenu("X Axis")) {


                    if (ImGui::MenuItem("Red")) {
                        Viewports_[Index]->Grid->GridColorX_ = glm::vec3(1.0f, 0.0f, 0.0f);
                    }

                    if (ImGui::MenuItem("Green")) {
                        Viewports_[Index]->Grid->GridColorX_ = glm::vec3(0.0f, 1.0f, 0.0f);
                    }

                    if (ImGui::MenuItem("Blue")) {
                        Viewports_[Index]->Grid->GridColorX_ = glm::vec3(0.0f, 0.0f, 1.0f);
                    }

                    if (ImGui::MenuItem("Dark Grey")) {
                        Viewports_[Index]->Grid->GridColorX_ = glm::vec3(0.25f);
                    }

                    if (ImGui::MenuItem("Very Dark Grey")) {
                        Viewports_[Index]->Grid->GridColorX_ = glm::vec3(0.1f);
                    }

                    if (ImGui::MenuItem("Black")) {
                        Viewports_[Index]->Grid->GridColorX_ = glm::vec3(0.0f);
                    }

                ImGui::EndMenu();
                }


                // Z Axis Color
                if (ImGui::BeginMenu("Z Axis")) {


                    if (ImGui::MenuItem("Red")) {
                        Viewports_[Index]->Grid->GridColorZ_ = glm::vec3(1.0f, 0.0f, 0.0f);
                    }

                    if (ImGui::MenuItem("Green")) {
                        Viewports_[Index]->Grid->GridColorZ_ = glm::vec3(0.0f, 1.0f, 0.0f);
                    }

                    if (ImGui::MenuItem("Blue")) {
                        Viewports_[Index]->Grid->GridColorZ_ = glm::vec3(0.0f, 0.0f, 1.0f);
                    }

                    if (ImGui::MenuItem("Dark Grey")) {
                        Viewports_[Index]->Grid->GridColorZ_ = glm::vec3(0.25f);
                    }

                    if (ImGui::MenuItem("Very Dark Grey")) {
                        Viewports_[Index]->Grid->GridColorZ_ = glm::vec3(0.1f);
                    }

                    if (ImGui::MenuItem("Black")) {
                        Viewports_[Index]->Grid->GridColorZ_ = glm::vec3(0.0f);
                    }

                ImGui::EndMenu();
                }


            ImGui::EndMenu();
            }


        ImGui::EndMenu();
        }


    ImGui::EndMenuBar();
    }

}
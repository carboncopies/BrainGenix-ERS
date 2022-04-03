//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_VisualRenderer.h>



ERS_CLASS_VisualRenderer::ERS_CLASS_VisualRenderer(ERS_STRUCT_SystemUtils* SystemUtils, GLFWwindow* Window, Cursors3D* Cursors3D) {

    SystemUtils->Logger_->Log("Populating Renderer Member Pointers", 5);
    SystemUtils_ = SystemUtils;
    Window_ = Window;
    Cursors3D_ = Cursors3D;

    SystemUtils_->Logger_->Log("Initializing OpenGL", 5);
    InitializeOpenGL();

    SystemUtils_->Logger_->Log("Initializing MeshRenderer Class", 5);
    MeshRenderer_ = std::make_unique<ERS_CLASS_MeshRenderer>(SystemUtils_);

}

ERS_CLASS_VisualRenderer::~ERS_CLASS_VisualRenderer() {

    // Destroy Framebuffers
    for (int i = 0; (long)i < (long)Viewports_.size(); i++) {

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

    // Setup OpenGL For Blending (For Transparency Issues)
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

}

void ERS_CLASS_VisualRenderer::SetOpenGLDefaults(ERS_STRUCT_OpenGLDefaults* Defaults) {

    OpenGLDefaults_ = Defaults;

}

void ERS_CLASS_VisualRenderer::UpdateViewports(float DeltaTime, ERS_CLASS_SceneManager* SceneManager) {

    // Close Any Viewports That Aren't All Open
    int ViewportsToClose = -1;
    for (int i = 0; (long)i < (long)Viewports_.size(); i++) {
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
    for (int i = 0; (long)i < (long)Viewports_.size(); i++) {
        UpdateViewport(i, SceneManager, DeltaTime);
    }

    // Update Mouse Capture State
    if (CaptureCursor_) {
        glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }



    // Handle Window Input
    for (int i = 0; (long)i < (long)Viewports_.size(); i++) {

        // Get Input Processor
        ERS_CLASS_InputProcessor* InputProcessorInstance = Viewports_[i]->Processor.get();

        bool CaptureEnabled = false;
        if ((CaptureIndex_ == i) && (!Cursors3D_->IsUsing())) {
            CaptureEnabled = true;
        }

        // Update Viewport Camera/Position/Etc.
        InputProcessorInstance->ProcessKeyboardInput(DeltaTime, CaptureEnabled);
        InputProcessorInstance->UpdateFramebuffer();
        InputProcessorInstance->UpdateMouse(CaptureEnabled);
        InputProcessorInstance->ProcessMouseScroll(CaptureEnabled);

    }
    CaptureCursor_ = false;

    // BIND To Default Framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void ERS_CLASS_VisualRenderer::UpdateViewport(int Index, ERS_CLASS_SceneManager* SceneManager, float DeltaTime, bool DrawCursor) {


    // Render To ImGui
    ImGuiWindowFlags Flags = ImGuiWindowFlags_None;
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

        bool EnableCursorCapture;
        if (EnableCameraMovement && ImGui::IsWindowFocused() && (MouseInRange | Viewports_[Index]->WasSelected) && (glfwGetMouseButton(Window_, 0) == GLFW_PRESS)) {
            CaptureCursor_ = true;
            EnableCursorCapture = true;
            CaptureIndex_ = Index;
            Viewports_[Index]->WasSelected = true;
        } else {
            EnableCursorCapture = false;
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
        UpdateShader(ShaderIndex, DeltaTime, RenderWidth, RenderHeight, SceneManager, Viewports_[Index]->Camera.get());
        Shaders_[ShaderIndex]->SetMat4("projection", projection);
        Shaders_[ShaderIndex]->SetMat4("view", view);


        // Update Cursor If Selection Changed
        if (SceneManager->Scenes_[SceneManager->ActiveScene_]->HasSelectionChanged && DrawCursor) {

            // Get Selected Model
            int SelectedObject = SceneManager->Scenes_[SceneManager->ActiveScene_]->SelectedObject;

            // Get LocRotScale
            glm::vec3 Position;        
            glm::vec3 Rotation;      
            glm::vec3 Scale;
            bool HasRotation = false;
            bool HasScale = false;

            if (SceneManager->Scenes_[SceneManager->ActiveScene_]->SceneObjects_[SelectedObject].Type_ == std::string("Model")) {
                unsigned long Index = SceneManager->Scenes_[SceneManager->ActiveScene_]->SceneObjects_[SelectedObject].Index_;
                Position = SceneManager->Scenes_[SceneManager->ActiveScene_]->Models[Index]->ModelPosition;        
                Rotation = SceneManager->Scenes_[SceneManager->ActiveScene_]->Models[Index]->ModelRotation;        
                Scale = SceneManager->Scenes_[SceneManager->ActiveScene_]->Models[Index]->ModelScale;
                HasRotation = true;
                HasScale = true;
            } else if (SceneManager->Scenes_[SceneManager->ActiveScene_]->SceneObjects_[SelectedObject].Type_ == std::string("PointLight")) {
                unsigned long Index = SceneManager->Scenes_[SceneManager->ActiveScene_]->SceneObjects_[SelectedObject].Index_;
                Position = SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights[Index]->Pos;        
            } else if (SceneManager->Scenes_[SceneManager->ActiveScene_]->SceneObjects_[SelectedObject].Type_ == std::string("DirectionalLight")) {
                unsigned long Index = SceneManager->Scenes_[SceneManager->ActiveScene_]->SceneObjects_[SelectedObject].Index_;
                Position = SceneManager->Scenes_[SceneManager->ActiveScene_]->DirectionalLights[Index]->Pos;        
                Rotation = SceneManager->Scenes_[SceneManager->ActiveScene_]->DirectionalLights[Index]->Rot;    
                HasRotation = true;    
            } else if (SceneManager->Scenes_[SceneManager->ActiveScene_]->SceneObjects_[SelectedObject].Type_ == std::string("SpotLight")) {
                unsigned long Index = SceneManager->Scenes_[SceneManager->ActiveScene_]->SceneObjects_[SelectedObject].Index_;
                Position = SceneManager->Scenes_[SceneManager->ActiveScene_]->SpotLights[Index]->Pos;        
                Rotation = SceneManager->Scenes_[SceneManager->ActiveScene_]->SpotLights[Index]->Rot;    
                HasRotation = true;    
            }

            // Set Cursor Position        
            Cursors3D_->SetLocRotScale(Position, Rotation, Scale, HasRotation, HasScale);

            // Indicate Selection Hasn't Changed
            SceneManager->Scenes_[SceneManager->ActiveScene_]->HasSelectionChanged = false;
        }


        // Update Selected Object
        SceneManager->UpdateLocRotScale(Cursors3D_->Pos_, Cursors3D_->Rot_, Cursors3D_->Scale_);

        // Render
        //SceneManager->Render(OpenGLDefaults_, Shaders_[ShaderIndex]);
        MeshRenderer_->RenderScene(SceneManager->Scenes_[SceneManager->ActiveScene_].get(), OpenGLDefaults_, Shaders_[ShaderIndex]);
        if (Viewports_[Index]->GridEnabled) {
            Viewports_[Index]->Grid->DrawGrid(view, projection, Viewports_[Index]->Camera->Position_);
        }
        if (true) {
            Viewports_[Index]->LightIconRenderer->Draw(Viewports_[Index]->Camera.get(), SceneManager);
        }




        // Render Framebuffer To Window
        ImGui::GetWindowDrawList()->AddImage(
            (void*)(intptr_t)Viewports_[Index]->FramebufferColorObject,
            ImGui::GetCursorScreenPos(),
            ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowSize().x, ImGui::GetCursorScreenPos().y + ImGui::GetWindowSize().y),
            ImVec2(0, 1),
            ImVec2(1, 0)        
        );


        // Draw 3D Cursor
        if (Cursors3D_->HasStateChanged()) {
            if (ImGui::IsWindowHovered()) {
                ActiveViewportCursorIndex_ = Index;
            }
        }

        bool DrawCursor;
        if (Cursors3D_->IsUsing() && (ActiveViewportCursorIndex_ == Index)) {
            DrawCursor = true;
        } else if (!Cursors3D_->IsUsing()) {
            DrawCursor = true;
        } else {
            DrawCursor = false;
        }

        if (DrawCursor) {
            Cursors3D_->Draw(Viewports_[Index]->Camera.get(), EnableCursorCapture, Viewports_[Index]->ShowCube, Viewports_[Index]->GizmoEnabled);
        } else {
            Cursors3D_->Draw(Viewports_[Index]->Camera.get(), false, Viewports_[Index]->ShowCube, false);

        }

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


long ERS_CLASS_VisualRenderer::FindShaderIndex(std::string Name) {

    long Index = 0;
    for (unsigned long i = 0; i < Shaders_.size(); i++) {
        if (Shaders_[i]->InternalName == Name) {
            Index = i;
            break;
        }
    }

    return Index;

}


void ERS_CLASS_VisualRenderer::CreateViewport(std::string ViewportName) {


    // Log Creation
    SystemUtils_->Logger_->Log(std::string(std::string("Creating New Viewport '") + ViewportName + std::string("'")).c_str(), 5);


    // Create Viewport Struct
    std::shared_ptr<ERS_STRUCT_Viewport> Viewport = std::make_shared<ERS_STRUCT_Viewport>();


    // Populate Viewport Struct
    Viewport->ShaderIndex = DefaultShader_;
    Viewport->Camera = std::make_unique<ERS_STRUCT_Camera>();
    Viewport->Grid = std::make_unique<ERS_CLASS_Grid>(SystemUtils_, Shaders_[FindShaderIndex(std::string("_Grid"))]);
    Viewport->LightIconRenderer = std::make_unique<ERS_CLASS_LightIconRenderer>(OpenGLDefaults_, SystemUtils_, Shaders_[FindShaderIndex(std::string("LightIcon"))]); //Set TO Shader 19 For Billboard Shader, Temp. Disabled As It Doesn't Work ATM
    Viewport->Name = ViewportName;
    
    Viewport->Width = 1;
    Viewport->Height = 1;

    Viewport->WasSelected = false;
    Viewport->Enabled = std::make_unique<bool>(true);


    // Create Input Processor
    SystemUtils_->Logger_->Log("Creating New Input Processor", 4);
    Viewport->Processor = std::make_unique<ERS_CLASS_InputProcessor>(Viewport->Camera.get(), Window_);


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

void ERS_CLASS_VisualRenderer::UpdateShader(int ShaderIndex, float DeltaTime, int RenderWidth, int RenderHeight, ERS_CLASS_SceneManager*SceneManager, ERS_STRUCT_Camera* Camera) {

    /**

    -- Current list of supported shader params: 

    uniform float Time; // Time since program started in seconds
    uniform float FrameTime; // Render Time Of The Frame
    uniform int FrameNumber; // Number of the frame, counts up from zero
    uniform vec2 ViewportRes; // XY Resolution of the viewport

    **/


    // Get Pointer to Shader
    std::shared_ptr<ERS_STRUCT_Shader> ActiveShader = Shaders_[ShaderIndex];

    // Set Metadata Params
    float Time = glfwGetTime();
    ActiveShader->SetFloat("Time", Time);

    ActiveShader->SetFloat("FrameTime", DeltaTime);
    ActiveShader->SetInt("FrameNumber", FrameNumber_);
    ActiveShader->SetVec2("ViewportRes", RenderWidth, RenderHeight);
    ActiveShader->SetVec3("CameraPosition", Camera->Position_);



    // ---- SEND LIGHTING INFORMATION TO SHADERS ---- //
    // NOTE: Due to limitations with shaders, the maximum number of lights is as follows (per object) 
    // Directional lights: 4
    // Point Lights: 32
    // Spot Lights: 16
    // TO DO BELOW:
    // When these limitations are reached, ERS will remove the lights that are farthest from the object

    // Prepare To Handle Lights
    //const int DirectionalLightLimit = 4;
    //const int PointLightLimit = 64;
    //const int SpotLightLimit = 32;


    ERS_STRUCT_Scene* ActiveScene = SceneManager->Scenes_[SceneManager->ActiveScene_].get();


    // ~-------------------------------------------------------------------!!!!!!!!!!!!!!!FIXME: IMPLEMENT SYSTEM TO USE THE LIGHTS CLOSEST TO THE OBJECT !!!!!!!!!!!!!!!!!!!!!~----------------------------------- //


    // Directional Lights
    int NumberDirectionalLights = ActiveScene->DirectionalLights.size();
    ActiveShader->SetInt("NumberDirectionalLights", NumberDirectionalLights);
    for (int i = 0; i < NumberDirectionalLights; i++) {
    
        std::string UniformName = std::string("DirectionalLights[") + std::to_string(i) + std::string("]");
        
        ActiveShader->SetVec3((UniformName + std::string(".Direction")).c_str(), ActiveScene->DirectionalLights[i]->Rot);

        ActiveShader->SetVec3((UniformName + std::string(".Ambient")).c_str(), ActiveScene->DirectionalLights[i]->Ambient);
        ActiveShader->SetVec3((UniformName + std::string(".Diffuse")).c_str(), ActiveScene->DirectionalLights[i]->Diffuse);
        ActiveShader->SetVec3((UniformName + std::string(".Specular")).c_str(), ActiveScene->DirectionalLights[i]->Specular);
    
    }

    // Point Lights
    int NumberPointLights = ActiveScene->PointLights.size();
    ActiveShader->SetInt("NumberPointLights", NumberPointLights);
    for (int i = 0; i < NumberPointLights; i++) {
    
        std::string UniformName = std::string("PointLights[") + std::to_string(i) + std::string("]");

        ActiveShader->SetVec3((UniformName + std::string(".Position")).c_str(), ActiveScene->PointLights[i]->Pos);

        ActiveShader->SetFloat((UniformName + std::string(".ConstantRolloff")).c_str(), ActiveScene->PointLights[i]->RolloffConstant);
        ActiveShader->SetFloat((UniformName + std::string(".LinearRolloff")).c_str(), ActiveScene->PointLights[i]->RolloffLinear);
        ActiveShader->SetFloat((UniformName + std::string(".QuadraticRolloff")).c_str(), ActiveScene->PointLights[i]->RolloffQuadratic);

        ActiveShader->SetVec3((UniformName + std::string(".Ambient")).c_str(), ActiveScene->PointLights[i]->Ambient);
        ActiveShader->SetVec3((UniformName + std::string(".Diffuse")).c_str(), ActiveScene->PointLights[i]->Diffuse);
        ActiveShader->SetVec3((UniformName + std::string(".Specular")).c_str(), ActiveScene->PointLights[i]->Specular);
    
    }


    // Spot Lights
    int NumberSpotLights = ActiveScene->SpotLights.size();
    ActiveShader->SetInt("NumberSpotLights", NumberSpotLights);
    for (int i = 0; i < NumberSpotLights; i++) {
    
        std::string UniformName = std::string("SpotLights[") + std::to_string(i) + std::string("]");

        ActiveShader->SetVec3((UniformName + std::string(".Position")).c_str(), ActiveScene->SpotLights[i]->Pos);
        ActiveShader->SetVec3((UniformName + std::string(".Direction")).c_str(), ActiveScene->SpotLights[i]->Rot);

        ActiveShader->SetFloat((UniformName + std::string(".ConstantRolloff")).c_str(), ActiveScene->SpotLights[i]->RolloffConstant);
        ActiveShader->SetFloat((UniformName + std::string(".LinearRolloff")).c_str(), ActiveScene->SpotLights[i]->RolloffLinear);
        ActiveShader->SetFloat((UniformName + std::string(".QuadraticRolloff")).c_str(), ActiveScene->SpotLights[i]->RolloffQuadratic);

        ActiveShader->SetFloat((UniformName + std::string(".CutOff")).c_str(), ActiveScene->SpotLights[i]->CutOff);
        ActiveShader->SetFloat((UniformName + std::string(".OuterCutOff")).c_str(), ActiveScene->SpotLights[i]->OuterCutOff);

        ActiveShader->SetVec3((UniformName + std::string(".Ambient")).c_str(), ActiveScene->SpotLights[i]->Ambient);
        ActiveShader->SetVec3((UniformName + std::string(".Diffuse")).c_str(), ActiveScene->SpotLights[i]->Diffuse);
        ActiveShader->SetVec3((UniformName + std::string(".Specular")).c_str(), ActiveScene->SpotLights[i]->Specular);

    }



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
            for (int i = 0; (long)i < (long)Shaders_.size(); i++) {

                if (strcmp(Shaders_[i]->DisplayName.substr(0, 1).c_str(), "_")) {
                    if (ImGui::Selectable(Shaders_[i]->DisplayName.c_str(), i == Viewports_[Index]->ShaderIndex)) {
                        Viewports_[Index]->ShaderIndex = i;
                    }
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


        // Add Items Menu
        if (ImGui::BeginMenu("Add")) {

            if (ImGui::BeginMenu("Light")) {

                if (ImGui::MenuItem("Point Light")) {

                }

                if (ImGui::MenuItem("Spot Light")) {

                }

                if (ImGui::MenuItem("Directional Light")) {
                    
                }

            ImGui::EndMenu();
            }


        ImGui::EndMenu();
        }


    ImGui::EndMenuBar();
    }

}
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <VisualRenderer.h>

#include <algorithm>
#include <cmath>
#include <limits>

namespace {

constexpr int ERS_RENDERER_MAX_DIRECTIONAL_LIGHTS = 2;
constexpr int ERS_RENDERER_MAX_POINT_LIGHTS = 32;
constexpr int ERS_RENDERER_MAX_SPOT_LIGHTS = 16;

template<class LightVector>
std::vector<unsigned long> ERS_FUNCTION_GetStrongestLightIndexes(const LightVector& Lights, int Limit) {

    std::vector<unsigned long> Indexes;
    if (Limit <= 0) {
        return Indexes;
    }

    for (unsigned long i = 0; i < Lights.size(); i++) {
        Indexes.push_back(i);
    }

    std::stable_sort(Indexes.begin(), Indexes.end(), [&Lights](unsigned long A, unsigned long B) {
        return Lights[A]->Intensity > Lights[B]->Intensity;
    });

    if (Indexes.size() > static_cast<unsigned long>(Limit)) {
        Indexes.resize(static_cast<unsigned long>(Limit));
    }

    return Indexes;

}

template<class LightVector>
std::vector<unsigned long> ERS_FUNCTION_GetNearestLightIndexes(const LightVector& Lights, glm::vec3 ReferencePosition, int Limit) {

    std::vector<unsigned long> Indexes;
    if (Limit <= 0) {
        return Indexes;
    }

    for (unsigned long i = 0; i < Lights.size(); i++) {
        Indexes.push_back(i);
    }

    std::stable_sort(Indexes.begin(), Indexes.end(), [&Lights, ReferencePosition](unsigned long A, unsigned long B) {
        glm::vec3 DistanceA = Lights[A]->Pos - ReferencePosition;
        glm::vec3 DistanceB = Lights[B]->Pos - ReferencePosition;
        return glm::dot(DistanceA, DistanceA) < glm::dot(DistanceB, DistanceB);
    });

    if (Indexes.size() > static_cast<unsigned long>(Limit)) {
        Indexes.resize(static_cast<unsigned long>(Limit));
    }

    return Indexes;

}

glm::mat4 ERS_FUNCTION_GetModelBoundingBoxMatrix(ERS_STRUCT_Model* Model) {

    glm::mat4 ModelMatrix = glm::mat4(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, Model->ModelPosition);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Model->ModelRotation.z), glm::vec3(0, 0, 1));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Model->ModelRotation.y), glm::vec3(0, 1, 0));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Model->ModelRotation.x), glm::vec3(1, 0, 0));
    ModelMatrix = glm::scale(ModelMatrix, Model->TrueModelScale * Model->BoxScale_);

    return ModelMatrix;

}

bool ERS_FUNCTION_RayIntersectsUnitBox(glm::vec3 RayOrigin, glm::vec3 RayDirection, float& HitDistance) {

    const float BoxMin = -0.5f;
    const float BoxMax = 0.5f;
    const float Epsilon = 0.000001f;

    float MinimumDistance = 0.0f;
    float MaximumDistance = std::numeric_limits<float>::max();

    for (int Axis = 0; Axis < 3; Axis++) {
        if (std::abs(RayDirection[Axis]) < Epsilon) {
            if ((RayOrigin[Axis] < BoxMin) || (RayOrigin[Axis] > BoxMax)) {
                return false;
            }
            continue;
        }

        float AxisMinDistance = (BoxMin - RayOrigin[Axis]) / RayDirection[Axis];
        float AxisMaxDistance = (BoxMax - RayOrigin[Axis]) / RayDirection[Axis];

        if (AxisMinDistance > AxisMaxDistance) {
            std::swap(AxisMinDistance, AxisMaxDistance);
        }

        MinimumDistance = std::max(MinimumDistance, AxisMinDistance);
        MaximumDistance = std::min(MaximumDistance, AxisMaxDistance);

        if (MinimumDistance > MaximumDistance) {
            return false;
        }
    }

    HitDistance = MinimumDistance;
    return MaximumDistance >= 0.0f;

}

bool ERS_FUNCTION_RayIntersectsModel(ERS_STRUCT_Model* Model, glm::vec3 RayOrigin, glm::vec3 RayDirection, float& HitDistance) {

    const float Epsilon = 0.000001f;
    glm::vec3 BoundingScale = Model->TrueModelScale * Model->BoxScale_;
    if ((std::abs(BoundingScale.x) < Epsilon) || (std::abs(BoundingScale.y) < Epsilon) || (std::abs(BoundingScale.z) < Epsilon)) {
        return false;
    }

    glm::mat4 ModelMatrix = ERS_FUNCTION_GetModelBoundingBoxMatrix(Model);
    glm::mat4 InverseModelMatrix = glm::inverse(ModelMatrix);

    glm::vec3 LocalOrigin = glm::vec3(InverseModelMatrix * glm::vec4(RayOrigin, 1.0f));
    glm::vec3 LocalDirection = glm::normalize(glm::vec3(InverseModelMatrix * glm::vec4(RayDirection, 0.0f)));

    float LocalHitDistance = 0.0f;
    if (!ERS_FUNCTION_RayIntersectsUnitBox(LocalOrigin, LocalDirection, LocalHitDistance)) {
        return false;
    }

    glm::vec3 LocalHitPosition = LocalOrigin + (LocalDirection * LocalHitDistance);
    glm::vec3 WorldHitPosition = glm::vec3(ModelMatrix * glm::vec4(LocalHitPosition, 1.0f));
    HitDistance = glm::length(WorldHitPosition - RayOrigin);

    return true;

}

int ERS_FUNCTION_FindSceneObjectIndexForModel(ERS_STRUCT_Scene* Scene, unsigned long ModelIndex) {

    for (unsigned long i = 0; i < Scene->SceneObjects_.size(); i++) {
        if ((Scene->SceneObjects_[i].Type_ == std::string("Model")) && (Scene->SceneObjects_[i].Index_ == ModelIndex)) {
            return i;
        }
    }

    return -1;

}

void ERS_FUNCTION_SelectModelFromRay(ERS_STRUCT_Scene* Scene, glm::vec3 RayOrigin, glm::vec3 RayDirection) {

    int SelectedSceneObject = -1;
    float ClosestHitDistance = std::numeric_limits<float>::max();

    for (unsigned long i = 0; i < Scene->Models.size(); i++) {
        ERS_STRUCT_Model* Model = Scene->Models[i].get();
        if (!Model->Enabled) {
            continue;
        }

        float HitDistance = 0.0f;
        if (ERS_FUNCTION_RayIntersectsModel(Model, RayOrigin, RayDirection, HitDistance) && (HitDistance < ClosestHitDistance)) {
            int SceneObjectIndex = ERS_FUNCTION_FindSceneObjectIndexForModel(Scene, i);
            if (SceneObjectIndex != -1) {
                SelectedSceneObject = SceneObjectIndex;
                ClosestHitDistance = HitDistance;
            }
        }
    }

    if (SelectedSceneObject != -1) {
        Scene->SelectedObject = SelectedSceneObject;
        Scene->HasSelectionChanged = true;
    }

}

glm::vec3 ERS_FUNCTION_GetViewportRay(
    int MousePositionX,
    int MousePositionY,
    int WindowTopLeftCornerX,
    int WindowTopLeftCornerY,
    int RenderWidth,
    int RenderHeight,
    glm::mat4 Projection,
    glm::mat4 View) {

    float MouseX = (float)(MousePositionX - WindowTopLeftCornerX);
    float MouseY = (float)(MousePositionY - WindowTopLeftCornerY);

    float NormalizedDeviceX = (2.0f * MouseX) / (float)RenderWidth - 1.0f;
    float NormalizedDeviceY = 1.0f - (2.0f * MouseY) / (float)RenderHeight;

    glm::vec4 RayClip = glm::vec4(NormalizedDeviceX, NormalizedDeviceY, -1.0f, 1.0f);
    glm::vec4 RayEye = glm::inverse(Projection) * RayClip;
    RayEye = glm::vec4(RayEye.x, RayEye.y, -1.0f, 0.0f);

    return glm::normalize(glm::vec3(glm::inverse(View) * RayEye));

}

} // namespace


ERS_CLASS_VisualRenderer::ERS_CLASS_VisualRenderer(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, GLFWwindow* Window, Cursors3D* Cursors3D) {

    SystemUtils->Logger_->Log("Populating Renderer Member Pointers", 5);
    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    Window_ = Window;
    Cursors3D_ = Cursors3D;

    SystemUtils_->Logger_->Log("Initializing MeshRenderer Class", 5);
    MeshRenderer_ = std::make_unique<ERS_CLASS_MeshRenderer>(SystemUtils_);

    SystemUtils_->Logger_->Log("Initializing Viewport Overlay Subsystem", 5);
    ViewportOverlay_ = std::make_unique<ERS_CLASS_ViewportOverlay>(SystemUtils_, ProjectUtils_);

    SystemUtils_->Logger_->Log("Initializing Viewport Menu Subsystem", 5);
    ViewportMenu_ = std::make_unique<ERS_CLASS_ViewportMenu>(SystemUtils_, ProjectUtils_, &GameStartTime_, &IsEditorMode_, &Shaders_);

    ShadowMaps_ = std::make_unique<ERS_CLASS_ShadowMaps>(SystemUtils_, ProjectUtils_, MeshRenderer_.get());

    // DEFAULT MODES, CHANGE THIS LATER! --------------------------------
    IsEditorMode_ = true;
    

}

ERS_CLASS_VisualRenderer::~ERS_CLASS_VisualRenderer() {

    // Destroy Framebuffers
    for (int i = 0; (long)i < (long)Viewports_.size(); i++) {

        glDeleteFramebuffers(1, &Viewports_[i]->FramebufferObject);
        glDeleteTextures(1, &Viewports_[i]->FramebufferColorObject);
        glDeleteRenderbuffers(1, &Viewports_[i]->RenderbufferObject);

    }

}


void ERS_CLASS_VisualRenderer::SetDefaultShader(int ShaderID) {
    
    DefaultShader_ = ShaderID;
}

void ERS_CLASS_VisualRenderer::SetOpenGLDefaults(ERS_STRUCT_OpenGLDefaults* Defaults) {

    OpenGLDefaults_ = Defaults;

}

void ERS_CLASS_VisualRenderer::StoreEditorViewportCameraState() {

    if (Viewports_.empty() || (Viewports_[0]->Camera == nullptr)) {
        return;
    }

    ERS_STRUCT_Camera* Camera = Viewports_[0]->Camera.get();
    StoredEditorCameraPosition_ = Camera->GetPosition();
    StoredEditorCameraRotation_ = Camera->GetRotation();
    StoredEditorCameraFOV_ = Camera->GetFOV();
    Camera->GetClipBoundires(StoredEditorCameraNearClip_, StoredEditorCameraFarClip_);
    StoredEditorCameraPriority_ = Camera->GetStreamingPriority();
    HasStoredEditorCameraState_ = true;

}

void ERS_CLASS_VisualRenderer::RestoreEditorViewportCameraState() {

    if (!HasStoredEditorCameraState_ || Viewports_.empty() || (Viewports_[0]->Camera == nullptr)) {
        return;
    }

    ERS_STRUCT_Camera* Camera = Viewports_[0]->Camera.get();
    Camera->SetPosition(StoredEditorCameraPosition_);
    Camera->SetRotation(StoredEditorCameraRotation_);
    Camera->SetFOV(StoredEditorCameraFOV_);
    Camera->SetClipBoundries(StoredEditorCameraNearClip_, StoredEditorCameraFarClip_);
    Camera->SetStreamingPriority(StoredEditorCameraPriority_);
    Camera->Update();

    if (Viewports_[0]->Processor != nullptr) {
        Viewports_[0]->Processor->SetPosition(StoredEditorCameraPosition_);
        Viewports_[0]->Processor->SetRotation(StoredEditorCameraRotation_);
        Viewports_[0]->Processor->SetFOV(StoredEditorCameraFOV_);
        Viewports_[0]->Processor->SetClipBoundries(StoredEditorCameraNearClip_, StoredEditorCameraFarClip_);
        Viewports_[0]->Processor->SetForceUpdate();
    }

}

void ERS_CLASS_VisualRenderer::UpdateViewports(float DeltaTime, ERS_CLASS_SceneManager* SceneManager) {

    

    // Handle editor/play camera transitions before play mode overwrites viewport 0.
    ERS_STRUCT_Scene* Scene = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get();
    if (LastEditorMode_ && !IsEditorMode_) {
        StoreEditorViewportCameraState();
    } else if (!LastEditorMode_ && IsEditorMode_) {
        RestoreEditorViewportCameraState();
    }
    LastEditorMode_ = IsEditorMode_;

    // Apply Scene Camera Transforms
    if (!IsEditorMode_ && Scene->ActiveSceneCameraIndex != -1 && !Viewports_.empty()) {
        ERS_STRUCT_Camera* Camera = Viewports_[0]->Camera.get();
        ERS_STRUCT_SceneCamera* SceneCamera = Scene->SceneCameras[Scene->ActiveSceneCameraIndex].get();
        if (SceneCamera->EnforceAspectRatio_) {
            Camera->SetAspectRatio(SceneCamera->AspectRatio_);
        }
        Camera->SetClipBoundries(SceneCamera->NearClip_, SceneCamera->FarClip_);
        Camera->SetFOV(SceneCamera->FOV_);
        Camera->SetPosition(SceneCamera->Pos_);
        Camera->SetRotation(SceneCamera->Rot_);
        Camera->SetStreamingPriority(SceneCamera->StreamingPriority_);
    }

    // Set Depth Shader For Shadow System
    DepthMapShader_ = Shaders_[ERS_FUNCTION_FindShaderByName(std::string("_DepthMap"), &Shaders_)].get();
    CubemapDepthShader_ = Shaders_[ERS_FUNCTION_FindShaderByName(std::string("_DepthCubeMap"), &Shaders_)].get();

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

    


    // Generate Shadows
    //DepthMapShader_ = Shaders_[ERS_FUNCTION_FindShaderByName(std::string("Preview Shader"), &Shaders_)].get();
    if (Viewports_.size() > 0) {
        ShadowMaps_->UpdateShadowMaps(DepthMapShader_, CubemapDepthShader_, Viewports_[0]->Camera->GetPosition());
    }

    // Setup Vars
    glEnable(GL_DEPTH_TEST);
    CaptureCursor_ = false;
    CaptureIndex_ = -1;
    FrameNumber_++;

    


    RunTime_ = glfwGetTime() - GameStartTime_;
   SystemUtils_->ERS_CLASS_LuaJITInterpreterIntegration_->UpdateSystemInfoData(RunTime_);
   //SystemUtils_->ERS_CLASS_LuaJITInterpreterIntegration_->SetSystemInfoData(lua_State* L);




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
        if (IsEditorMode_ || i != 0) {
            InputProcessorInstance->Process(DeltaTime, CaptureEnabled);
        } else {
            CaptureEnabled = false;
        }


    }
    CaptureCursor_ = false;

    // BIND To Default Framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    


    // RUN SCRIPTS WHEN NOT IN EDITOR MODE
    if (!IsEditorMode_) {

        for (unsigned long i = 0; i < SceneManager->Scenes_[SceneManager->ActiveScene_]->Models.size(); i++) {

            // Get Model
            ERS_STRUCT_Model* Model = SceneManager->Scenes_[SceneManager->ActiveScene_]->Models[i].get();

            // Go Through All Scripts In Model
            for (unsigned long x = 0; x < Model->AttachedScriptIndexes_.size(); x++) {

                long ScriptIndex = Model->AttachedScriptIndexes_[x];
                std::string Code = ProjectUtils_->ProjectManager_->Project_.Scripts[ScriptIndex].Code_;

              bool Status;
                if (x == (unsigned long)SelectedScript_) {
                    Status = SystemUtils_->ERS_CLASS_LuaJITInterpreterIntegration_->ExecuteModelScript(Code, Model, DebugLog_);
                } else {
                    Status = SystemUtils_->ERS_CLASS_LuaJITInterpreterIntegration_->ExecuteModelScript(Code, Model);
                }

                if (!Status) {
                    IsEditorMode_ = true;
                }
            }
        }

        for (unsigned long i = 0; i < SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights.size(); i++) {

            // Get Model
            ERS_STRUCT_PointLight* Target = SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights[i].get();

            // Go Through All Scripts In Model
            for (unsigned long x = 0; x < Target->AttachedScriptIndexes_.size(); x++) {

                long ScriptIndex = Target->AttachedScriptIndexes_[x];
                std::string Code = ProjectUtils_->ProjectManager_->Project_.Scripts[ScriptIndex].Code_;

                bool Status;
                  if (x == (unsigned long)SelectedScript_) {
                    Status = SystemUtils_->ERS_CLASS_LuaJITInterpreterIntegration_->ExecutePointLightScript(Code, Target, DebugLog_);
                } else {
                    Status = SystemUtils_->ERS_CLASS_LuaJITInterpreterIntegration_->ExecutePointLightScript(Code, Target);
                }

                if (!Status) {
                    IsEditorMode_ = true;
                }
            }
        }

        for (unsigned long i = 0; i < SceneManager->Scenes_[SceneManager->ActiveScene_]->DirectionalLights.size(); i++) {

            // Get Model
            ERS_STRUCT_DirectionalLight* Target = SceneManager->Scenes_[SceneManager->ActiveScene_]->DirectionalLights[i].get();

            // Go Through All Scripts In Model
            for (unsigned long x = 0; x < Target->AttachedScriptIndexes_.size(); x++) {

                long ScriptIndex = Target->AttachedScriptIndexes_[x];
                std::string Code = ProjectUtils_->ProjectManager_->Project_.Scripts[ScriptIndex].Code_;

               bool Status;
                if (x == (unsigned long)SelectedScript_) {
                    Status = SystemUtils_->ERS_CLASS_LuaJITInterpreterIntegration_->ExecuteDirectionalLightScript(Code, Target, DebugLog_);
                } else {
                    Status = SystemUtils_->ERS_CLASS_LuaJITInterpreterIntegration_->ExecuteDirectionalLightScript(Code, Target);
                }

                if (!Status) {
                    IsEditorMode_ = true;
                }
            }
        }

        for (unsigned long i = 0; i < SceneManager->Scenes_[SceneManager->ActiveScene_]->SpotLights.size(); i++) {

            // Get Model
            ERS_STRUCT_SpotLight* Target = SceneManager->Scenes_[SceneManager->ActiveScene_]->SpotLights[i].get();

            // Go Through All Scripts In Model
            for (unsigned long x = 0; x < Target->AttachedScriptIndexes_.size(); x++) {

                long ScriptIndex = Target->AttachedScriptIndexes_[x];
                std::string Code = ProjectUtils_->ProjectManager_->Project_.Scripts[ScriptIndex].Code_;

              bool Status;
                if (x == (unsigned long)SelectedScript_) {
                    Status = SystemUtils_->ERS_CLASS_LuaJITInterpreterIntegration_->ExecuteSpotLightScript(Code, Target, DebugLog_);
                } else {
                    Status = SystemUtils_->ERS_CLASS_LuaJITInterpreterIntegration_->ExecuteSpotLightScript(Code, Target);
                }

                if (!Status) {
                    IsEditorMode_ = true;
                }
            }
        }

        for (unsigned long i = 0; i < SceneManager->Scenes_[SceneManager->ActiveScene_]->SceneCameras.size(); i++) {

            // Get Model
            ERS_STRUCT_SceneCamera* Target = SceneManager->Scenes_[SceneManager->ActiveScene_]->SceneCameras[i].get();

            // Go Through All Scripts In Model
            for (unsigned long x = 0; x < Target->AttachedScriptIndexes_.size(); x++) {

                long ScriptIndex = Target->AttachedScriptIndexes_[x];
                std::string Code = ProjectUtils_->ProjectManager_->Project_.Scripts[ScriptIndex].Code_;

                bool Status;
                if (x == (unsigned long)SelectedScript_) {
                    Status = SystemUtils_->ERS_CLASS_LuaJITInterpreterIntegration_->ExecuteSceneCameraScript(Code, Target, DebugLog_);
                } else {
                    Status = SystemUtils_->ERS_CLASS_LuaJITInterpreterIntegration_->ExecuteSceneCameraScript(Code, Target);
                }

                if (!Status) {
                    IsEditorMode_ = true;
                }
            }
        }

    }

    // Reset Selected Script
    SelectedScript_ = -1;


}

void ERS_CLASS_VisualRenderer::SetScriptDebug(int Index, std::vector<std::string>* DebugLog) {

    SelectedScript_ = Index;
    DebugLog_ = DebugLog;

}

void ERS_CLASS_VisualRenderer::UpdateViewport(int Index, ERS_CLASS_SceneManager* SceneManager, float DeltaTime, bool DrawCursor) {

    // Get Vars
    ERS_STRUCT_Viewport* Viewport = Viewports_[Index].get();
    ERS_STRUCT_Scene* Scene = SceneManager->Scenes_[SceneManager->ActiveScene_].get();

    // Render To ImGui
    ImGuiWindowFlags Flags = ImGuiWindowFlags_None;
    if (Viewport->MenuEnabled) {
        Flags |= ImGuiWindowFlags_MenuBar;
    }

    bool Visible = ImGui::Begin(Viewport->Name.c_str(), Viewport->Enabled.get(), Flags);

    // Set Default Window Size
    ImGui::SetWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);






    // Check For Orphaned Scripts
    for (unsigned int i = 0; i < Scene->Models.size(); i++) {
        ERS_STRUCT_Model* Model = Scene->Models[i].get();
        std::vector<long> NewIndexes;

        for (unsigned int x = 0; x < Model->AttachedScriptIndexes_.size(); x++) {
        
            int ScriptIndex = Model->AttachedScriptIndexes_[x];
        
            if (ScriptIndex > -1 && ScriptIndex < (int)ProjectUtils_->ProjectManager_->Project_.Scripts.size()) {
                NewIndexes.push_back(ScriptIndex);
            }

        }

        Model->AttachedScriptIndexes_ = NewIndexes;

    }




    // Check If Window Visible
    if (Visible) {

        // Handle Viewport Menu
        if (ImGui::IsKeyPressed(GLFW_KEY_GRAVE_ACCENT)) {
            Viewport->MenuEnabled = !Viewport->MenuEnabled;
        }
        ViewportMenu_->DrawMenu(Viewport, ShadowMaps_.get());


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
        bool SelectModelWithRay = EnableCameraMovement && ImGui::IsWindowFocused() && MouseInRange && ImGui::IsMouseClicked(0);

        bool EnableCursorCapture;
        if (EnableCameraMovement && ImGui::IsWindowFocused() && (MouseInRange | Viewport->WasSelected) && (glfwGetMouseButton(Window_, 0) == GLFW_PRESS)) {

            if (!IsEditorMode_ && Index == 0) {
                CaptureCursor_ = false;
            } else {
                CaptureCursor_ = true;
            }
            EnableCursorCapture = true;
            CaptureIndex_ = Index;
            Viewport->WasSelected = true;
        } else {
            EnableCursorCapture = false;
            Viewport->WasSelected = false;
        }





        glViewport(0, 0, RenderWidth, RenderHeight);
        glScissor(0, 0, RenderWidth, RenderHeight);


        // Resize Viewport If Needed
        if ((RenderWidth != Viewport->Width) || (RenderHeight != Viewport->Height)) {
            ResizeViewport(Index, RenderWidth, RenderHeight);
        }


        // Bind To Framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, Viewport->FramebufferObject);

        // Rendering Commands Here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update Camera
        float AspectRatio = (float)RenderWidth / (float)RenderHeight;
        Viewport->Camera->Update();
        Viewport->Camera->SetAspectRatio(AspectRatio);
        glm::mat4 Projection;
        glm::mat4 View;
        Viewport->Camera->GetMatrices(Projection, View);

        if (SelectModelWithRay && (RenderWidth > 0) && (RenderHeight > 0)) {
            glm::vec3 RayOrigin = Viewport->Camera->GetPosition();
            glm::vec3 RayDirection = ERS_FUNCTION_GetViewportRay(
                MousePositionX,
                MousePositionY,
                WindowTopLeftCornerX,
                WindowTopLeftCornerY,
                RenderWidth,
                RenderHeight,
                Projection,
                View
                );

            ERS_FUNCTION_SelectModelFromRay(Scene, RayOrigin, RayDirection);
        }



        // Use Shader
        int ShaderIndex = Viewport->ShaderIndex;
        Shaders_[ShaderIndex]->MakeActive();

        // Update Shaders
        UpdateShader(DeltaTime, RenderWidth, RenderHeight, SceneManager, Viewport->Camera.get(), Projection, View, Viewport);

        


        // Update Cursor If Selection Changed
        if (Scene->HasSelectionChanged && DrawCursor && (Scene->SceneObjects_.size() != 0)) {

            // Get Selected Model
            int SelectedObject = Scene->SelectedObject;
            if ((unsigned int)SelectedObject >= Scene->SceneObjects_.size()) {
                SelectedObject = 0;
                Scene->SelectedObject = 0;
            }

            // Get LocRotScale
            glm::vec3 Position;        
            glm::vec3 Rotation;      
            glm::vec3 Scale;
            bool HasRotation = false;
            bool HasScale = false;

            if (Scene->SceneObjects_[SelectedObject].Type_ == std::string("Model")) {
                unsigned long ModelIndex = Scene->SceneObjects_[SelectedObject].Index_;
                Position = Scene->Models[ModelIndex]->ModelPosition;        
                Rotation = Scene->Models[ModelIndex]->ModelRotation;        
                Scale = Scene->Models[ModelIndex]->ModelScale;                
                HasRotation = true;
                HasScale = true;
            } else if (Scene->SceneObjects_[SelectedObject].Type_ == std::string("PointLight")) {
                unsigned long Index = Scene->SceneObjects_[SelectedObject].Index_;
                Position = Scene->PointLights[Index]->Pos;        
            } else if (Scene->SceneObjects_[SelectedObject].Type_ == std::string("DirectionalLight")) {
                unsigned long Index = Scene->SceneObjects_[SelectedObject].Index_;
                Position = Scene->DirectionalLights[Index]->Pos;        
                Rotation = Scene->DirectionalLights[Index]->Rot;    
                HasRotation = true;    
            } else if (Scene->SceneObjects_[SelectedObject].Type_ == std::string("SpotLight")) {
                unsigned long Index = Scene->SceneObjects_[SelectedObject].Index_;
                Position = Scene->SpotLights[Index]->Pos;        
                Rotation = Scene->SpotLights[Index]->Rot;    
                HasRotation = true;    
            } else if (Scene->SceneObjects_[SelectedObject].Type_ == std::string("SceneCamera")) {
                unsigned long Index = Scene->SceneObjects_[SelectedObject].Index_;
                Position = Scene->SceneCameras[Index]->Pos_;        
                Rotation = Scene->SceneCameras[Index]->Rot_;    
                HasRotation = true;    
            }


            // Set Cursor Position        
            Cursors3D_->SetLocRotScale(Position, Rotation, Scale, HasRotation, HasScale);

            // Indicate Selection Hasn't Changed
            Scene->HasSelectionChanged = false;
        }


        // // Update Camera Location If System Running
        // if (!IsEditorMode_ && Index == 0 && Scene->ActiveSceneCameraIndex != -1) {
        //     Viewport->Camera->SetPosition(Scene->SceneCameras[Scene->ActiveSceneCameraIndex]->Pos_);
        //     Viewport->Camera->SetRotation(Scene->SceneCameras[Scene->ActiveSceneCameraIndex]->Rot_);
            
        // }


        // Render
        std::vector<ERS_STRUCT_Shader*> ShaderPointers;
        for (unsigned int i = 0; i < Shaders_.size(); i++) {
            ShaderPointers.push_back(Shaders_[i].get());
        }
        MeshRenderer_->RenderScene(Scene, OpenGLDefaults_, ShaderPointers, ShaderIndex, *ShaderUniformData_);


        if (Viewport->GridEnabled) {
            Viewport->Grid->DrawGrid(View, Projection, Viewport->Camera->GetPosition());
        }
        if (Viewport->LightIcons) {
            Viewport->IconRenderer->Draw(Viewport->Camera.get(), SceneManager);
        }

        Viewport->BoundingBoxRenderer->SetDepthTest(Viewport->DisableBoundingBoxDepthTest_);
        Viewport->BoundingBoxRenderer->SetDrawMode(Viewport->WireframeBoundingBoxes_);
        if (Viewport->ShowBoundingBox_) {
            Viewport->BoundingBoxRenderer->DrawAll(Viewport->Camera.get(), Scene);
        }
        if (Scene->SceneObjects_.size() > 0) {
            if (Viewport->ShowBoxOnSelectedModel_ && Scene->SceneObjects_[Scene->SelectedObject].Type_ == std::string("Model")) {
                unsigned long ModelIndex = Scene->SceneObjects_[Scene->SelectedObject].Index_;
                Viewport->BoundingBoxRenderer->DrawModel(Viewport->Camera.get(), Scene->Models[ModelIndex].get());
            }
        }

        // Render Framebuffer To Window
        ImGui::GetWindowDrawList()->AddImage(
            (void*)(intptr_t)Viewport->FramebufferColorObject,
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
        Cursors3D_->SetGridSnap(Viewport->GridSnapAmountTranslate_, Viewport->GridSnapAmountRotate_, Viewport->GridSnapAmountScale_);
        if (Cursors3D_->IsUsing() && (ActiveViewportCursorIndex_ == Index)) {
            DrawCursor = true;
        } else if (!Cursors3D_->IsUsing()) {
            DrawCursor = true;
        } else {
            DrawCursor = false;
        }

        if (DrawCursor) {
            Cursors3D_->Draw(Viewport->Camera.get(), EnableCursorCapture, Viewport->ShowCube, Viewport->GizmoEnabled);
        } else {
            Cursors3D_->Draw(Viewport->Camera.get(), false, Viewport->ShowCube, false);

        }



        // Update Selected Object
        if (!Cursors3D_->HasObjectChanged_) {
            SceneManager->UpdateLocRotScale(Cursors3D_->Pos_, Cursors3D_->Rot_, Cursors3D_->Scale_);
        } else {
            Cursors3D_->HasObjectChanged_ = false;
            
        }


        ViewportOverlay_->DrawOverlay(Viewport);


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
    
    Viewport->Camera = std::make_unique<ERS_STRUCT_Camera>();
    // Viewport->EditorCamera = std::make_unique<ERS_STRUCT_EditorCamera>();
    // Viewport->EditorCamera->SetupCamera(Viewport->Camera.get());

    Viewport->Grid = std::make_unique<ERS_CLASS_Grid>(SystemUtils_, Shaders_[ERS_FUNCTION_FindShaderByName(std::string("_Grid"), &Shaders_)].get());
    Viewport->IconRenderer = std::make_unique<ERS_CLASS_IconRenderer>(OpenGLDefaults_, SystemUtils_, Shaders_[ERS_FUNCTION_FindShaderByName(std::string("_LightIcon"), &Shaders_)].get()); //Set TO Shader 19 For Billboard Shader, Temp. Disabled As It Doesn't Work ATM
    Viewport->BoundingBoxRenderer = std::make_unique<ERS_CLASS_BoundingBoxRenderer>(SystemUtils_, Shaders_[ERS_FUNCTION_FindShaderByName(std::string("_BoundingBox"), &Shaders_)].get());
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 800, 800, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // NOTE: THIS MUST HAPPEN ON RESIZE!
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

void ERS_CLASS_VisualRenderer::UpdateShader(float DeltaTime, int RenderWidth, int RenderHeight, 
ERS_CLASS_SceneManager*SceneManager, ERS_STRUCT_Camera* Camera, glm::mat4 Projection, glm::mat4 View,
ERS_STRUCT_Viewport* Viewport) {

    // Clear Shader Uniform Data
    ShaderUniformData_ = std::make_unique<ERS_STRUCT_ShaderUniformData>();

    // Set Metadata Params
    float Time = glfwGetTime();
    ShaderUniformData_->Time_ = Time;
    ShaderUniformData_->FrameTime_ = DeltaTime;
    ShaderUniformData_->FrameNumber_ = FrameNumber_;
    ShaderUniformData_->ViewportRes_ = glm::vec2(RenderWidth, RenderHeight);
    ShaderUniformData_->CameraPosition_ = Camera->GetPosition();
    ShaderUniformData_->ShininessOffset_ = 0.5f;


    // Viewport Config
    ShaderUniformData_->Projection_ = Projection;
    ShaderUniformData_->View_ = View;

    // Camera Info
    ShaderUniformData_->GammaCorrectionEnabled_ = Viewport->GammaCorrection;
    ShaderUniformData_->Gamma_ = Viewport->Gamma_;
    ShaderUniformData_->HDREnabled_ = Viewport->HDREnabled_;
    ShaderUniformData_->Exposure_ = Viewport->Exposure_;


    // Set Shadow Filter Info
    int ShadowFilterType = 0;
    ERS::Renderer::ShadowFilteringType ShadowFilterEnum = SystemUtils_->RendererSettings_->ShadowFilteringType_;
    if (ShadowFilterEnum == ERS::Renderer::ERS_SHADOW_FILTERING_DISABLED) {
        ShadowFilterType = 0;
    } else if (ShadowFilterEnum == ERS::Renderer::ERS_SHADOW_FILTERING_PCF) {
        ShadowFilterType = 1;
    } else if (ShadowFilterEnum == ERS::Renderer::ERS_SHADOW_FILTERING_POISSON_SAMPLING) {
        ShadowFilterType = 2;
    } else if (ShadowFilterEnum == ERS::Renderer::ERS_SHADOW_FILTERING_STRATIFIED_POISSON_SAMPLING) {
        ShadowFilterType = 3;
    }
    ShaderUniformData_->ShadowFilterType_ = ShadowFilterType;
    ShaderUniformData_->ShadowFilterKernelSize_ = SystemUtils_->RendererSettings_->ShadowFilterKernelSize_;
    ShaderUniformData_->DepthMapArray_ = ShadowMaps_->ERS_CLASS_DepthMaps_->DepthTextureArrayID_;
    ShaderUniformData_->DepthCubemapArray_ = ShadowMaps_->ERS_CLASS_DepthMaps_->DepthTextureCubemapArrayID_;

    ERS_STRUCT_Scene* ActiveScene = SceneManager->Scenes_[SceneManager->ActiveScene_].get();

    // Clamp viewport-wide light uploads to the fixed-size shader arrays.
    std::vector<unsigned long> DirectionalLightIndexes = ERS_FUNCTION_GetStrongestLightIndexes(
        ActiveScene->DirectionalLights, ERS_RENDERER_MAX_DIRECTIONAL_LIGHTS);
    std::vector<unsigned long> PointLightIndexes = ERS_FUNCTION_GetNearestLightIndexes(
        ActiveScene->PointLights, ShaderUniformData_->CameraPosition_, ERS_RENDERER_MAX_POINT_LIGHTS);
    std::vector<unsigned long> SpotLightIndexes = ERS_FUNCTION_GetNearestLightIndexes(
        ActiveScene->SpotLights, ShaderUniformData_->CameraPosition_, ERS_RENDERER_MAX_SPOT_LIGHTS);

    // Directional Lights
    int NumberDirectionalLights = static_cast<int>(DirectionalLightIndexes.size());
    ShaderUniformData_->NumberDirectionalLights_ = NumberDirectionalLights;
    for (int i = 0; i < NumberDirectionalLights; i++) {
        unsigned long LightIndex = DirectionalLightIndexes[i];
        ShaderUniformData_->DirectionalLights_.push_back(ERS_STRUCT_ShaderUniformDataDirectionalLight());
        ShaderUniformData_->DirectionalLights_[i].Direction_         = ERS_FUNCTION_ConvertRotationToFrontVector(ActiveScene->DirectionalLights[LightIndex]->Rot);
        ShaderUniformData_->DirectionalLights_[i].Color_             = ActiveScene->DirectionalLights[LightIndex]->Color;
        ShaderUniformData_->DirectionalLights_[i].Intensity_         = ActiveScene->DirectionalLights[LightIndex]->Intensity;
        ShaderUniformData_->DirectionalLights_[i].MaxDistance_       = ActiveScene->DirectionalLights[LightIndex]->MaxDistance;
        ShaderUniformData_->DirectionalLights_[i].CastsShadows_      = ActiveScene->DirectionalLights[LightIndex]->CastsShadows_;
        ShaderUniformData_->DirectionalLights_[i].DepthMapIndex_     = ActiveScene->DirectionalLights[LightIndex]->DepthMap.DepthMapTextureIndex;
        ShaderUniformData_->DirectionalLights_[i].LightSpaceMatrix_  = ActiveScene->DirectionalLights[LightIndex]->DepthMap.TransformationMatrix;
    }

    // Point Lights
    int NumberPointLights = static_cast<int>(PointLightIndexes.size());
    ShaderUniformData_->NumberPointLights_ = NumberPointLights;
    for (int i = 0; i < NumberPointLights; i++) {
        unsigned long LightIndex = PointLightIndexes[i];
        ShaderUniformData_->PointLights_.push_back(ERS_STRUCT_ShaderUniformDataPointLight());
        ShaderUniformData_->PointLights_[i].Position_           = ActiveScene->PointLights[LightIndex]->Pos;
        ShaderUniformData_->PointLights_[i].Intensity_          = ActiveScene->PointLights[LightIndex]->Intensity;
        ShaderUniformData_->PointLights_[i].Color_              = ActiveScene->PointLights[LightIndex]->Color;
        ShaderUniformData_->PointLights_[i].MaxDistance_        = ActiveScene->PointLights[LightIndex]->MaxDistance;
        ShaderUniformData_->PointLights_[i].CastsShadows_       = ActiveScene->PointLights[LightIndex]->CastsShadows_;
        ShaderUniformData_->PointLights_[i].DepthCubemapIndex_  = ActiveScene->PointLights[LightIndex]->DepthMap.DepthMapTextureIndex;
    }

    // Spot Lights
    int NumberSpotLights = static_cast<int>(SpotLightIndexes.size());
    ShaderUniformData_->NumberSpotLights_ = NumberSpotLights;
    for (int i = 0; i < NumberSpotLights; i++) {
        unsigned long LightIndex = SpotLightIndexes[i];
        ShaderUniformData_->SpotLights_.push_back(ERS_STRUCT_ShaderUniformDataSpotLight());
        ShaderUniformData_->SpotLights_[i].Position_ = ActiveScene->SpotLights[LightIndex]->Pos;
        ShaderUniformData_->SpotLights_[i].Direction_ = ERS_FUNCTION_ConvertRotationToFrontVector(ActiveScene->SpotLights[LightIndex]->Rot);
        ShaderUniformData_->SpotLights_[i].Intensity_ = ActiveScene->SpotLights[LightIndex]->Intensity;
        ShaderUniformData_->SpotLights_[i].CutOff_ = 1.0f - (ActiveScene->SpotLights[LightIndex]->CutOff * (0.01745329 / 4));
        ShaderUniformData_->SpotLights_[i].RollOff_ = glm::radians(ActiveScene->SpotLights[LightIndex]->Rolloff);
        ShaderUniformData_->SpotLights_[i].Color_ = ActiveScene->SpotLights[LightIndex]->Color;
        ShaderUniformData_->SpotLights_[i].MaxDistance_ = ActiveScene->SpotLights[LightIndex]->MaxDistance;
        ShaderUniformData_->SpotLights_[i].CastsShadows_ = ActiveScene->SpotLights[LightIndex]->CastsShadows_;
        ShaderUniformData_->SpotLights_[i].DepthMapIndex_ = ActiveScene->SpotLights[LightIndex]->DepthMap.DepthMapTextureIndex;
        ShaderUniformData_->SpotLights_[i].LightSpaceMatrix_ = ActiveScene->SpotLights[LightIndex]->DepthMap.TransformationMatrix;
    }
}

//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_ViewportOverlay.h>


ERS_CLASS_ViewportOverlay::ERS_CLASS_ViewportOverlay(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;

    SystemUtils_->Logger_->Log("Initializing Viewport Overlay Subsystem", 5);

}


ERS_CLASS_ViewportOverlay::~ERS_CLASS_ViewportOverlay() {

    SystemUtils_->Logger_->Log("Viewport Overlay Subsystem Destructor Invoked", 6);

}


void ERS_CLASS_ViewportOverlay::DrawOverlay(ERS_STRUCT_Viewport* Viewport) {


    // Draw Scene Info Overlay
    if (Viewport->ShowSceneInfo_) {

        // Generate Info
        unsigned long NumModels = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models.size();
        unsigned long NumVerts = 0;
        unsigned long NumIndices = 0;
        unsigned long NumTextures = 0;
        unsigned long TotalModels = 0;
        unsigned long InstancedModels = 0;

        for (unsigned long i = 0; i < NumModels; i++) {
            if (ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->Enabled) {
                NumVerts += ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->TotalVertices_;
                NumIndices += ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->TotalIndices_;
                NumTextures += ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->OpenGLTextureIDs_.size();
                TotalModels ++;
                if (!ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->IsTemplateModel) {
                    InstancedModels++;
                }
            }
        }

        std::string SceneMessage = std::string("Scene: ") + std::to_string(TotalModels) + std::string(" Models (") + std::to_string(InstancedModels)
        + std::string(" Instanced Models, ") + std::to_string(TotalModels - InstancedModels) + std::string(" Template Models), ") + std::to_string(NumVerts)
        + std::string(" Verts, ") + std::to_string(NumIndices) + std::string(" Indices, ") + std::to_string(NumTextures) + std::string(" Textures");

        ImGui::TextColored(ImVec4(0.25f, 1.0f, 0.25f, 1.0f), "%s", SceneMessage.c_str());


    }


    // Show System Resources Info Overlay
    if (Viewport->ShowResourceInfo_) {

        // Generate Info
        unsigned long NumModels = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models.size();
        unsigned long InMemoryVerts = 0;
        unsigned long InMemoryIndices = 0;

        for (unsigned long i = 0; i < NumModels; i++) {
            if (ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->IsTemplateModel) {
                InMemoryVerts += ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->TotalVertices_;
                InMemoryIndices += ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->TotalIndices_;
            }
        }


        std::string ResourcesMessages = std::to_string(InMemoryVerts) + std::string(" Verts In Memory, ") + std::to_string(InMemoryIndices) + std::string(" Indices In Memory");
        ImGui::TextColored(ImVec4(0.25f, 1.0f, 0.25f, 1.0f), "%s", ResourcesMessages.c_str());

    }

    // Show Loading Time Info Overlay
    if (Viewport->ShowLoadingTimeInfo_) {

        // Generate Info
        unsigned long NumModels = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models.size();
        double LongestLoadingTime = 0;
        double ShortestLoadingTime = 65535;
        double AverageLoadingTime = 0;

        for (unsigned long i = 0; i < NumModels; i++) {
            if (ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->TotalLoadingTime_ > LongestLoadingTime) {
                LongestLoadingTime = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->TotalLoadingTime_;
            }
            if (ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->TotalLoadingTime_ < ShortestLoadingTime && ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->TotalLoadingTime_ != 0.0f) {
                ShortestLoadingTime = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->TotalLoadingTime_;
            }
            AverageLoadingTime += ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_]->Models[i]->TotalLoadingTime_;
        }

        AverageLoadingTime /= NumModels;

        std::string LoadingTimeMessage = std::string("Asset Loading Times | Average: ") + std::to_string(AverageLoadingTime) + std::string(" Seconds, Shortest: ") + std::to_string(ShortestLoadingTime) + std::string(" Seconds, Longest: ") + std::to_string(LongestLoadingTime) + std::string(" Seconds");
        ImGui::TextColored(ImVec4(0.25f, 1.0f, 0.25f, 1.0f), "%s", LoadingTimeMessage.c_str());

    }

    // Show/Hide Light Debug Info Overlay
    if (Viewport->ShowLightInfo_) {


        // Initialize
        ERS_STRUCT_Scene* ActiveScene = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get();

        // Get Lighting Information
        unsigned int NumDirectionalDepthMaps = 0;
        unsigned int NumSpotDepthMaps = 0;
        unsigned int NumPointDepthMaps = 0;
        
        unsigned int NumDirectionalLights = 0;
        unsigned int NumSpotLights = 0;
        unsigned int NumPointLights = 0;

        for (unsigned int i = 0; i < ActiveScene->DirectionalLights.size(); i++) {
            if (ActiveScene->DirectionalLights[i]->DepthMap.Initialized) {
                NumDirectionalDepthMaps++;
            }
            NumDirectionalLights++;
        }

        for (unsigned int i = 0; i < ActiveScene->SpotLights.size(); i++) {
            if (ActiveScene->SpotLights[i]->DepthMap.Initialized) {
                NumSpotDepthMaps++;
            }
            NumSpotLights++;
        }

        for (unsigned int i = 0; i < ActiveScene->PointLights.size(); i++) {
            if (ActiveScene->PointLights[i]->DepthMap.Initialized) {
                NumPointDepthMaps++;
            }
            NumPointLights++;
        }

        std::string LabelText = std::to_string(NumDirectionalLights) + std::string(" Directional Lights (") + std::to_string(NumDirectionalDepthMaps)
         + std::string(" Have Depth Maps) ") + std::to_string(NumSpotLights) + std::string(" Spot Lights (") + std::to_string(NumSpotDepthMaps)
         + std::string(" Have Depth Maps) ") + std::to_string(NumPointLights) + std::string(" Point Lights (") + std::to_string(NumPointDepthMaps)
         + std::string(" Have Depth Maps)");
        ImGui::TextColored(ImVec4(0.25f, 1.0f, 0.25f, 1.0f), "%s", LabelText.c_str());


    }




}
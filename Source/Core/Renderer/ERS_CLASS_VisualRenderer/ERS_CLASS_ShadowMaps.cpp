//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_ShadowMaps.h>


ERS_CLASS_ShadowMaps::ERS_CLASS_ShadowMaps(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_CLASS_MeshRenderer* Renderer) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    Renderer_ = Renderer;

    SystemUtils_->Logger_->Log("Initializing Shadow Map Subsystem", 5);
    ERS_CLASS_DepthMaps_ = std::make_unique<ERS_CLASS_DepthMaps>(SystemUtils_, ProjectUtils_, Renderer_); 

    MersenneTwister_.seed(RandomSeed_);

}

ERS_CLASS_ShadowMaps::~ERS_CLASS_ShadowMaps() {

    SystemUtils_->Logger_->Log("Viewport Overlay Subsystem Destructor Invoked", 6);

}


void ERS_CLASS_ShadowMaps::UpdateShadowMaps(ERS_STRUCT_Shader* DepthMapShader, ERS_STRUCT_Shader* CubemapDepthShader, glm::vec3 CameraPosition) {

    // Get Updated Info From Renderer Settings
    ERS_CLASS_DepthMaps_->CheckSettings();
    ERS::Renderer::ShadowUpdateMode UpdateMode = SystemUtils_->RendererSettings_->ShadowUpdateMode_;
    ERS::Renderer::ShadowFilteringType FilterMode = SystemUtils_->RendererSettings_->ShadowFilteringType_;




    // Create List Of All Depth Maps
    ERS_STRUCT_Scene* ActiveScene = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get();
    std::vector<ERS_STRUCT_DepthMap*> DepthMaps;
    std::vector<glm::vec3> LightPositions;
    for (unsigned int i = 0; i < ActiveScene->PointLights.size(); i++) {
        DepthMaps.push_back(&ActiveScene->PointLights[i]->DepthMap);
        LightPositions.push_back(ActiveScene->PointLights[i]->Pos);
    }
    for (unsigned int i = 0; i < ActiveScene->SpotLights.size(); i++) {
        DepthMaps.push_back(&ActiveScene->SpotLights[i]->DepthMap);
        LightPositions.push_back(ActiveScene->SpotLights[i]->Pos);
    }

    // All Directional Lights Will Be Updated
    for (unsigned int i = 0; i < ActiveScene->DirectionalLights.size(); i++) {
        ActiveScene->DirectionalLights[i]->DepthMap.ToBeUpdated = true;

    }

    

    // Skip Handling An Update If No Lights Are To Be Updated Here
    if (DepthMaps.size() != 0) {

        // Tell The Depth Map Update System Which Depth Maps To Update
        if (UpdateMode == ERS::Renderer::ERS_SHADOW_UPDATE_MODE_DISABLED) {
            // Do Nothing As All Updates Are Disabled
        } else if (UpdateMode == ERS::Renderer::ERS_SHADOW_UPDATE_MODE_ALL) {

            for (unsigned int i = 0; i < DepthMaps.size(); i++) {

                DepthMaps[i]->ToBeUpdated = true;

            }
        } else if (UpdateMode == ERS::Renderer::ERS_SHADOW_UPDATE_MODE_CONSECUTIVE) {
            for (unsigned int i = 0; i < (unsigned int)SystemUtils_->RendererSettings_->MaxShadowUpdatesPerFrame_; i++) {

                // Calculate The Current index, Wrap At End Of List Size
                LastUpdateIndex_++;
                if (LastUpdateIndex_ > DepthMaps.size() - 1) {
                    LastUpdateIndex_ = 0;
                }

                DepthMaps[LastUpdateIndex_]->ToBeUpdated = true;

            }
        } else if (UpdateMode == ERS::Renderer::ERS_SHADOW_UPDATE_MODE_RANDOM) {

            // Randomly Update The Light, Note: Updates Are Guarenteed To Be Less Than Max But Not Equal To That
            for (unsigned int i = 0; i < (unsigned int)SystemUtils_->RendererSettings_->MaxShadowUpdatesPerFrame_; i++) {
                int UpdateIndex = RandomNumberGenerator_(MersenneTwister_) % (DepthMaps.size()-1);
                DepthMaps[UpdateIndex]->ToBeUpdated = true;
            }

        } else if (UpdateMode == ERS::Renderer::ERS_SHADOW_UPDATE_MODE_DISTANCE_PRIORITIZED) {
            
            // Create Map Of Indexes And Distances
            std::map<float, unsigned int> LightDistances;        
            for (unsigned int i = 0; i < DepthMaps.size(); i++) {
                float Distance = glm::distance(CameraPosition, LightPositions[i]);
                LightDistances.insert(std::make_pair(Distance, i));
            }

            std::map<unsigned int, float> SortedLightDistances;
            for (auto const& Entry : LightDistances) {
                std::cout<<Entry.first<<"|"<<Entry.second<<std::endl;
                SortedLightDistances.insert(std::make_pair(Entry.second, Entry.first));
            }


            // for (unsigned int i = 0; i <SortedLightDistances.size();i++) {
            //     std::cout<<i<<" | "<<SortedLightDistances[i]<<std::endl;
            // }

        }

    }
    // Update All Depth Maps
    ERS_CLASS_DepthMaps_->UpdateDepthMaps(DepthMapShader, CubemapDepthShader);

}
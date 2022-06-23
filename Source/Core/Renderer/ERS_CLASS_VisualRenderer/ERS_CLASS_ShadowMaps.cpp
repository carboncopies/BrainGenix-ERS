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
        if (ActiveScene->PointLights[i]->CastsShadows_) {

            // Check If Light Has DepthMap
            if (!ActiveScene->PointLights[i]->DepthMap.Initialized) {
                ActiveScene->PointLights[i]->DepthMap = ERS_CLASS_DepthMaps_->GenerateDepthMap2D();   
            }

            DepthMaps.push_back(&ActiveScene->PointLights[i]->DepthMap);
            LightPositions.push_back(ActiveScene->PointLights[i]->Pos);
        }
    }
    for (unsigned int i = 0; i < ActiveScene->SpotLights.size(); i++) {
        if (ActiveScene->SpotLights[i]->CastsShadows_) {


            // Check If Light Has DepthMap
            if (!ActiveScene->SpotLights[i]->DepthMap.Initialized) {
                ActiveScene->SpotLights[i]->DepthMap.DepthMapTextureIndex = ERS_CLASS_DepthMaps_->AllocateDepthMapIndexCubemap();
                ActiveScene->SpotLights[i]->DepthMap.Initialized = true;
            }

            DepthMaps.push_back(&ActiveScene->SpotLights[i]->DepthMap);
            LightPositions.push_back(ActiveScene->SpotLights[i]->Pos);
        }
    }

    // All Directional Lights Will Be Updated
    for (unsigned int i = 0; i < ActiveScene->DirectionalLights.size(); i++) {
        if (ActiveScene->DirectionalLights[i]->CastsShadows_) {

            // Check If Light Has DepthMap
            if (!ActiveScene->DirectionalLights[i]->DepthMap.Initialized) {
                ActiveScene->DirectionalLights[i]->DepthMap = ERS_CLASS_DepthMaps_->GenerateDepthMap2D();   
            }

            ActiveScene->DirectionalLights[i]->DepthMap.ToBeUpdated = true;
        }

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
            for (int i = 0; i < SystemUtils_->RendererSettings_->MaxShadowUpdatesPerFrame_; i++) {

                // Calculate The Current index, Wrap At End Of List Size
                LastUpdateIndex_++;
                if (LastUpdateIndex_ > DepthMaps.size() - 1) {
                    LastUpdateIndex_ = 0;
                }

                DepthMaps[LastUpdateIndex_]->ToBeUpdated = true;

            }
        } else if (UpdateMode == ERS::Renderer::ERS_SHADOW_UPDATE_MODE_RANDOM) {

            // Randomly Update The Light, Note: Updates Are Guarenteed To Be Less Than Max But Not Equal To That
            for (int i = 0; i < SystemUtils_->RendererSettings_->MaxShadowUpdatesPerFrame_; i++) {
                int UpdateIndex = RandomNumberGenerator_(MersenneTwister_) % (DepthMaps.size()-1);
                DepthMaps[UpdateIndex]->ToBeUpdated = true;
            }

        } else if (UpdateMode == ERS::Renderer::ERS_SHADOW_UPDATE_MODE_DISTANCE_PRIORITIZED) {
            
            // Create Sorted List Of Light Indexes Based On Distance
            std::map<float, unsigned int> LightDistances;        
            for (unsigned int i = 0; i < DepthMaps.size(); i++) {
                float Distance = glm::distance(CameraPosition, LightPositions[i]);
                LightDistances.insert(std::make_pair(Distance, i));
            }

            std::vector<unsigned int> SortedLightDistances;
            for (auto const& Entry : LightDistances) {
                SortedLightDistances.push_back(Entry.second);
            }


            // Mark Lights To Be Updated
            for (int i = 0; i < SystemUtils_->RendererSettings_->MaxShadowUpdatesPerFrame_; i++) {
                unsigned int DepthMapIndex = SortedLightDistances[i];
                if ((signed long)RandomNumberGenerator_(MersenneTwister_) % (signed long)(DepthMaps.size()-1) == (signed long)i) {
                    DepthMapIndex = RandomNumberGenerator_(MersenneTwister_) % (DepthMaps.size()-1);
                }
                DepthMaps[DepthMapIndex]->ToBeUpdated = true;
            }
            

        }

    }
    // Update All Depth Maps
    ERS_CLASS_DepthMaps_->UpdateDepthMaps(DepthMapShader, CubemapDepthShader);

}
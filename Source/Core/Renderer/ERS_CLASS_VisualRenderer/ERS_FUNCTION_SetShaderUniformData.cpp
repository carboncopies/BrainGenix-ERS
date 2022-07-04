//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_SetShaderUniformData.h>


void ERS_FUNCTION_SetShaderUniformData(ERS_STRUCT_Shader* Shader, ERS_STRUCT_ShaderUniformData Data) {



    // Get Pointer to Shader
    ERS_STRUCT_Shader* Shader = Shaders_[ShaderIndex].get();

    // Set Metadata Params
    float Time = glfwGetTime();
    Shader->SetFloat("Time", Time);

    Shader->SetFloat("FrameTime", DeltaTime);
    Shader->SetInt("FrameNumber", FrameNumber_);
    Shader->SetVec2("ViewportRes", RenderWidth, RenderHeight);
    Shader->SetVec3("CameraPosition", Camera->Position_);



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
    Shader->SetInt("NumberDirectionalLights", NumberDirectionalLights);
    for (int i = 0; i < NumberDirectionalLights; i++) {
    
        std::string UniformName = std::string("DirectionalLights[") + std::to_string(i) + std::string("]");
        
        // Re-Do Rotation
        Shader->SetVec3((UniformName + std::string(".Direction")).c_str(), ERS_FUNCTION_ConvertRotationToFrontVector(ActiveScene->DirectionalLights[i]->Rot));
        Shader->SetVec3((UniformName + std::string(".Color")).c_str(), ActiveScene->DirectionalLights[i]->Color);
        Shader->SetFloat((UniformName + std::string(".Intensity")).c_str(), ActiveScene->DirectionalLights[i]->Intensity);

        Shader->SetFloat((UniformName + std::string(".MaxDistance")).c_str(), ActiveScene->DirectionalLights[i]->MaxDistance);

        Shader->SetBool((UniformName + std::string(".CastsShadows")).c_str(), ActiveScene->DirectionalLights[i]->CastsShadows_);

        Shader->SetInt((UniformName + std::string(".DepthMapIndex")).c_str(), ActiveScene->DirectionalLights[i]->DepthMap.DepthMapTextureIndex);
        Shader->SetMat4((UniformName + std::string(".LightSpaceMatrix")).c_str(), ActiveScene->DirectionalLights[i]->DepthMap.TransformationMatrix);
    
    }

    // Point Lights
    int NumberPointLights = ActiveScene->PointLights.size();
    Shader->SetInt("NumberPointLights", NumberPointLights);
    for (int i = 0; i < NumberPointLights; i++) {
    
        std::string UniformName = std::string("PointLights[") + std::to_string(i) + std::string("]");

        Shader->SetVec3((UniformName + std::string(".Position")).c_str(), ActiveScene->PointLights[i]->Pos);
        Shader->SetFloat((UniformName + std::string(".Intensity")).c_str(), ActiveScene->PointLights[i]->Intensity);
        Shader->SetVec3((UniformName + std::string(".Color")).c_str(), ActiveScene->PointLights[i]->Color);
    
        Shader->SetFloat((UniformName + std::string(".MaxDistance")).c_str(), ActiveScene->PointLights[i]->MaxDistance);
        
        Shader->SetBool((UniformName + std::string(".CastsShadows")).c_str(), ActiveScene->PointLights[i]->CastsShadows_);

        Shader->SetInt((UniformName + std::string(".DepthCubemapIndex")).c_str(), ActiveScene->PointLights[i]->DepthMap.DepthMapTextureIndex);

    }


    // Spot Lights
    int NumberSpotLights = ActiveScene->SpotLights.size();
    Shader->SetInt("NumberSpotLights", NumberSpotLights);
    for (int i = 0; i < NumberSpotLights; i++) {
    
        std::string UniformName = std::string("SpotLights[") + std::to_string(i) + std::string("]");

        // Re-Do Rotation
        Shader->SetVec3((UniformName + std::string(".Position")).c_str(), ActiveScene->SpotLights[i]->Pos);
        Shader->SetVec3((UniformName + std::string(".Direction")).c_str(), ERS_FUNCTION_ConvertRotationToFrontVector(ActiveScene->SpotLights[i]->Rot));
        Shader->SetFloat((UniformName + std::string(".Intensity")).c_str(), ActiveScene->SpotLights[i]->Intensity);
        Shader->SetFloat((UniformName + std::string(".CutOff")).c_str(), 1.0f - (ActiveScene->SpotLights[i]->CutOff * (0.01745329 / 4)));
        Shader->SetFloat((UniformName + std::string(".RollOff")).c_str(), glm::radians(ActiveScene->SpotLights[i]->Rolloff));
        Shader->SetVec3((UniformName + std::string(".Color")).c_str(), ActiveScene->SpotLights[i]->Color);

        Shader->SetFloat((UniformName + std::string(".MaxDistance")).c_str(), ActiveScene->SpotLights[i]->MaxDistance);

        Shader->SetBool((UniformName + std::string(".CastsShadows")).c_str(), ActiveScene->SpotLights[i]->CastsShadows_);


        Shader->SetInt((UniformName + std::string(".DepthMapIndex")).c_str(), ActiveScene->SpotLights[i]->DepthMap.DepthMapTextureIndex);
        Shader->SetMat4((UniformName + std::string(".LightSpaceMatrix")).c_str(), ActiveScene->SpotLights[i]->DepthMap.TransformationMatrix);

    }


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
    Shader->SetInt("ShadowFilterType_", ShadowFilterType);
    Shader->SetInt("ShadowFilterKernelSize_", SystemUtils_->RendererSettings_->ShadowFilterKernelSize_);
    


    Shader->SetFloat("Shinyness", 32.0f);

}
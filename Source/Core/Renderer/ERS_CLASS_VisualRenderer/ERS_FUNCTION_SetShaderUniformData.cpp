//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_SetShaderUniformData.h>


void ERS_FUNCTION_SetShaderUniformData(ERS_STRUCT_Shader* Shader, ERS_STRUCT_ShaderUniformData Data) {



    // Get Pointer to Shader
    ERS_STRUCT_Shader* ActiveShader = Shaders_[ShaderIndex].get();

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
        
        // Re-Do Rotation
        ActiveShader->SetVec3((UniformName + std::string(".Direction")).c_str(), ERS_FUNCTION_ConvertRotationToFrontVector(ActiveScene->DirectionalLights[i]->Rot));
        ActiveShader->SetVec3((UniformName + std::string(".Color")).c_str(), ActiveScene->DirectionalLights[i]->Color);
        ActiveShader->SetFloat((UniformName + std::string(".Intensity")).c_str(), ActiveScene->DirectionalLights[i]->Intensity);

        ActiveShader->SetFloat((UniformName + std::string(".MaxDistance")).c_str(), ActiveScene->DirectionalLights[i]->MaxDistance);

        ActiveShader->SetBool((UniformName + std::string(".CastsShadows")).c_str(), ActiveScene->DirectionalLights[i]->CastsShadows_);

        ActiveShader->SetInt((UniformName + std::string(".DepthMapIndex")).c_str(), ActiveScene->DirectionalLights[i]->DepthMap.DepthMapTextureIndex);
        ActiveShader->SetMat4((UniformName + std::string(".LightSpaceMatrix")).c_str(), ActiveScene->DirectionalLights[i]->DepthMap.TransformationMatrix);
    
    }

    // Point Lights
    int NumberPointLights = ActiveScene->PointLights.size();
    ActiveShader->SetInt("NumberPointLights", NumberPointLights);
    for (int i = 0; i < NumberPointLights; i++) {
    
        std::string UniformName = std::string("PointLights[") + std::to_string(i) + std::string("]");

        ActiveShader->SetVec3((UniformName + std::string(".Position")).c_str(), ActiveScene->PointLights[i]->Pos);
        ActiveShader->SetFloat((UniformName + std::string(".Intensity")).c_str(), ActiveScene->PointLights[i]->Intensity);
        ActiveShader->SetVec3((UniformName + std::string(".Color")).c_str(), ActiveScene->PointLights[i]->Color);
    
        ActiveShader->SetFloat((UniformName + std::string(".MaxDistance")).c_str(), ActiveScene->PointLights[i]->MaxDistance);
        
        ActiveShader->SetBool((UniformName + std::string(".CastsShadows")).c_str(), ActiveScene->PointLights[i]->CastsShadows_);

        ActiveShader->SetInt((UniformName + std::string(".DepthCubemapIndex")).c_str(), ActiveScene->PointLights[i]->DepthMap.DepthMapTextureIndex);

    }


    // Spot Lights
    int NumberSpotLights = ActiveScene->SpotLights.size();
    ActiveShader->SetInt("NumberSpotLights", NumberSpotLights);
    for (int i = 0; i < NumberSpotLights; i++) {
    
        std::string UniformName = std::string("SpotLights[") + std::to_string(i) + std::string("]");

        // Re-Do Rotation
        ActiveShader->SetVec3((UniformName + std::string(".Position")).c_str(), ActiveScene->SpotLights[i]->Pos);
        ActiveShader->SetVec3((UniformName + std::string(".Direction")).c_str(), ERS_FUNCTION_ConvertRotationToFrontVector(ActiveScene->SpotLights[i]->Rot));
        ActiveShader->SetFloat((UniformName + std::string(".Intensity")).c_str(), ActiveScene->SpotLights[i]->Intensity);
        ActiveShader->SetFloat((UniformName + std::string(".CutOff")).c_str(), 1.0f - (ActiveScene->SpotLights[i]->CutOff * (0.01745329 / 4)));
        ActiveShader->SetFloat((UniformName + std::string(".RollOff")).c_str(), glm::radians(ActiveScene->SpotLights[i]->Rolloff));
        ActiveShader->SetVec3((UniformName + std::string(".Color")).c_str(), ActiveScene->SpotLights[i]->Color);

        ActiveShader->SetFloat((UniformName + std::string(".MaxDistance")).c_str(), ActiveScene->SpotLights[i]->MaxDistance);

        ActiveShader->SetBool((UniformName + std::string(".CastsShadows")).c_str(), ActiveScene->SpotLights[i]->CastsShadows_);


        ActiveShader->SetInt((UniformName + std::string(".DepthMapIndex")).c_str(), ActiveScene->SpotLights[i]->DepthMap.DepthMapTextureIndex);
        ActiveShader->SetMat4((UniformName + std::string(".LightSpaceMatrix")).c_str(), ActiveScene->SpotLights[i]->DepthMap.TransformationMatrix);

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
    ActiveShader->SetInt("ShadowFilterType_", ShadowFilterType);
    ActiveShader->SetInt("ShadowFilterKernelSize_", SystemUtils_->RendererSettings_->ShadowFilterKernelSize_);
    


    ActiveShader->SetFloat("Shinyness", 32.0f);

}
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_SetShaderUniformData.h>


void ERS_FUNCTION_SetShaderUniformData(ERS_STRUCT_Shader* Shader, ERS_STRUCT_ShaderUniformData Data) {

    // Set Metadata Params
    float Time = glfwGetTime();
    Shader->SetFloat("Time", Data.Time_);

    Shader->SetFloat("FrameTime", Data.FrameTime_);
    Shader->SetInt("FrameNumber", Data.FrameNumber_);
    Shader->SetVec2("ViewportRes", Data.ViewportRes_);
    Shader->SetVec3("CameraPosition", Data.CameraPosition_);
    Shader->SetFloat("ShininessOffset", Data.ShininessOffset_);


    // Set Shadow Filter Info
    Shader->SetInt("ShadowFilterType_", Data.ShadowFilterType_);
    Shader->SetInt("ShadowFilterKernelSize_", Data.ShadowFilterKernelSize_);
    





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



}
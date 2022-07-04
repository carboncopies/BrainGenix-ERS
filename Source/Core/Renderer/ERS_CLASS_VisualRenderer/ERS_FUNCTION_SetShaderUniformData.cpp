//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_SetShaderUniformData.h>


void ERS_FUNCTION_SetShaderUniformData(ERS_STRUCT_Shader* Shader, ERS_STRUCT_ShaderUniformData Data) {

    // Set Metadata Params
    Shader->SetVec3("CameraPosition", Data.CameraPosition_);
    Shader->SetVec2("ViewportRes", Data.ViewportRes_);
    Shader->SetFloat("Time", Data.Time_);
    Shader->SetFloat("FrameTime", Data.FrameTime_);
    Shader->SetFloat("ShininessOffset", Data.ShininessOffset_);
    Shader->SetInt("FrameNumber", Data.FrameNumber_);


    // Set Shadow Filter Info
    Shader->SetInt("ShadowFilterType_", Data.ShadowFilterType_);
    Shader->SetInt("ShadowFilterKernelSize_", Data.ShadowFilterKernelSize_);
    





    // Directional Lights
    Shader->SetInt("NumberDirectionalLights", Data.NumberDirectionalLights_);
    for (int i = 0; i < Data.NumberDirectionalLights_; i++) {
    
        std::string UniformName = std::string("DirectionalLights[") + std::to_string(i) + std::string("]");

        Shader->SetMat4  ((UniformName + std::string(".LightSpaceMatrix")).c_str(),   Data.DirectionalLights_[i].LightSpaceMatrix_);
        Shader->SetVec3  ((UniformName + std::string(".Direction")).c_str(),          Data.DirectionalLights_[i].Direction_);
        Shader->SetVec3  ((UniformName + std::string(".Color")).c_str(),              Data.DirectionalLights_[i].Color_);
        Shader->SetFloat ((UniformName + std::string(".Intensity")).c_str(),          Data.DirectionalLights_[i].Intensity_);
        Shader->SetFloat ((UniformName + std::string(".MaxDistance")).c_str(),        Data.DirectionalLights_[i].MaxDistance_);
        Shader->SetInt   ((UniformName + std::string(".DepthMapIndex")).c_str(),      Data.DirectionalLights_[i].DepthMapIndex_);
        Shader->SetBool  ((UniformName + std::string(".CastsShadows")).c_str(),       Data.DirectionalLights_[i].CastsShadows_);
    
    }

    // Point Lights
    Shader->SetInt("NumberPointLights", Data.NumberPointLights_);
    for (int i = 0; i < Data.NumberPointLights_; i++) {
    
        std::string UniformName = std::string("PointLights[") + std::to_string(i) + std::string("]");

        Shader->SetVec3  ((UniformName + std::string(".Position")).c_str(),           Data.PointLights_[i].Position_);
        Shader->SetVec3  ((UniformName + std::string(".Color")).c_str(),              Data.PointLights_[i].Color_);
        Shader->SetFloat ((UniformName + std::string(".MaxDistance")).c_str(),        Data.PointLights_[i].MaxDistance_);
        Shader->SetFloat ((UniformName + std::string(".Intensity")).c_str(),          Data.PointLights_[i].Intensity_);
        Shader->SetInt   ((UniformName + std::string(".DepthCubemapIndex")).c_str(),  Data.PointLights_[i].DepthCubemapIndex_);
        Shader->SetBool  ((UniformName + std::string(".CastsShadows")).c_str(),       Data.PointLights_[i].CastsShadows_);

    }


    // Spot Lights
    Shader->SetInt("NumberSpotLights", Data.NumberSpotLights_);
    for (int i = 0; i < Data.NumberSpotLights_; i++) {
    
        std::string UniformName = std::string("SpotLights[") + std::to_string(i) + std::string("]");

        Shader->SetMat4  ((UniformName + std::string(".LightSpaceMatrix")).c_str(),   Data.SpotLights_[i].LightSpaceMatrix_);
        Shader->SetVec3  ((UniformName + std::string(".Position")).c_str(),           Data.SpotLights_[i].Position_);
        Shader->SetVec3  ((UniformName + std::string(".Direction")).c_str(),          Data.SpotLights_[i].Direction_);
        Shader->SetVec3  ((UniformName + std::string(".Color")).c_str(),              Data.SpotLights_[i].Color_);
        Shader->SetFloat ((UniformName + std::string(".Intensity")).c_str(),          Data.SpotLights_[i].Intensity_);
        Shader->SetFloat ((UniformName + std::string(".CutOff")).c_str(),             Data.SpotLights_[i].CutOff_);
        Shader->SetFloat ((UniformName + std::string(".RollOff")).c_str(),            Data.SpotLights_[i].RollOff_);
        Shader->SetFloat ((UniformName + std::string(".MaxDistance")).c_str(),        Data.SpotLights_[i].MaxDistance_);
        Shader->SetInt   ((UniformName + std::string(".DepthMapIndex")).c_str(),      Data.SpotLights_[i].DepthMapIndex_);
        Shader->SetBool  ((UniformName + std::string(".CastsShadows")).c_str(),       Data.SpotLights_[i].CastsShadows_);
    }
}
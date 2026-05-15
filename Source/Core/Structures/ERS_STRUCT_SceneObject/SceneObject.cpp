//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <SceneObject.h>


std::string ERS_FUNCTION_GetSceneObjectTypeName(ERS_ENUM_SceneObjectType Type) {

    switch (Type) {
        case ERS_ENUM_SceneObjectType::Model:
            return std::string("Model");

        case ERS_ENUM_SceneObjectType::SpotLight:
            return std::string("SpotLight");

        case ERS_ENUM_SceneObjectType::DirectionalLight:
            return std::string("DirectionalLight");

        case ERS_ENUM_SceneObjectType::PointLight:
            return std::string("PointLight");

        case ERS_ENUM_SceneObjectType::SceneCamera:
            return std::string("SceneCamera");

        case ERS_ENUM_SceneObjectType::Unknown:
        default:
            return std::string("Unknown");
    }
}


ERS_ENUM_SceneObjectType ERS_FUNCTION_GetSceneObjectTypeFromName(const std::string& Type) {

    if (Type == std::string("Model")) {
        return ERS_ENUM_SceneObjectType::Model;
    }

    if (Type == std::string("SpotLight")) {
        return ERS_ENUM_SceneObjectType::SpotLight;
    }

    if (Type == std::string("DirectionalLight")) {
        return ERS_ENUM_SceneObjectType::DirectionalLight;
    }

    if (Type == std::string("PointLight")) {
        return ERS_ENUM_SceneObjectType::PointLight;
    }

    if (Type == std::string("SceneCamera")) {
        return ERS_ENUM_SceneObjectType::SceneCamera;
    }

    return ERS_ENUM_SceneObjectType::Unknown;
}


std::uint64_t ERS_FUNCTION_CreateSceneEntityID(ERS_ENUM_SceneObjectType Type, unsigned long Index) {

    constexpr std::uint64_t TypeBitShift = 32;
    constexpr std::uint64_t IndexMask = 0xFFFFFFFFULL;

    std::uint64_t TypeID = static_cast<std::uint64_t>(Type);
    std::uint64_t ObjectIndex = static_cast<std::uint64_t>(Index);

    return (TypeID << TypeBitShift) | (ObjectIndex & IndexMask);
}

// ToDO: then add to project struct, then update project loader/writer with this info. Then check trello board for other related tasks like live ediitng.


//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <cstdint>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")



/**
 * @brief Runtime object kinds used by scene entities.
 *
 */
enum class ERS_ENUM_SceneObjectType : std::uint8_t {
    Unknown = 0,
    Model,
    SpotLight,
    DirectionalLight,
    PointLight,
    SceneCamera
};


std::string ERS_FUNCTION_GetSceneObjectTypeName(ERS_ENUM_SceneObjectType Type);
ERS_ENUM_SceneObjectType ERS_FUNCTION_GetSceneObjectTypeFromName(const std::string& Type);
std::uint64_t ERS_FUNCTION_CreateSceneEntityID(ERS_ENUM_SceneObjectType Type, unsigned long Index);


/**
 * @brief Struct containing the info about an object in the scene
 * 
 */
struct ERS_STRUCT_SceneObject {

    std::uint64_t EntityID_ = 0; /**<Runtime Entity ID Generated From The Object Type And Index*/
    ERS_ENUM_SceneObjectType EntityType_ = ERS_ENUM_SceneObjectType::Unknown; /**<Runtime Entity Type*/
    std::string Type_; /**<Name Of The Type Of The Object*/
    std::string Label_; /**<Human Readable Name Of The Object*/
    unsigned long Index_ = 0; /**<Index in respective list (e.g. If Type Is Model, This Would Be The Index In The Model List)*/

};

//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <utility>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <Camera.h>
#include <Scene.h>


/**
 * @brief Utility class for read-only scene sorting operations.
 *
 */
class ERS_CLASS_SceneSorter {

public:

    /**
     * @brief Sort models in a scene by distance from a camera.
     *
     * @param Scene Scene to inspect.
     * @param Camera Camera to sort from.
     * @return std::vector<std::pair<float, unsigned int>> Distance plus model index, sorted nearest first.
     */
    static std::vector<std::pair<float, unsigned int>> SortModelsByDistanceFromCamera(ERS_STRUCT_Scene* Scene, ERS_STRUCT_Camera* Camera);

    /**
     * @brief Sort models in a scene by distance from multiple cameras.
     *
     * @param Scene Scene to inspect.
     * @param Cameras Cameras to sort from.
     * @return std::vector<std::vector<std::pair<float, unsigned int>>> Per-camera sorted model distances.
     */
    static std::vector<std::vector<std::pair<float, unsigned int>>> SortModelsByDistanceFromCameras(ERS_STRUCT_Scene* Scene, std::vector<ERS_STRUCT_Camera*> Cameras);

};

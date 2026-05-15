//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <SceneSorter.h>

// Standard Libraries (BG convention: use <> instead of "")
#include <algorithm>
#include <future>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/geometric.hpp>


std::vector<std::pair<float, unsigned int>> ERS_CLASS_SceneSorter::SortModelsByDistanceFromCamera(ERS_STRUCT_Scene* Scene, ERS_STRUCT_Camera* Camera) {

    std::vector<std::pair<float, unsigned int>> Distances;
    if (Scene == nullptr || Camera == nullptr) {
        return Distances;
    }

    Distances.reserve(Scene->Models.size());
    glm::vec3 CameraPosition = Camera->GetPosition();

    for (unsigned int i = 0; i < Scene->Models.size(); i++) {
        if (Scene->Models[i] == nullptr) {
            continue;
        }

        float TotalDistance = glm::distance(CameraPosition, Scene->Models[i]->ModelPosition);

        glm::vec3 CubeBoundaryBox = Scene->Models[i]->BoxScale_ * Scene->Models[i]->TrueModelScale;
        float ApproxCubeBoundaryDistance = std::max(CubeBoundaryBox.x, std::max(CubeBoundaryBox.y, CubeBoundaryBox.z));
        float Distance = TotalDistance - ApproxCubeBoundaryDistance;

        // Cap distance at 0 when the camera is inside the model bounds.
        Distance = std::max(0.0f, Distance);
        Distances.push_back(std::make_pair(Distance, i));
    }

    std::stable_sort(
        Distances.begin(),
        Distances.end(),
        [](const std::pair<float, unsigned int>& Left, const std::pair<float, unsigned int>& Right) {
            if (Left.first == Right.first) {
                return Left.second < Right.second;
            }
            return Left.first < Right.first;
        }
    );

    return Distances;
}

std::vector<std::vector<std::pair<float, unsigned int>>> ERS_CLASS_SceneSorter::SortModelsByDistanceFromCameras(ERS_STRUCT_Scene* Scene, std::vector<ERS_STRUCT_Camera*> Cameras) {

    std::vector<std::vector<std::pair<float, unsigned int>>> DistancesFromCamera(Cameras.size());
    if (Scene == nullptr || Cameras.size() == 0) {
        return DistancesFromCamera;
    }

    if (Cameras.size() == 1) {
        DistancesFromCamera[0] = SortModelsByDistanceFromCamera(Scene, Cameras[0]);
        return DistancesFromCamera;
    }

    std::vector<std::future<std::vector<std::pair<float, unsigned int>>>> SortTasks;
    SortTasks.reserve(Cameras.size());
    for (unsigned int i = 0; i < Cameras.size(); i++) {
        SortTasks.push_back(std::async(std::launch::async, ERS_CLASS_SceneSorter::SortModelsByDistanceFromCamera, Scene, Cameras[i]));
    }

    for (unsigned int i = 0; i < SortTasks.size(); i++) {
        DistancesFromCamera[i] = SortTasks[i].get();
    }

    return DistancesFromCamera;
}

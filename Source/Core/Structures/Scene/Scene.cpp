//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the scene structure.
    Documentation Status: Done
    Additonal Notes: None
    Date Created: 2021-11-22
*/

#include <Scene.h>


// Define ProcessScene
void ERS_OBJECT_SCENE::ProcessScene(YAML::Node RawSceneData) {

    // Create Vector Of YAML::Nodes
    std::vector<YAML::Node> SceneItems;

    // Populate Vector With Elements From SceneData
    YAML::Node SceneDataNode = RawSceneData["SceneData"];
    for (YAML::const_iterator it=SceneDataNode.begin(); it!=SceneDataNode.end(); ++it) {
        ColorLookup_[it->first.as<int>()] = {
            it->second[0].as<int>(),
            it->second[1].as<int>(),
            it->second[2].as<int>()
        };
    }


}
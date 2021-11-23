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

    // Grab Metadata
    SceneFormatVersion = RawSceneData["SceneFormatVersion"].as<long>();
    SceneName = RawSceneData["SceneName"].as<std::string>();

    // Create Vector Of YAML::Nodes
    std::vector<YAML::Node> SceneItems;

    // Populate Vector With Elements From SceneData
    YAML::Node SceneDataNode = RawSceneData["SceneData"];
    for (YAML::const_iterator it=SceneDataNode.begin(); it!=SceneDataNode.end(); ++it) {
        SceneItems.push_back(it->second;);
    }

    // Iterate Through Vector To Add Each Asset To Loading Queue Of Requested Type
    for (long i = 0; i < SceneDataNode.size(); i++) {

        // Get Asset Information
        std::string AssetName = SceneDataNode[i]["AssetName"].as<std::string>();
        std::string AssetType = SceneDataNode[i]["AssetType"].as<std::string>();
        std::string AssetPath = SceneDataNode[i]["AssetPath"].as<std::string>();

        // Get Asset LocRotScale
        


    }

}
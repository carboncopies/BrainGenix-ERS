//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing scene decoding.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

ERS_STRUCTURE_SCENE  LoadScene(long SceneID, LoggerClass *Logger_, bool LogLoading) {

    // Initialize Vars
    ERS_STRUCTURE_SCENE Scene;

    // ADD CHECK LATER TO SEE IF DATABASE CONNECTED

    bool DatabaseLoad;
    DatabaseLoad = false;

    // Load Scene From Database (Preferred)
    if (DatabaseLoad) {
        // db load code here...
    }

    // Load Scene From LocalFile (Fallback)
    if (!DatabaseLoad) {
        
        // Calculate File Path
        std::string FilePath;
        FilePath = "Assets/Scene/";
        FilePath += std::to_string(SceneID);
        FilePath += ".bg";

        // Log If Enabled
        if (LogLoading) {
            std::string LogString = std::string("Loading Scene File With ID '") + std::to_string(SceneID) + std::string("' Using Local Filesystem");
            Logger_->Log(LogString.c_str(), 4);
        }

        // Load Scene
        Scene.SceneData = YAML::LoadFile(FilePath);

    }

    // Parse Scene Metadata
    Scene.SceneName = Scene.SceneData["Name"].as<std::string>();
    Scene.FormatVersion = Scene.SceneData["FormatVersion"].as<std::string>();

    // Parse Scene Subnodes
    YAML::Node SubnodesMap = Scene.SceneData["Subnodes"];
    for (YAML::const_iterator it=SubnodesMap.begin(); it!=SubnodesMap.end(); ++it) {
        Scene.Subnodes[it->first.as<long>()] = {
            it->second[0].as<std::string>(),
            it->second[1].as<std::string>(),
        };
    }


    // Return Scene
    return Scene;


}


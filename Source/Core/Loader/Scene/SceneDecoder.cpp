//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing scene decoding.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

#include "Core/Loader/Scene/SceneDecoder.h"

ERS_OBJECT_SCENE  LoadScene(long SceneID, LoggerClass *Logger_, bool LogLoading) {

    // Initialize Vars
    ERS_OBJECT_SCENE Scene;

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
        FilePath = "Assets/";
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
    std::cout<<SubnodesMap<<"\n\n************************\n";
    int i = 0;
    for (YAML::const_iterator it=SubnodesMap.begin(); it!=SubnodesMap.end(); ++it) {
        long V1 = it->second["ID"].as<long>();
        YAML::Node V2 = it->second;

        //std::cout<<V1<<"|"<<V2<<std::endl;

        Scene.Subnodes.insert({V1, V2});

        std::cout<<"\n Value Is Now: "<<Scene.Subnodes[i++]<<std::endl<<std::endl;
    }


    std::cout<<Scene.Subnodes[0]<<std::endl;
    std::cout<<"END\n";


    // Return Scene
    return Scene;


}


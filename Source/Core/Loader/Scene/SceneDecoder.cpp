//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing scene decoding.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

YAML::Node LoadScene(long SceneID) {

    // ADD CHECK LATER TO SEE IF DATABASE CONNECTED
    bool DatabaseLoad;

    DatabaseLoad = false

    // IF DB CONNECTED, LOAD FROM DB
    if (DatabaseLoad) {
        // db load code here...
    }


    // File Load Fallback
    if (!DatabaseLoad) {
        
        // Calculate File Path
        std::string FilePath;

    }


}


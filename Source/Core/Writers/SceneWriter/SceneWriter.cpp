//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the scene loader class.
    Documentation Status: Completed
    Additonal Notes: None
    Date Created: 2021-11-22
*/

// FIXME: Make template textures added to their own map so they can be reused.
// FIXME: Make dynamic/static models that can each be rotated/translated (dynamically or statically). Then make updateposition functions, etc.

#include <SceneWriter.h>

// SceneWriter Constructor
SceneWriter::SceneWriter(LoggerClass *Logger) {

    // Create Local Pointer
    Logger_ = Logger;

    // Log Initializaton Start
    Logger_->Log("Initializing SceneWriter Subsystem", 5);

}

// SceneWriter Destructor
SceneWriter::~SceneWriter() {

    // Log Destructor Call
    Logger_->Log("SceneWriter Destructor Called", 6);

}

// Process Scenes
void SceneWriter::ProcessScene(ERS_OBJECT_SCENE InputScene, const char* ScenePath) {

    // Convert Scene To YAML
    const char* ScenefileData = ProcessScene(InputScene); 

    std::cout<<ScenefileData<<std::endl;

    // Write To File
    std::ofstream FileOutput(ScenePath);
    FileOutput<<ScenefileData;
    FileOutput.close();

}

// SceneWriter Process Scene Function
const char* SceneWriter::ProcessScene(ERS_OBJECT_SCENE InputScene) {

    // Log Scene Write
    Logger_->Log(std::string(std::string("Serializing Scene '") + InputScene.SceneName + std::string("'")).c_str(), 4);

    // Create Emitter
    YAML::Emitter Output;


    // Write Metadata
    Output << InputScene.SceneData;

    std::cout<<Output.c_str()<<std::endl;
    // Return Scene
    return Output.c_str();

}


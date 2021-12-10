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

// Load And Process Scene
void SceneWriter::ProcessScene(ERS_OBJECT_SCENE InputScene, const char* ScenePath) {

    // Load Then Process Scene
    //YAML::Emitter OutputScene = ProcessScene(OutputScene); 
    //return YAML::EmitSeq(ScenePath);

}

// SceneWriter Process Scene Function
YAML::Emitter SceneWriter::ProcessScene(ERS_OBJECT_SCENE InputScene) {

    // Create Emitter
    YAML::Emitter Output;

    // Write Metadata
    Output << YAML::Key << "SceneFormatVersion" << YAML::Value << InputScene.SceneFormatVersion;


    // Return Scene
    return Output;

}


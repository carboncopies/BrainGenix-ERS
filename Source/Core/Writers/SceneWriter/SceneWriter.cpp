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
SceneWriter::SceneWriter(LoggerClass *Logger, ModelLoader *ModelLoader) {

    // Create Local Pointer
    Logger_ = Logger;
    ModelLoader_ = ModelLoader;

    // Log Initializaton Start
    Logger_->Log("Initializing SceneWriter Subsystem", 5);

}

// SceneWriter Destructor
SceneWriter::~SceneWriter() {

    // Log Destructor Call
    Logger_->Log("SceneWriter Destructor Called", 6);

}

// Load And Process Scene
ERS_OBJECT_SCENE SceneWriter::ProcessScene(const char* ScenePath) {

    // Load Then Process Scene
    YAML::Node TestScene = YAML::LoadFile(ScenePath);
    return ProcessScene(TestScene);

}

// SceneWriter Process Scene Function
ERS_OBJECT_SCENE SceneWriter::ProcessScene(YAML::Node RawSceneData) {

    // Create Scene Instance
    ERS_OBJECT_SCENE Scene;

    // Grab Metadata
    Scene.SceneFormatVersion = RawSceneData["SceneFormatVersion"].as<long>();
    Scene.SceneName = RawSceneData["SceneName"].as<std::string>();

    // Log Scene Processing
    Logger_->Log(std::string(std::string("Processing Scene: ") + std::string(Scene.SceneName)).c_str(), 4);

    // Create Vector Of YAML::Nodes
    std::vector<YAML::Node> SceneItems;

    // Populate Vector With Elements From SceneData
    YAML::Node SceneDataNode = RawSceneData["SceneData"];
    for (YAML::const_iterator it=SceneDataNode.begin(); it!=SceneDataNode.end(); ++it) {
        SceneItems.push_back(it->second);
    }

    
    // Iterate Through Vector To Add Each Asset To Loading Queue Of Requested Type
    for (long i = 0; i < SceneDataNode.size(); i++) {

        // Get Asset Information
        std::string AssetName = SceneDataNode[i]["AssetName"].as<std::string>();
        std::string AssetType = SceneDataNode[i]["AssetType"].as<std::string>();
        std::string AssetPath = SceneDataNode[i]["AssetPath"].as<std::string>();


        // If type Is Model
        if (AssetType == std::string("Model")) {

            // Get Model Texture Info
            bool FlipTextures = SceneDataNode[i]["FlipTextures"].as<bool>();

            // Get Asset LocRotScale
            float PosX = SceneDataNode[i]["AssetPositionX"].as<double>();
            float PosY = SceneDataNode[i]["AssetPositionY"].as<double>();
            float PosZ = SceneDataNode[i]["AssetPositionZ"].as<double>();

            float RotX = SceneDataNode[i]["AssetRotationX"].as<double>();
            float RotY = SceneDataNode[i]["AssetRotationY"].as<double>();
            float RotZ = SceneDataNode[i]["AssetRotationZ"].as<double>();

            float ScaleX = SceneDataNode[i]["AssetScaleX"].as<double>();
            float ScaleY = SceneDataNode[i]["AssetScaleY"].as<double>();
            float ScaleZ = SceneDataNode[i]["AssetScaleZ"].as<double>();

            // Check If Model Already Loaded
            int ModelIndex;


            

            if (TemplateModels_.count(AssetPath) != 0) {

                // Create New Model Struct
                ERS_OBJECT_MODEL Model;
                
                // Copy In Parameters
                Model.Directory = TemplateModels_[AssetPath].Directory;
                Model.AssetPath_ = TemplateModels_[AssetPath].AssetPath_;
                Model.GammaCorrection = TemplateModels_[AssetPath].GammaCorrection;
                Model.HasTexturesLoaded = TemplateModels_[AssetPath].HasTexturesLoaded;
                Model.Name = AssetName;

                // Copy Texture References
                Model.Textures_Loaded = TemplateModels_[AssetPath].Textures_Loaded;

                // Copy In Mesh References
                for (int i = 0; i < TemplateModels_[AssetPath].Meshes.size(); i++) {

                    std::vector<ERS_OBJECT_VERTEX> Vertices;
                    std::vector<unsigned int> Indices;
                    std::vector<ERS_OBJECT_TEXTURE_2D> Textures = TemplateModels_[AssetPath].Meshes[i].Textures;

                    ERS_OBJECT_MESH Mesh(Vertices, Indices, Textures);
                    Mesh.NumberIndices = TemplateModels_[AssetPath].Meshes[i].NumberIndices;
                    Mesh.VAO = TemplateModels_[AssetPath].Meshes[i].VAO;


                    Model.Meshes.push_back(Mesh);

                }



                // Apply Transformations
                Model.SetLocRotScale(glm::vec3(PosX, PosY, PosZ), glm::vec3(RotX, RotY, RotZ), glm::vec3(ScaleX, ScaleY, ScaleZ));
                Model.ApplyTransformations();

                // Append To Models Vector
                Scene.Models.push_back(Model);

                // Log Duplicate
                Logger_->Log(std::string(std::string("Model Already In Template Buffer, Using Template For: ") + AssetPath).c_str(), 3);


            } else { // Load Model And Add To Template

                // Load Model 
                ERS_OBJECT_MODEL Model = ModelLoader_->LoadModelFromFile(AssetPath.c_str(), FlipTextures);

                // Set Name
                Model.Name = AssetName;

                // Copy To Template Map
                Model.IsTemplateModel = true;
                TemplateModels_.insert({AssetPath, Model});

                // Add Instance To Models Vector
                Model.IsTemplateModel = false;
                Model.SetLocRotScale(glm::vec3(PosX, PosY, PosZ), glm::vec3(RotX, RotY, RotZ), glm::vec3(ScaleX, ScaleY, ScaleZ));
                Model.ApplyTransformations();
                Scene.Models.push_back(Model);
            }

        }


    }

    // Indicate Scene Is Loaded
    Scene.IsSceneLoaded = true;

    // Return Scene
    return Scene;

}


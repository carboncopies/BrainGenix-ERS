//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <PythonInterpreterIntegration.h>


// yes this is bad i know, but idk how else to fix it
#include <PyBind11ModelClass.cpp>
#include <PyBind11SystemInfo.cpp>
#include <PyBind11DirectionalLightClass.cpp>
#include <PyBind11PointLightClass.cpp>
#include <PyBind11SpotLightClass.cpp>



ERS_CLASS_PythonInterpreterIntegration::ERS_CLASS_PythonInterpreterIntegration(BG::Common::Logger::LoggingSystem* Logger) {

    Logger_ = Logger;

    Logger_->Log("Initializing Python Interpreter Subsystem", 5);


    // Start Python Interpreter
    Logger_->Log("Starting Python Interpreter", 5);
    Guard_ = std::make_unique<pybind11::scoped_interpreter>();
    Logger_->Log("Finished Starting Python Interpreter", 4);
    
}

ERS_CLASS_PythonInterpreterIntegration::~ERS_CLASS_PythonInterpreterIntegration() {

    Logger_->Log("Shutting Down Python Interpreter Subsystem", 6);

}



bool ERS_CLASS_PythonInterpreterIntegration::ExecuteModelScript(std::string ScriptSource, ERS_STRUCT_Model* Model, std::vector<std::string>* ErrorMessageString) {


    // Inport The Model Module, Set System Info
    pybind11::module ModelModule = pybind11::module_::import("Model");
    SetSystemInfoData(&ModelModule);

    // Set System Parameters
    ModelModule.attr("PosX") = Model->ModelPosition.x;
    ModelModule.attr("PosY") = Model->ModelPosition.y;
    ModelModule.attr("PosZ") = Model->ModelPosition.z;
    ModelModule.attr("RotX") = Model->ModelRotation.x;
    ModelModule.attr("RotY") = Model->ModelRotation.y;
    ModelModule.attr("RotZ") = Model->ModelRotation.z;
    ModelModule.attr("ScaleX") = Model->ModelScale.x;
    ModelModule.attr("ScaleY") = Model->ModelScale.y;
    ModelModule.attr("ScaleZ") = Model->ModelScale.z;

    ModelModule.attr("Enabled") = Model->Enabled;


    // Get Local Dict
    pybind11::dict Locals = ModelModule.attr("__dict__");

    // If No Message String Vec Provided, Run All At Once, Else Run Line By Line
    if (ErrorMessageString == nullptr) {
        try {
            pybind11::exec(ScriptSource, pybind11::globals(), Locals);
        } catch (pybind11::value_error const&) {
            return false;
        } catch (pybind11::key_error const&) {
            return false;
        } catch (pybind11::reference_cast_error const&) {
            return false;
        } catch (pybind11::attribute_error const&) {
            return false;
        } catch (pybind11::import_error const&) {
            return false;
        } catch (pybind11::buffer_error const&) {
            return false;
        } catch (pybind11::index_error const&) {
            return false;
        } catch (pybind11::type_error const&) {
            return false;
        } catch (pybind11::cast_error const&) {
            return false;
        } catch (pybind11::error_already_set &Exception) {
            return false;
        }

    } else {
        ErrorMessageString->erase(ErrorMessageString->begin(), ErrorMessageString->end());
        std::string Line;
        std::stringstream StringStream(ScriptSource);
        unsigned long i = 0;

        while (getline(StringStream, Line, '\n')) {
            
            i++;
            try {
                pybind11::exec(Line, pybind11::globals(), Locals);
            } catch (pybind11::value_error const&) {
                ErrorHandle(ErrorMessageString, i, "ValueError");
            } catch (pybind11::key_error const&) {
                ErrorHandle(ErrorMessageString, i, "KeyError");
            } catch (pybind11::reference_cast_error const&) {
                ErrorHandle(ErrorMessageString, i, "ReferenceCastError");
            } catch (pybind11::attribute_error const&) {
                ErrorHandle(ErrorMessageString, i, "AttributeError");
            } catch (pybind11::import_error const&) {
                ErrorHandle(ErrorMessageString, i, "ImportError");
            } catch (pybind11::buffer_error const&) {
                ErrorHandle(ErrorMessageString, i, "BufferError");
            } catch (pybind11::index_error const&) {
                ErrorHandle(ErrorMessageString, i, "IndexError");
            } catch (pybind11::type_error const&) {
                ErrorHandle(ErrorMessageString, i, "TypeError");
            } catch (pybind11::cast_error const&) {
                ErrorHandle(ErrorMessageString, i, "CastError");
            } catch (pybind11::error_already_set &Exception) {
                ErrorHandle(ErrorMessageString, i, Exception.what());
            }

        }

    }

    // Write Back Model Data
    double ModelPosX, ModelPosY, ModelPosZ;
    double ModelRotX, ModelRotY, ModelRotZ;
    double ModelScaleX, ModelScaleY, ModelScaleZ;
    bool Successful = true;

    try {
        ModelPosX = ModelModule.attr("PosX").cast<double>();
        ModelPosY = ModelModule.attr("PosY").cast<double>();
        ModelPosZ = ModelModule.attr("PosZ").cast<double>();
        Model->SetPosition(glm::vec3(ModelPosX, ModelPosY, ModelPosZ));
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("Model Position CAST_ERROR");
        Successful = false;
    }
    try {
        ModelRotX = ModelModule.attr("RotX").cast<double>();
        ModelRotY = ModelModule.attr("RotY").cast<double>();
        ModelRotZ = ModelModule.attr("RotZ").cast<double>();
        Model->SetRotation(glm::vec3(ModelRotX, ModelRotY, ModelRotZ));
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("Model Rotation CAST_ERROR");
        Successful = false;
    }
    try {
        ModelScaleX = ModelModule.attr("ScaleX").cast<double>();
        ModelScaleY = ModelModule.attr("ScaleY").cast<double>();
        ModelScaleZ = ModelModule.attr("ScaleZ").cast<double>();
        Model->SetScale(glm::vec3(ModelScaleX, ModelScaleY, ModelScaleZ));
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("Model Scale CAST_ERROR");
        Successful = false;
    }

    try {
        Model->Enabled = ModelModule.attr("Enabled").cast<bool>(); 
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("Model Enable CAST_ERROR");
        Successful = false;
    }


    if (Successful) {
        Model->ApplyTransformations();
    }
    


    // Return Status
    return true;
    

}



bool ERS_CLASS_PythonInterpreterIntegration::ExecuteSceneCameraScript(std::string ScriptSource, ERS_STRUCT_SceneCamera* Camera, std::vector<std::string>* ErrorMessageString) {


    // Inport The Camera Module, Set System Info
    pybind11::module CameraModule = pybind11::module_::import("Camera");
    SetSystemInfoData(&CameraModule);

    // Set System Parameters
    CameraModule.attr("PosX") = Camera->Pos_.x;
    CameraModule.attr("PosY") = Camera->Pos_.y;
    CameraModule.attr("PosZ") = Camera->Pos_.z;
    CameraModule.attr("RotX") = Camera->Rot_.x;
    CameraModule.attr("RotY") = Camera->Rot_.y;
    CameraModule.attr("RotZ") = Camera->Rot_.z;

    CameraModule.attr("FOV") = Camera->FOV_;
    CameraModule.attr("Priority") = Camera->StreamingPriority_;


    // Get Local Dict
    pybind11::dict Locals = CameraModule.attr("__dict__");

    // If No Message String Vec Provided, Run All At Once, Else Run Line By Line
    if (ErrorMessageString == nullptr) {
        try {
            pybind11::exec(ScriptSource, pybind11::globals(), Locals);
        } catch (pybind11::value_error const&) {
            return false;
        } catch (pybind11::key_error const&) {
            return false;
        } catch (pybind11::reference_cast_error const&) {
            return false;
        } catch (pybind11::attribute_error const&) {
            return false;
        } catch (pybind11::import_error const&) {
            return false;
        } catch (pybind11::buffer_error const&) {
            return false;
        } catch (pybind11::index_error const&) {
            return false;
        } catch (pybind11::type_error const&) {
            return false;
        } catch (pybind11::cast_error const&) {
            return false;
        } catch (pybind11::error_already_set &Exception) {
            return false;
        }

    } else {
        ErrorMessageString->erase(ErrorMessageString->begin(), ErrorMessageString->end());
        std::string Line;
        std::stringstream StringStream(ScriptSource);
        unsigned long i = 0;

        while (getline(StringStream, Line, '\n')) {
            
            i++;
            try {
                pybind11::exec(Line, pybind11::globals(), Locals);
            } catch (pybind11::value_error const&) {
                ErrorHandle(ErrorMessageString, i, "ValueError");
            } catch (pybind11::key_error const&) {
                ErrorHandle(ErrorMessageString, i, "KeyError");
            } catch (pybind11::reference_cast_error const&) {
                ErrorHandle(ErrorMessageString, i, "ReferenceCastError");
            } catch (pybind11::attribute_error const&) {
                ErrorHandle(ErrorMessageString, i, "AttributeError");
            } catch (pybind11::import_error const&) {
                ErrorHandle(ErrorMessageString, i, "ImportError");
            } catch (pybind11::buffer_error const&) {
                ErrorHandle(ErrorMessageString, i, "BufferError");
            } catch (pybind11::index_error const&) {
                ErrorHandle(ErrorMessageString, i, "IndexError");
            } catch (pybind11::type_error const&) {
                ErrorHandle(ErrorMessageString, i, "TypeError");
            } catch (pybind11::cast_error const&) {
                ErrorHandle(ErrorMessageString, i, "CastError");
            } catch (pybind11::error_already_set &Exception) {
                ErrorHandle(ErrorMessageString, i, Exception.what());
            }

        }

    }

    // Write Back Camera Data
    try {
        double CameraPosX, CameraPosY, CameraPosZ;
        CameraPosX = CameraModule.attr("PosX").cast<double>();
        CameraPosY = CameraModule.attr("PosY").cast<double>();
        CameraPosZ = CameraModule.attr("PosZ").cast<double>();
        Camera->Pos_ = glm::vec3(CameraPosX, CameraPosY, CameraPosZ);
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("Camera Position CAST_ERROR");
    }
    try {
        double CameraRotX, CameraRotY, CameraRotZ;
        CameraRotX = CameraModule.attr("RotX").cast<double>();
        CameraRotY = CameraModule.attr("RotY").cast<double>();
        CameraRotZ = CameraModule.attr("RotZ").cast<double>();
        Camera->Rot_ = glm::vec3(CameraRotX, CameraRotY, CameraRotZ);
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("Camera Rotation CAST_ERROR");
    }

    try {
        float FOV;
        FOV = CameraModule.attr("FOV").cast<float>();
        Camera->FOV_ = FOV;
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("Camera FOV CAST_ERROR");
    }

    try {
        float Priority;
        Priority = CameraModule.attr("Priority").cast<float>();
        Camera->StreamingPriority_ = Priority;
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("Camera Asset Streaming Priority CAST_ERROR");
    }


    // Return Status
    return true;
    

}



bool ERS_CLASS_PythonInterpreterIntegration::ExecutePointLightScript(std::string ScriptSource, ERS_STRUCT_PointLight* PointLight, std::vector<std::string>* ErrorMessageString) {



    // Inport The PointLight Module, Set System Info
    pybind11::module PointLightModule = pybind11::module_::import("PointLight");
    SetSystemInfoData(&PointLightModule);

    // Set System Parameters
    PointLightModule.attr("PosX") = PointLight->Pos.x;
    PointLightModule.attr("PosY") = PointLight->Pos.y;
    PointLightModule.attr("PosZ") = PointLight->Pos.z;

    PointLightModule.attr("ColorR") = PointLight->Color.r;
    PointLightModule.attr("ColorG") = PointLight->Color.g;
    PointLightModule.attr("ColorB") = PointLight->Color.b;
    
    PointLightModule.attr("Intensity") = PointLight->Intensity;
    PointLightModule.attr("MaxDistance") = PointLight->MaxDistance;
    

    // Get Local Dict
    pybind11::dict Locals = PointLightModule.attr("__dict__");

    // If No Message String Vec Provided, Run All At Once, Else Run Line By Line
    if (ErrorMessageString == nullptr) {
        try {
            pybind11::exec(ScriptSource, pybind11::globals(), Locals);
        } catch (pybind11::value_error const&) {
            return false;
        } catch (pybind11::key_error const&) {
            return false;
        } catch (pybind11::reference_cast_error const&) {
            return false;
        } catch (pybind11::attribute_error const&) {
            return false;
        } catch (pybind11::import_error const&) {
            return false;
        } catch (pybind11::buffer_error const&) {
            return false;
        } catch (pybind11::index_error const&) {
            return false;
        } catch (pybind11::type_error const&) {
            return false;
        } catch (pybind11::cast_error const&) {
            return false;
        } catch (pybind11::error_already_set &Exception) {
            return false;
        }

    } else {
        ErrorMessageString->erase(ErrorMessageString->begin(), ErrorMessageString->end());
        std::string Line;
        std::stringstream StringStream(ScriptSource);
        unsigned long i = 0;

        while (getline(StringStream, Line, '\n')) {
            
            i++;
            try {
                pybind11::exec(Line, pybind11::globals(), Locals);
            } catch (pybind11::value_error const&) {
                ErrorHandle(ErrorMessageString, i, "ValueError");
            } catch (pybind11::key_error const&) {
                ErrorHandle(ErrorMessageString, i, "KeyError");
            } catch (pybind11::reference_cast_error const&) {
                ErrorHandle(ErrorMessageString, i, "ReferenceCastError");
            } catch (pybind11::attribute_error const&) {
                ErrorHandle(ErrorMessageString, i, "AttributeError");
            } catch (pybind11::import_error const&) {
                ErrorHandle(ErrorMessageString, i, "ImportError");
            } catch (pybind11::buffer_error const&) {
                ErrorHandle(ErrorMessageString, i, "BufferError");
            } catch (pybind11::index_error const&) {
                ErrorHandle(ErrorMessageString, i, "IndexError");
            } catch (pybind11::type_error const&) {
                ErrorHandle(ErrorMessageString, i, "TypeError");
            } catch (pybind11::cast_error const&) {
                ErrorHandle(ErrorMessageString, i, "CastError");
            } catch (pybind11::error_already_set &Exception) {
                ErrorHandle(ErrorMessageString, i, Exception.what());
            }

        }

    }

    // Write Back PointLight Data
    double PointLightPosX, PointLightPosY, PointLightPosZ;
    float ColorR, ColorG, ColorB;

    try {
        PointLightPosX = PointLightModule.attr("PosX").cast<double>();
        PointLightPosY = PointLightModule.attr("PosY").cast<double>();
        PointLightPosZ = PointLightModule.attr("PosZ").cast<double>();
        PointLight->Pos = glm::vec3(PointLightPosX, PointLightPosY, PointLightPosZ);
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("PointLight Position CAST_ERROR");
    }

    try {
        ColorR = PointLightModule.attr("ColorR").cast<double>();
        ColorG = PointLightModule.attr("ColorG").cast<double>();
        ColorB = PointLightModule.attr("ColorB").cast<double>();
        PointLight->Color = glm::vec3(ColorR, ColorG, ColorB);
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("PointLight Color CAST_ERROR");
    }

    try {
        PointLight->Intensity = PointLightModule.attr("Intensity").cast<float>();
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("PointLight Intensity CAST_ERROR");
    }

    try {
        PointLight->Intensity = PointLightModule.attr("Distance").cast<float>();
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("PointLight MaxDistance CAST_ERROR");
    }


    // Return Status
    return true;
    

}

bool ERS_CLASS_PythonInterpreterIntegration::ExecuteDirectionalLightScript(std::string ScriptSource, ERS_STRUCT_DirectionalLight* DirectionalLight, std::vector<std::string>* ErrorMessageString) {



    // Inport The DirectionalLight Module, Set System Info
    pybind11::module DirectionalLightModule = pybind11::module_::import("DirectionalLight");
    SetSystemInfoData(&DirectionalLightModule);

    // Set System Parameters
    DirectionalLightModule.attr("PosX") = DirectionalLight->Pos.x;
    DirectionalLightModule.attr("PosY") = DirectionalLight->Pos.y;
    DirectionalLightModule.attr("PosZ") = DirectionalLight->Pos.z;

    DirectionalLightModule.attr("RotX") = DirectionalLight->Rot.x;
    DirectionalLightModule.attr("RotY") = DirectionalLight->Rot.y;
    DirectionalLightModule.attr("RotZ") = DirectionalLight->Rot.z;

    DirectionalLightModule.attr("ColorR") = DirectionalLight->Color.r;
    DirectionalLightModule.attr("ColorG") = DirectionalLight->Color.g;
    DirectionalLightModule.attr("ColorB") = DirectionalLight->Color.b;

    DirectionalLightModule.attr("Intensity") = DirectionalLight->Intensity;    
    DirectionalLightModule.attr("Distance") = DirectionalLight->MaxDistance;   

    // Get Local Dict
    pybind11::dict Locals = DirectionalLightModule.attr("__dict__");

    // If No Message String Vec Provided, Run All At Once, Else Run Line By Line
    if (ErrorMessageString == nullptr) {
        try {
            pybind11::exec(ScriptSource, pybind11::globals(), Locals);
        } catch (pybind11::value_error const&) {
            return false;
        } catch (pybind11::key_error const&) {
            return false;
        } catch (pybind11::reference_cast_error const&) {
            return false;
        } catch (pybind11::attribute_error const&) {
            return false;
        } catch (pybind11::import_error const&) {
            return false;
        } catch (pybind11::buffer_error const&) {
            return false;
        } catch (pybind11::index_error const&) {
            return false;
        } catch (pybind11::type_error const&) {
            return false;
        } catch (pybind11::cast_error const&) {
            return false;
        } catch (pybind11::error_already_set &Exception) {
            return false;
        }

    } else {
        ErrorMessageString->erase(ErrorMessageString->begin(), ErrorMessageString->end());
        std::string Line;
        std::stringstream StringStream(ScriptSource);
        unsigned long i = 0;

        while (getline(StringStream, Line, '\n')) {
            
            i++;
            try {
                pybind11::exec(Line, pybind11::globals(), Locals);
            } catch (pybind11::value_error const&) {
                ErrorHandle(ErrorMessageString, i, "ValueError");
            } catch (pybind11::key_error const&) {
                ErrorHandle(ErrorMessageString, i, "KeyError");
            } catch (pybind11::reference_cast_error const&) {
                ErrorHandle(ErrorMessageString, i, "ReferenceCastError");
            } catch (pybind11::attribute_error const&) {
                ErrorHandle(ErrorMessageString, i, "AttributeError");
            } catch (pybind11::import_error const&) {
                ErrorHandle(ErrorMessageString, i, "ImportError");
            } catch (pybind11::buffer_error const&) {
                ErrorHandle(ErrorMessageString, i, "BufferError");
            } catch (pybind11::index_error const&) {
                ErrorHandle(ErrorMessageString, i, "IndexError");
            } catch (pybind11::type_error const&) {
                ErrorHandle(ErrorMessageString, i, "TypeError");
            } catch (pybind11::cast_error const&) {
                ErrorHandle(ErrorMessageString, i, "CastError");
            } catch (pybind11::error_already_set &Exception) {
                ErrorHandle(ErrorMessageString, i, Exception.what());
            }

        }

    }

    // Write Back DirectionalLight Data
    double DirectionalLightPosX, DirectionalLightPosY, DirectionalLightPosZ;
    double DirectionalLightRotX, DirectionalLightRotY, DirectionalLightRotZ;
    float ColorR, ColorG, ColorB;

    try {
        DirectionalLightPosX = DirectionalLightModule.attr("PosX").cast<double>();
        DirectionalLightPosY = DirectionalLightModule.attr("PosY").cast<double>();
        DirectionalLightPosZ = DirectionalLightModule.attr("PosZ").cast<double>();
        DirectionalLight->Pos = glm::vec3(DirectionalLightPosX, DirectionalLightPosY, DirectionalLightPosZ);
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("DirectionalLight Position CAST_ERROR");
    }

    try {
        DirectionalLightRotX = DirectionalLightModule.attr("RotX").cast<double>();
        DirectionalLightRotY = DirectionalLightModule.attr("RotY").cast<double>();
        DirectionalLightRotZ = DirectionalLightModule.attr("RotZ").cast<double>();
        DirectionalLight->Rot = glm::vec3(DirectionalLightRotX, DirectionalLightRotY, DirectionalLightRotZ);
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("DirectionalLight Rotation CAST_ERROR");
    }

    try {
        ColorR = DirectionalLightModule.attr("ColorR").cast<double>();
        ColorG = DirectionalLightModule.attr("ColorG").cast<double>();
        ColorB = DirectionalLightModule.attr("ColorB").cast<double>();
        DirectionalLight->Color = glm::vec3(ColorR, ColorG, ColorB);
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("DirectionalLight Color CAST_ERROR");
    }


    try {
        DirectionalLight->Intensity = DirectionalLightModule.attr("Intensity").cast<float>();
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("DirectionalLight Intensity CAST_ERROR");
    }

    try {
        DirectionalLight->Intensity = DirectionalLightModule.attr("Distance").cast<float>();
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("DirectionalLight MaxDistance CAST_ERROR");
    }



    // Return Status
    return true;
    
}

bool ERS_CLASS_PythonInterpreterIntegration::ExecuteSpotLightScript(std::string ScriptSource, ERS_STRUCT_SpotLight* SpotLight, std::vector<std::string>* ErrorMessageString) {



    // Inport The SpotLight Module, Set System Info
    pybind11::module SpotLightModule = pybind11::module_::import("SpotLight");
    SetSystemInfoData(&SpotLightModule);

    // Set System Parameters
    SpotLightModule.attr("PosX") = SpotLight->Pos.x;
    SpotLightModule.attr("PosY") = SpotLight->Pos.y;
    SpotLightModule.attr("PosZ") = SpotLight->Pos.z;

    SpotLightModule.attr("RotX") = SpotLight->Rot.x;
    SpotLightModule.attr("RotY") = SpotLight->Rot.y;
    SpotLightModule.attr("RotZ") = SpotLight->Rot.z;

    SpotLightModule.attr("ColorR") = SpotLight->Color.r;
    SpotLightModule.attr("ColorG") = SpotLight->Color.g;
    SpotLightModule.attr("ColorB") = SpotLight->Color.b;
    
    SpotLightModule.attr("Intensity") = SpotLight->Intensity;
    SpotLightModule.attr("Distance") = SpotLight->MaxDistance;
    
    SpotLightModule.attr("Cutoff") = SpotLight->CutOff;
    SpotLightModule.attr("Rolloff") = SpotLight->Rolloff;
 

    // Get Local Dict
    pybind11::dict Locals = SpotLightModule.attr("__dict__");

    // If No Message String Vec Provided, Run All At Once, Else Run Line By Line
    if (ErrorMessageString == nullptr) {
        try {
            pybind11::exec(ScriptSource, pybind11::globals(), Locals);
        } catch (pybind11::value_error const&) {
            return false;
        } catch (pybind11::key_error const&) {
            return false;
        } catch (pybind11::reference_cast_error const&) {
            return false;
        } catch (pybind11::attribute_error const&) {
            return false;
        } catch (pybind11::import_error const&) {
            return false;
        } catch (pybind11::buffer_error const&) {
            return false;
        } catch (pybind11::index_error const&) {
            return false;
        } catch (pybind11::type_error const&) {
            return false;
        } catch (pybind11::cast_error const&) {
            return false;
        } catch (pybind11::error_already_set &Exception) {
            return false;
        }

    } else {
        ErrorMessageString->erase(ErrorMessageString->begin(), ErrorMessageString->end());
        std::string Line;
        std::stringstream StringStream(ScriptSource);
        unsigned long i = 0;

        while (getline(StringStream, Line, '\n')) {
            
            i++;
            try {
                pybind11::exec(Line, pybind11::globals(), Locals);
            } catch (pybind11::value_error const&) {
                ErrorHandle(ErrorMessageString, i, "ValueError");
            } catch (pybind11::key_error const&) {
                ErrorHandle(ErrorMessageString, i, "KeyError");
            } catch (pybind11::reference_cast_error const&) {
                ErrorHandle(ErrorMessageString, i, "ReferenceCastError");
            } catch (pybind11::attribute_error const&) {
                ErrorHandle(ErrorMessageString, i, "AttributeError");
            } catch (pybind11::import_error const&) {
                ErrorHandle(ErrorMessageString, i, "ImportError");
            } catch (pybind11::buffer_error const&) {
                ErrorHandle(ErrorMessageString, i, "BufferError");
            } catch (pybind11::index_error const&) {
                ErrorHandle(ErrorMessageString, i, "IndexError");
            } catch (pybind11::type_error const&) {
                ErrorHandle(ErrorMessageString, i, "TypeError");
            } catch (pybind11::cast_error const&) {
                ErrorHandle(ErrorMessageString, i, "CastError");
            } catch (pybind11::error_already_set &Exception) {
                ErrorHandle(ErrorMessageString, i, Exception.what());
            }

        }

    }

    // Write Back SpotLight Data
    double SpotLightPosX, SpotLightPosY, SpotLightPosZ;
    double SpotLightRotX, SpotLightRotY, SpotLightRotZ;
    float ColorR, ColorG, ColorB;

    try {
        SpotLightPosX = SpotLightModule.attr("PosX").cast<double>();
        SpotLightPosY = SpotLightModule.attr("PosY").cast<double>();
        SpotLightPosZ = SpotLightModule.attr("PosZ").cast<double>();
        SpotLight->Pos = glm::vec3(SpotLightPosX, SpotLightPosY, SpotLightPosZ);
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("SpotLight Position CAST_ERROR");
    }

    try {
        SpotLightRotX = SpotLightModule.attr("RotX").cast<double>();
        SpotLightRotY = SpotLightModule.attr("RotY").cast<double>();
        SpotLightRotZ = SpotLightModule.attr("RotZ").cast<double>();
        SpotLight->Rot = glm::vec3(SpotLightRotX, SpotLightRotY, SpotLightRotZ);
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("SpotLight Rotation CAST_ERROR");
    }

    try {
        ColorR = SpotLightModule.attr("ColorR").cast<double>();
        ColorG = SpotLightModule.attr("ColorG").cast<double>();
        ColorB = SpotLightModule.attr("ColorB").cast<double>();
        SpotLight->Color = glm::vec3(ColorR, ColorG, ColorB);
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("SpotLight Color CAST_ERROR");
    }

    try {
        SpotLight->Intensity = SpotLightModule.attr("Intensity").cast<float>();
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("SpotLight Intensity CAST_ERROR");
    }


    try {
        SpotLight->MaxDistance = SpotLightModule.attr("Distance").cast<float>();
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("SpotLight Rolloff CAST_ERROR");
    }



    try {
        SpotLight->CutOff = SpotLightModule.attr("Cutoff").cast<float>();
        SpotLight->Rolloff = SpotLightModule.attr("Rolloff").cast<float>();
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("SpotLight Cutoff CAST_ERROR");
    }


    // Return Status
    return true;
    
}

void ERS_CLASS_PythonInterpreterIntegration::ErrorHandle(std::vector<std::string>* Target, unsigned long LineNumber, std::string Error) {

    std::string ErrorMessage = std::string("Error On Line '") + std::to_string(LineNumber) + std::string("': ") + Error + std::string("\n");
    Target->push_back(ErrorMessage);


}

void ERS_CLASS_PythonInterpreterIntegration::UpdateSystemInfoData(double RunTime) {

    RunTime_ = RunTime;

}

void ERS_CLASS_PythonInterpreterIntegration::SetSystemInfoData(pybind11::module* Locals) {

    // Set System Info Module
    pybind11::module SystemInfo = pybind11::module_::import("SystemInfo");
    Locals->attr("GameTime") = pybind11::float_(RunTime_);

    auto Clock = std::chrono::system_clock::now();
    long double UnixEpoch = std::chrono::duration_cast<std::chrono::seconds>(Clock.time_since_epoch()).count();
    Locals->attr("SystemTime") = UnixEpoch;

}
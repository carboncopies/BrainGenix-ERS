//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_PythonInterpreterIntegration.h>


// yes this is bad i know, but idk how else to fix it
#include <PyBind11ModelClass.cpp>
#include <PyBind11SystemInfo.cpp>
#include <PyBind11DirectionalLightClass.cpp>
#include <PyBind11PointLightClass.cpp>
#include <PyBind11SpotLightClass.cpp>



ERS_CLASS_PythonInterpreterIntegration::ERS_CLASS_PythonInterpreterIntegration(ERS_CLASS_LoggingSystem* Logger) {

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
    ModelModule.attr("ModelPosX") = Model->ModelPosition.x;
    ModelModule.attr("ModelPosY") = Model->ModelPosition.y;
    ModelModule.attr("ModelPosZ") = Model->ModelPosition.z;
    ModelModule.attr("ModelRotX") = Model->ModelRotation.x;
    ModelModule.attr("ModelRotY") = Model->ModelRotation.y;
    ModelModule.attr("ModelRotZ") = Model->ModelRotation.z;
    ModelModule.attr("ModelScaleX") = Model->ModelScale.x;
    ModelModule.attr("ModelScaleY") = Model->ModelScale.y;
    ModelModule.attr("ModelScaleZ") = Model->ModelScale.z;

    ModelModule.attr("ModelEnabled") = Model->Enabled;


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
        ModelPosX = ModelModule.attr("ModelPosX").cast<double>();
        ModelPosY = ModelModule.attr("ModelPosY").cast<double>();
        ModelPosZ = ModelModule.attr("ModelPosZ").cast<double>();
        Model->SetPosition(glm::vec3(ModelPosX, ModelPosY, ModelPosZ));
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("Model Position CAST_ERROR");
        Successful = false;
    }
    try {
        ModelRotX = ModelModule.attr("ModelRotX").cast<double>();
        ModelRotY = ModelModule.attr("ModelRotY").cast<double>();
        ModelRotZ = ModelModule.attr("ModelRotZ").cast<double>();
        Model->SetRotation(glm::vec3(ModelRotX, ModelRotY, ModelRotZ));
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("Model Rotation CAST_ERROR");
        Successful = false;
    }
    try {
        ModelScaleX = ModelModule.attr("ModelScaleX").cast<double>();
        ModelScaleY = ModelModule.attr("ModelScaleY").cast<double>();
        ModelScaleZ = ModelModule.attr("ModelScaleZ").cast<double>();
        Model->SetScale(glm::vec3(ModelScaleX, ModelScaleY, ModelScaleZ));
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("Model Scale CAST_ERROR");
        Successful = false;
    }

    try {
        Model->Enabled = ModelModule.attr("ModelEnabled").cast<bool>(); 
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

bool ERS_CLASS_PythonInterpreterIntegration::ExecutePointLightScript(std::string ScriptSource, ERS_STRUCT_PointLight* PointLight, std::vector<std::string>* ErrorMessageString = nullptr) {



    // Inport The PointLight Module, Set System Info
    pybind11::module PointLightModule = pybind11::module_::import("PointLight");
    SetSystemInfoData(&PointLightModule);

    // Set System Parameters
    PointLightModule.attr("PointLightPosX") = PointLight->Pos.x;
    PointLightModule.attr("PointLightPosY") = PointLight->Pos.y;
    PointLightModule.attr("PointLightPosZ") = PointLight->Pos.z;

    PointLightModule.attr("PointLightDiffuseR") = PointLight->Diffuse.r;
    PointLightModule.attr("PointLightDiffuseG") = PointLight->Diffuse.g;
    PointLightModule.attr("PointLightDiffuseB") = PointLight->Diffuse.b;
    
    PointLightModule.attr("PointLightSpecularR") = PointLight->Specular.r;
    PointLightModule.attr("PointLightSpecularG") = PointLight->Specular.g;
    PointLightModule.attr("PointLightSpecularB") = PointLight->Specular.b;

    PointLightModule.attr("PointLightAmbientR") = PointLight->Ambient.r;
    PointLightModule.attr("PointLightAmbientG") = PointLight->Ambient.g;
    PointLightModule.attr("PointLightAmbientB") = PointLight->Ambient.b;
    
    PointLightModule.attr("PointLightRolloffConstant") = PointLight->RolloffConstant;
    PointLightModule.attr("PointLightRolloffLinear") = PointLight->RolloffLinear;
    PointLightModule.attr("PointLightRolloffQuadratic") = PointLight->RolloffQuadratic;
    

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
    double PointLightRotX, PointLightRotY, PointLightRotZ;
    double PointLightScaleX, PointLightScaleY, PointLightScaleZ;
    bool Successful = true;

    try {
        PointLightPosX = PointLightModule.attr("PointLightPosX").cast<double>();
        PointLightPosY = PointLightModule.attr("PointLightPosY").cast<double>();
        PointLightPosZ = PointLightModule.attr("PointLightPosZ").cast<double>();
        PointLight->SetPosition(glm::vec3(PointLightPosX, PointLightPosY, PointLightPosZ));
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("PointLight Position CAST_ERROR");
        Successful = false;
    }
    try {
        PointLightRotX = PointLightModule.attr("PointLightRotX").cast<double>();
        PointLightRotY = PointLightModule.attr("PointLightRotY").cast<double>();
        PointLightRotZ = PointLightModule.attr("PointLightRotZ").cast<double>();
        PointLight->SetRotation(glm::vec3(PointLightRotX, PointLightRotY, PointLightRotZ));
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("PointLight Rotation CAST_ERROR");
        Successful = false;
    }
    try {
        PointLightScaleX = PointLightModule.attr("PointLightScaleX").cast<double>();
        PointLightScaleY = PointLightModule.attr("PointLightScaleY").cast<double>();
        PointLightScaleZ = PointLightModule.attr("PointLightScaleZ").cast<double>();
        PointLight->SetScale(glm::vec3(PointLightScaleX, PointLightScaleY, PointLightScaleZ));
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("PointLight Scale CAST_ERROR");
        Successful = false;
    }

    try {
        PointLight->Enabled = PointLightModule.attr("PointLightEnabled").cast<bool>(); 
    } catch (pybind11::cast_error const&) {
        ErrorMessageString->push_back("PointLight Enable CAST_ERROR");
        Successful = false;
    }


    if (Successful) {
        PointLight->ApplyTransformations();
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

    //std::cout<<RunTime_<<std::endl;
    //Locals->attr("GameTime") = pybind11::cast<double>(RunTime_);

    Locals->attr("GameTime") = pybind11::float_(RunTime_);

    auto Clock = std::chrono::system_clock::now();
    double UnixEpoch = std::chrono::duration_cast<std::chrono::seconds>(Clock.time_since_epoch()).count();
    Locals->attr("SystemTime") = UnixEpoch;

}
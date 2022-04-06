//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_PythonInterpreterIntegration.h>


// yes this is bad i know, but idk how else to fix it
#include <PyBind11ModelClass.cpp>
#include <PyBind11SystemInfo.cpp>


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
                // make anther func to handle the PyException_ (all of them)
                ErrorHandle(ErrorMessageString, i, Exception.what());
                //ParsePythonErrors(ErrorMessageString, i, Exception);
            }

        }

    }

    // Write Back Model Data
    double ModelPosX = ModelModule.attr("ModelPosX").cast<double>();
    double ModelPosY = ModelModule.attr("ModelPosY").cast<double>();
    double ModelPosZ = ModelModule.attr("ModelPosZ").cast<double>();
    Model->SetPosition(glm::vec3(ModelPosX, ModelPosY, ModelPosZ));
    double ModelRotX = ModelModule.attr("ModelRotX").cast<double>();
    double ModelRotY = ModelModule.attr("ModelRotY").cast<double>();
    double ModelRotZ = ModelModule.attr("ModelRotZ").cast<double>();
    Model->SetRotation(glm::vec3(ModelRotX, ModelRotY, ModelRotZ));
    double ModelScaleX = ModelModule.attr("ModelScaleX").cast<double>();
    double ModelScaleY = ModelModule.attr("ModelScaleY").cast<double>();
    double ModelScaleZ = ModelModule.attr("ModelScaleZ").cast<double>();
    Model->SetScale(glm::vec3(ModelScaleX, ModelScaleY, ModelScaleZ));
    Model->ApplyTransformations();

    Model->Enabled = ModelModule.attr("ModelEnabled").cast<bool>();

    // Return Status
    if (ErrorMessageString->size() > 0) {
        return false;
    } else {
        return true;
    }

}



// void ERS_CLASS_PythonInterpreterIntegration::ParsePythonErrors(std::vector<std::string>* Target, unsigned long LineNumber, pybind11::error_already_set &Exception) {
    
//     std::cout<<Exception.what()<<std::endl;

// }

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
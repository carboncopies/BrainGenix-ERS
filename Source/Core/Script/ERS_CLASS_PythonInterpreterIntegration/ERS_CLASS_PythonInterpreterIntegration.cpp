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



bool ERS_CLASS_PythonInterpreterIntegration::ExecuteModelScript(std::string ScriptSource, ERS_STRUCT_Model* Model, std::string* ErrorMessageString) {


    // Inport The Model Module, Set Attributes
    pybind11::module ModelModule = pybind11::module_::import("Model");
    SetSystemInfoData(&ModelModule);

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


    pybind11::dict Locals = ModelModule.attr("__dict__");

    // For line by line errors, the source string could be split by lines, and then run sequentially. then the errors could be added to a vector and returned as an error list or something...

    try {
        pybind11::exec(ScriptSource, pybind11::globals(), Locals);
    } catch (pybind11::value_error) {
        ErrorHandle(ErrorMessageString, "Value Error");
        return false;
    } catch (pybind11::key_error) {
        ErrorHandle(ErrorMessageString, "Key Error");
        return false;
    } catch (pybind11::reference_cast_error) {
        ErrorHandle(ErrorMessageString, "Reference Cast Error");
        return false;
    } catch (pybind11::attribute_error) {
        ErrorHandle(ErrorMessageString, "Attribute Error");
        return false;
    } catch (pybind11::import_error) {
        ErrorHandle(ErrorMessageString, "Import Error");
        return false;
    } catch (pybind11::buffer_error) {
        ErrorHandle(ErrorMessageString, "Buffer Error");
        return false;
    } catch (pybind11::index_error) {
        ErrorHandle(ErrorMessageString, "Index Error");
        return false;
    } catch (pybind11::type_error) {
        ErrorHandle(ErrorMessageString, "Type Error");
        return false;
    } catch (pybind11::cast_error) {
        ErrorHandle(ErrorMessageString, "Cast Error");
        return false;
    }








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


    return true;

}

bool ExecutePointLightScript(std::string ScriptSource, ERS_STRUCT_PointLight* Model) {

}


void ERS_CLASS_PythonInterpreterIntegration::ErrorHandle(std::string* Target, std::string Value) {

    if (Target != nullptr) {
        Target = &Value;
    }

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
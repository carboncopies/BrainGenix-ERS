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






void ERS_CLASS_PythonInterpreterIntegration::ExecuteCode(std::string Code) {


    pybind11::module module = pybind11::module_::import("Model");
    module.attr("foo2") = Code;
    pybind11::dict locals = module.attr("__dict__");

    pybind11::exec(R"(
        print(foo2)
    )", pybind11::globals(), locals);


    //std::cout<<locals["b"].cast<int>()<<"\n";


}


bool ERS_CLASS_PythonInterpreterIntegration::ExecuteModelScript(std::string ScriptSource, ERS_STRUCT_Model* Model) {


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
    pybind11::exec(ScriptSource, pybind11::globals(), Locals);

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
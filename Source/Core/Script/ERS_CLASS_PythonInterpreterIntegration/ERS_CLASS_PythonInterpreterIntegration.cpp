//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_PythonInterpreterIntegration.h>



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


int ERS_CLASS_PythonInterpreterIntegration::foo() {
    return 42;
}


int foo2() {
    return 84;
}


void ERS_CLASS_PythonInterpreterIntegration::ExecuteCode(std::string Code) {

    pybind11::module module;
    module.def("test", foo2);

    auto locals = pybind11::dict("fmt"_a="{} + {} = {}", **module.attr("__dict__"));

}
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



    pybind11::dict locals = module.attr("__dict__");
    assert(locals["a"].cast<int>() == 1);
    assert(locals["b"].cast<int>() == 2);

    pybind11::exec(R"(
        b = test()
        print(b)
    )", pybind11::globals(), locals);

    assert(locals["c"].cast<int>() == 3);
    assert(locals["message"].cast<std::string>() == "1 + 2 = 3");


}
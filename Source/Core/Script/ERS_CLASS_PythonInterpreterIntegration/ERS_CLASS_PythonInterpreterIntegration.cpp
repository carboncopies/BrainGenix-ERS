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

PYBIND11_EMBEDDED_MODULE(test, m) {
    m.doc() = "test module";

    m.attr("foo") = std::string("A value.");

    m.def("testfunc", &foo2, "test function");
}





void ERS_CLASS_PythonInterpreterIntegration::ExecuteCode(std::string Code) {


    pybind11::module module = pybind11::module_::import("test");
    module.attr("foo2") = Code;
    pybind11::dict locals = module.attr("__dict__");

    pybind11::exec(R"(
        b = testfunc()
        print(b)
        print(foo)
        prnt(foo2)
    )", pybind11::globals(), locals);


    std::cout<<locals["b"].cast<int>()<<"\n";


}
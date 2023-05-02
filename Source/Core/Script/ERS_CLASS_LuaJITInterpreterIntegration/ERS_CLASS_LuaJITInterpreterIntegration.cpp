//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_LuaJITnterpreterIntegration.h>



ERS_CLASS_LuaJITInterpreterIntegration::ERS_CLASS_LuaJITInterpreterIntegration(ERS_LoggingSystem* Logger) {

    Logger_ = Logger;

    Logger_->Log("Initializing LuaJIT Interpreter Subsystem", 5);


    // Start LuaJIT Interpreter
    Logger_->Log("Starting LuaJIT Interpreter", 5);
    Guard_ = std::make_unique<LuaJIT::scoped_interpreter>();
    Logger_->Log("Finished Starting LuaJIT Interpreter", 4);
    
}

ERS_CLASS_LuaJITInterpreterIntegration::~ERS_CLASS_LuaJITInterpreterIntegration() {

    Logger_->Log("Shutting Down LuaJIT Interpreter Subsystem", 6);

}

void ERS_CLASS_LuaJITInterpreterIntegration::Test_Script()
{

	std::cout << "This is a demo how LuaCpp can be used" << "\n";
	LuaContext lua;

	// The simples way is to use CompileStringAndRun method
	try {
		lua.CompileStringAndRun("print('The fastest way to start using lua in a project')");
	}
	catch (std::runtime_error& e)
  	{
		std::cout << e.what() << '\n';
  	}

}
      
 


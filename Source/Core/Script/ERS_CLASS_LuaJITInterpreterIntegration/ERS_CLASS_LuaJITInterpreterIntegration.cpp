//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_LuaJITInterpreterIntegration.h>

ERS_CLASS_LuaJITInterpreterIntegration::ERS_CLASS_LuaJITInterpreterIntegration(ERS_LoggingSystem* Logger)
{
	Logger_ = Logger;

    Logger_->Log("Initializing LuaJIT Interpreter Subsystem", 5);
   // Start LuaJIT Interpreter

	// Create a new Lua state
    L = luaL_newstate();

    // Load the Lua standard library
    luaL_openlibs(L);
  
}

ERS_CLASS_LuaJITInterpreterIntegration::~ERS_CLASS_LuaJITInterpreterIntegration() {

    lua_close(L);
    Logger_->Log("Shutting Down JuaJIT Interpreter Subsystem", 6);
}

void ERS_CLASS_LuaJITInterpreterIntegration::Test_Script()
{
	
	
    // Load and run a Lua script
    int result = luaL_dostring(L, "print('Hello from LuaJIT!')");

    // Check for errors
    if (result != LUA_OK) {
        const char* error = lua_tostring(L, -1);
        std::cerr << "Lua error: " << error << std::endl;
        lua_pop(L, 1); // Pop the error message off the stack
    }
	

}
      
 


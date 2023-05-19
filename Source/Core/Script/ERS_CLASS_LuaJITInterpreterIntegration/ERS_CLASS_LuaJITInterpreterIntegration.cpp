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


void ERS_CLASS_LuaJITInterpreterIntegration::ErrorHandle(std::vector<std::string>* Target, unsigned long LineNumber, std::string Error) {

    std::string ErrorMessage = std::string("Error On Line '") + std::to_string(LineNumber) + std::string("': ") + Error + std::string("\n");
    Target->push_back(ErrorMessage);


}

void ERS_CLASS_LuaJITInterpreterIntegration::UpdateSystemInfoData(double RunTime) {

    RunTime_ = RunTime;

}

bool ERS_CLASS_LuaJITInterpreterIntegration::ExecuteSceneCameraScript(std::string ScriptSource, ERS_STRUCT_SceneCamera* Camera, std::vector<std::string>* ErrorMessageString) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);


    // Set system parameters
    lua_pushnumber(L, Camera->Pos_.x);
    lua_setglobal(L, "PosX");
    lua_pushnumber(L, Camera->Pos_.y);
    lua_setglobal(L, "PosY");
    lua_pushnumber(L, Camera->Pos_.z);
    lua_setglobal(L, "PosZ");
    lua_pushnumber(L, Camera->Rot_.x);
    lua_setglobal(L, "RotX");
    lua_pushnumber(L, Camera->Rot_.y);
    lua_setglobal(L, "RotY");
    lua_pushnumber(L, Camera->Rot_.z);
    lua_setglobal(L, "RotZ");
    lua_pushnumber(L, Camera->FOV_);
    lua_setglobal(L, "FOV");
    lua_pushnumber(L, Camera->StreamingPriority_);
    lua_setglobal(L, "Priority");

    // Load the Lua script
    if (luaL_dostring(L, ScriptSource.c_str()) != LUA_OK) {
        const char* errorMessage = lua_tostring(L, -1);
        if (ErrorMessageString != nullptr) {
            ErrorMessageString->push_back(errorMessage);
        }
        lua_close(L);
        return false;
    }

    // Write back camera data
    lua_getglobal(L, "PosX");
    Camera->Pos_.x = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "PosY");
    Camera->Pos_.y = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "PosZ");
    Camera->Pos_.z = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "RotX");
    Camera->Rot_.x = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "RotY");
    Camera->Rot_.y = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "RotZ");
    Camera->Rot_.z = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "FOV");
    Camera->FOV_ = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "Priority");

    lua_close(L);
    return true;
}

 


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


bool ERS_CLASS_LuaJITInterpreterIntegration::ExecuteSceneCameraScript(std::string ScriptSource, ERS_STRUCT_SceneCamera* Camera, std::vector<std::string>* ErrorMessageString) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    SetSystemInfoData(L);

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
    Camera->StreamingPriority_ = (float)lua_tonumber(L, -1);

    lua_close(L);
    return true;
}

 bool ERS_CLASS_LuaJITInterpreterIntegration::ExecuteModelScript(std::string ScriptSource, ERS_STRUCT_Model* Model, std::vector<std::string>* ErrorMessageString) {

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    SetSystemInfoData(L);

    // Set system parameters
    lua_pushnumber(L, Model->ModelPosition.x);
    lua_setglobal(L, "PosX");
    lua_pushnumber(L, Model->ModelPosition.y);
    lua_setglobal(L, "PosY");
    lua_pushnumber(L, Model->ModelPosition.z);
    lua_setglobal(L, "PosZ");
    lua_pushnumber(L, Model->ModelRotation.x);
    lua_setglobal(L, "RotX");
    lua_pushnumber(L, Model->ModelRotation.y);
    lua_setglobal(L, "RotY");
    lua_pushnumber(L, Model->ModelRotation.z);
    lua_setglobal(L, "RotZ");
    lua_pushnumber(L,Model->ModelScale.x);
    lua_setglobal(L,"ScaleX");
    lua_pushnumber(L,Model->ModelScale.y);
    lua_setglobal(L,"ScaleY");
    lua_pushnumber(L,Model->ModelScale.z);
    lua_setglobal(L,"ScaleZ");
    lua_pushnumber(L, Model->Enabled);
    lua_setglobal(L,"Enabled");


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
    Model->ModelPosition.x = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "PosY");
    Model->ModelPosition.y = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "PosZ");
    Model->ModelPosition.z = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "RotX");
    Model->ModelRotation.x = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "RotY");
    Model->ModelRotation.y = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "RotZ");
    Model->ModelRotation.z = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "Enabled");
    Model->Enabled= (float)lua_tonumber(L, -1);

    lua_close(L);
    return true;
 

}

bool ERS_CLASS_LuaJITInterpreterIntegration::ExecutePointLightScript(std::string ScriptSource, ERS_STRUCT_PointLight* PointLight, std::vector<std::string>* ErrorMessageString) {
lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    SetSystemInfoData(L);

    // Set system parameters
    lua_pushnumber(L, PointLight->Pos.x);
    lua_setglobal(L, "PosX");
    lua_pushnumber(L, PointLight->Pos.y);
    lua_setglobal(L, "PosY");
    lua_pushnumber(L, PointLight->Pos.z);
    lua_setglobal(L, "PosZ");
    lua_pushnumber(L, PointLight->Color.r);
    lua_setglobal(L, "ColorR");
    lua_pushnumber(L, PointLight->Color.g);
    lua_setglobal(L, "ColorG");
    lua_pushnumber(L, PointLight->Color.b);
    lua_setglobal(L, "ColoarB");
    lua_pushnumber(L, PointLight->Intensity);
    lua_setglobal(L, "Intensity");
    lua_pushnumber(L, PointLight->MaxDistance);
    lua_setglobal(L, "MaxDistance");

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
    PointLight->Pos.x = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "PosY");
    PointLight->Pos.y= (float)lua_tonumber(L, -1);
    lua_getglobal(L, "PosZ");
    PointLight->Pos.z = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "ColorR");
    PointLight->Color.r = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "ColorG");
    PointLight->Color.g = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "ColorB");
    PointLight->Color.b = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "Intensity");
    PointLight->Intensity = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "MaxDistance");
    PointLight->MaxDistance = (float)lua_tonumber(L, -1);

    lua_close(L);
    return true;


}

bool ERS_CLASS_LuaJITInterpreterIntegration::ExecuteDirectionalLightScript(std::string ScriptSource, ERS_STRUCT_DirectionalLight* DirectionalLight, std::vector<std::string>* ErrorMessageString) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    SetSystemInfoData(L);

    // Set system parameters
    lua_pushnumber(L, DirectionalLight->Pos.x);
    lua_setglobal(L, "PosX");
    lua_pushnumber(L, DirectionalLight->Pos.y);
    lua_setglobal(L, "PosY");
    lua_pushnumber(L, DirectionalLight->Pos.z);
    lua_setglobal(L, "PosZ");
    lua_pushnumber(L, DirectionalLight->Rot.x);
    lua_setglobal(L, "RotX");
    lua_pushnumber(L, DirectionalLight->Rot.y);
    lua_setglobal(L, "RotY");
    lua_pushnumber(L, DirectionalLight->Rot.z);
    lua_setglobal(L, "RotZ");
    lua_pushnumber(L, DirectionalLight->Color.r);
    lua_setglobal(L, "ColorR");
    lua_pushnumber(L, DirectionalLight->Color.g);
    lua_setglobal(L, "ColorG");
    lua_pushnumber(L, DirectionalLight->Color.b);
    lua_setglobal(L, "ColoarB");
    lua_pushnumber(L, DirectionalLight->Intensity);
    lua_setglobal(L, "Intensity");
    lua_pushnumber(L, DirectionalLight->MaxDistance);
    lua_setglobal(L, "MaxDistance");

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
    DirectionalLight->Pos.x = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "PosY");
    DirectionalLight->Pos.y= (float)lua_tonumber(L, -1);
    lua_getglobal(L, "PosZ");
    DirectionalLight->Pos.z = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "RotX");
    DirectionalLight->Rot.x = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "RotY");
    DirectionalLight->Rot.y = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "RotZ");
    DirectionalLight->Rot.z = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "ColorR");
    DirectionalLight->Color.r = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "ColorG");
    DirectionalLight->Color.g = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "ColorB");
    DirectionalLight->Color.b = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "Intensity");
    DirectionalLight->Intensity = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "MaxDistance");
    DirectionalLight->MaxDistance = (float)lua_tonumber(L, -1);

    lua_close(L);
    return true;


}

bool ERS_CLASS_LuaJITInterpreterIntegration::ExecuteSpotLightScript(std::string ScriptSource, ERS_STRUCT_SpotLight* SpotLight, std::vector<std::string>* ErrorMessageString) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    SetSystemInfoData(L);

    // Set system parameters
    lua_pushnumber(L, SpotLight->Pos.x);
    lua_setglobal(L, "PosX");
    lua_pushnumber(L, SpotLight->Pos.y);
    lua_setglobal(L, "PosY");
    lua_pushnumber(L, SpotLight->Pos.z);
    lua_setglobal(L, "PosZ");
    lua_pushnumber(L, SpotLight->Rot.x);
    lua_setglobal(L, "RotX");
    lua_pushnumber(L, SpotLight->Rot.y);
    lua_setglobal(L, "RotY");
    lua_pushnumber(L, SpotLight->Rot.z);
    lua_setglobal(L, "RotZ");
    lua_pushnumber(L, SpotLight->Color.r);
    lua_setglobal(L, "ColorR");
    lua_pushnumber(L, SpotLight->Color.g);
    lua_setglobal(L, "ColorG");
    lua_pushnumber(L, SpotLight->Color.b);
    lua_setglobal(L, "ColoarB");
    lua_pushnumber(L, SpotLight->Intensity);
    lua_setglobal(L, "Intensity");
    lua_pushnumber(L, SpotLight->MaxDistance);
    lua_setglobal(L, "MaxDistance");
    lua_pushnumber(L, SpotLight->CutOff);
    lua_setglobal(L, "CutOff");
    lua_pushnumber(L, SpotLight->Rolloff);
    lua_setglobal(L, "Rolloff");
    
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
    SpotLight->Pos.x = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "PosY");
    SpotLight->Pos.y= (float)lua_tonumber(L, -1);
    lua_getglobal(L, "PosZ");
    SpotLight->Pos.z = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "RotX");
    SpotLight->Rot.x = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "RotY");
    SpotLight->Rot.y = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "RotZ");
    SpotLight->Rot.z = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "ColorR");
    SpotLight->Color.r = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "ColorG");
    SpotLight->Color.g = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "ColorB");
    SpotLight->Color.b = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "Intensity");
    SpotLight->Intensity = (float)lua_tonumber(L, -1);
    lua_getglobal(L, "MaxDistance");
    SpotLight->MaxDistance = (float)lua_tonumber(L, -1);
       lua_getglobal(L, "CutOff");
    SpotLight->CutOff = (float)lua_tonumber(L, -1);
       lua_getglobal(L, "Rolloff");
    SpotLight->Rolloff = (float)lua_tonumber(L, -1);

    lua_close(L);
    return true;

}

void ERS_CLASS_LuaJITInterpreterIntegration::UpdateSystemInfoData(double RunTime) {

    RunTime_ = RunTime;

}


void ERS_CLASS_LuaJITInterpreterIntegration::SetSystemInfoData(lua_State* L) {
  
  // Set Game Time
  
    lua_pushnumber(L, RunTime_);
    lua_setglobal(L, "GameTime");

  // Get System Time
    auto Clock = std::chrono::system_clock::now();
    double UnixEpoch = std::chrono::duration_cast<std::chrono::seconds>(Clock.time_since_epoch()).count();

  // Set System Time
    lua_pushnumber(L, UnixEpoch);
    lua_setglobal(L, "SystemTime");
}

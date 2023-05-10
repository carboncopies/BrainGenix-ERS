//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the main file of the system.
    Additional Notes: None
    Date Created: 2021-11-01
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_GPURequest.h>
#include <RendererManager.h>

#include <ERS_LoggingSystem.h>
#include <ERS_LogSystemInfo.h>
#include <ERS_HardwareInformation.h>
#include <ERS_ArgumentParser.h>
#include <ERS_ModelImporter.h>
#include <ERS_LocalConfigLoader.h>


#include <ERS_SceneManager.h>

#include <ERS_InputOutputSubsystem.h>
#include <ERS_FramerateManager.h>
#include <ERS_ProjectLoader.h>
#include <ERS_ProjectManager.h>
#include <ERS_ProjectWriter.h>
#include <ERS_ControllerInputManager.h>

#include <ERS_STRUCT_HumanInputDeviceUtils.h>
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_ProjectUtils.h>
#include <ERS_STRUCT_RendererSettings.h>

#include <ERS_CLASS_PythonInterpreterIntegration.h>
#include <ERS_CLASS_LuaJITInterpreterIntegration.h>

#include <ERS_GetExecutablePath.h>


/**
 * Main system function.
*/
int main(int NumArguments, char** ArguemntValues);

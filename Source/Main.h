//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <LuciferIL/Lucifer_IncludeOnce.h>
#include <LuciferIL/Lucifer.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <GPURequest.h>
#include <RendererManager.h>

#include <LoggingSystem.h>
#include <LogSystemInfo.h>
#include <HardwareInformation.h>
#include <ArgumentParser.h>
#include <ModelImporter.h>
#include <LocalConfigLoader.h>

#include <SceneManager.h>

#include <InputOutputSubsystem.h>
#include <FramerateManager.h>
#include <ProjectLoader.h>
#include <ProjectManager.h>
#include <ProjectWriter.h>
#include <ControllerInputManager.h>

#include <HumanInputDeviceUtils.h>
#include <SystemUtils.h>
#include <ProjectUtils.h>
#include <RendererSettings.h>

#include <GetExecutablePath.h>



/**
 * Main funtion for system
*/
int main(int NumArguments, char** ArguemntValues);
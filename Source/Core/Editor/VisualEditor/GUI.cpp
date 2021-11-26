//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing the gui.
    Additonal Notes: None
    Date Created: 2021-01-25
*/

#include <GUI.h>

GUISystem::GUISystem(LoggerClass* Logger) {

    // Bootstrap CEGUI::System with an OpenGL3Renderer object that uses the
    // current GL viewport, the DefaultResourceProvider, and the default
    // ImageCodec.
    //
    // NB: Your OpenGL context must already be initialised when you call this; CEGUI
    // will not create the OpenGL context itself. Nothing special has to be done to
    // choose between desktop OpenGL and OpenGL ES: the type is automatically
    // determined by the type of the current OpenGL context.
    CEGUI::OpenGL3Renderer& myRenderer = CEGUI::OpenGL3Renderer::bootstrapSystem();


}
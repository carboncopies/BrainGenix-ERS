//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <PyBind11SceneCameraClass.h>



PYBIND11_EMBEDDED_MODULE(Camera, m) {
    m.doc() = "Allows the script to manipulate the Scene Camera that it's attached to.";
}
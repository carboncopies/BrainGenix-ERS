//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <PyBind11PointLightClass.h>


PYBIND11_EMBEDDED_MODULE(Camera, m) {
    m.doc() = "Allows the script to manipulate the Scene Camera that it's attached to.";
}


PYBIND11_EMBEDDED_MODULE(PointLight, m) {
    m.doc() = "Allows the script to manipulate the point light that it's attached to.";
}
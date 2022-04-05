//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <PyBind11ModelClass.h>



PYBIND11_EMBEDDED_MODULE(SystemInfo, m) {
    m.doc() = "Provides access to basic system information.";
}
########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_PythonInterpreterIntegration 

            # Add Source Files (.cpp)
            "ERS_CLASS_PythonInterpreterIntegration.cpp"
            "PyBind11ModelClass.cpp"
            "PyBind11SystemInfo.cpp"

            # Add Header Files (.h)
            "ERS_CLASS_PythonInterpreterIntegration.h"
            "PyBind11ModelClass.h"
            "PyBind11SystemInfo.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_CLASS_PythonInterpreterIntegration
    pybind11::embed
    )

# Link Internal Libs
target_link_libraries(ERS_CLASS_PythonInterpreterIntegration
    ERS_CLASS_LoggingSystem

    ERS_STRUCT_Model
    ERS_STRUCT_Light

    )

set_target_properties(ERS_CLASS_PythonInterpreterIntegration
    PROPERTIES
    CXX_VISIBILITY_PRESET
    hidden
)
set_target_properties(pybind11::embed
    PROPERTIES
    CXX_VISIBILITY_PRESET
    hidden
)

target_include_directories(ERS_CLASS_PythonInterpreterIntegration PUBLIC ./)
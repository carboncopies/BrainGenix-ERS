########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_PythonInterpreterIntegration 

            # Add Source Files (.cpp)
            "ERS_CLASS_PythonInterpreterIntegration.cpp"

            # Add Header Files (.h)
            "ERS_CLASS_PythonInterpreterIntegration.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_CLASS_PythonInterpreterIntegration
    pybind11::embed
    )

# Link Internal Libs
target_link_libraries(ERS_CLASS_PythonInterpreterIntegration
    ERS_CLASS_LoggingSystem
    )

target_include_directories(ERS_CLASS_PythonInterpreterIntegration PUBLIC ./)
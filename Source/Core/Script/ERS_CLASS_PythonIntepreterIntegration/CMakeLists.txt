########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_PythonIntepreterIntegration 

            # Add Source Files (.cpp)
            "ERS_CLASS_PythonIntepreterIntegration.cpp"

            # Add Header Files (.h)
            "ERS_CLASS_PythonIntepreterIntegration.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_CLASS_PythonIntepreterIntegration
    pybind11::embed
    )

# Link Internal Libs
target_link_libraries(ERS_CLASS_PythonIntepreterIntegration
    )

target_include_directories(ERS_CLASS_PythonIntepreterIntegration PUBLIC ./)
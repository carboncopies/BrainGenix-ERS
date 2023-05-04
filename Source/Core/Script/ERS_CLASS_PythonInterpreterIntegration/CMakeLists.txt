########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_PythonInterpreterIntegration 

            # Add Source Files (.cpp)
            "PythonInterpreterIntegration.cpp"
            "PyBind11ModelClass.cpp"
            "PyBind11SystemInfo.cpp"
            "PyBind11PointLightClass.cpp"
            "PyBind11DirectionalLightClass.cpp"
            "PyBind11SpotLightClass.cpp"
            "PyBind11SceneCameraClass.cpp"
            

            # Add Header Files (.h)
            "PythonInterpreterIntegration.h"
            "PyBind11ModelClass.h"
            "PyBind11SystemInfo.h"
            "PyBind11PointLightClass.h"
            "PyBind11DirectionalLightClass.h"
            "PyBind11SpotLightClass.h"
            "PyBind11SceneCameraClass.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
#target_link_libraries(ERS_CLASS_PythonInterpreterIntegration
 #   pybind11::embed
  #  )

# Link Internal Libs
target_link_libraries(ERS_CLASS_PythonInterpreterIntegration
    ERS_LoggingSystem

    ERS_STRUCT_Model
    ERS_STRUCT_Light
    ERS_STRUCT_SceneCamera

    
    )

target_include_directories(ERS_CLASS_PythonInterpreterIntegration PUBLIC ./)

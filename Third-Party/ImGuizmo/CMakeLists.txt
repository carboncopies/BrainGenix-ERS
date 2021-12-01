# Get Source Files
file(GLOB CPPFiles *.cpp)
file(GLOB HeaderFiles *.h)


# Create Library (Name Should Be Parent Dir Name)
add_library(ImGuizmo

            # Add Source Files (.cpp)
            CPPFiles

            # Add Header Files (.h)
            HeaderFiles
                
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(3DCursor

    IMGUI
    )


target_include_directories(3DCursor PUBLIC ./)
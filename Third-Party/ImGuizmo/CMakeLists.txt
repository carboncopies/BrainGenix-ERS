# Create Library (Name Should Be Parent Dir Name)
add_library(ImGuizmo

            # Add Source Files (.cpp)
            CPPFiles

            # Add Header Files (.h)
            HeaderFiles
                
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ImGuizmo

    IMGUI
    )


target_include_directories(ImGuizmo PUBLIC ./)
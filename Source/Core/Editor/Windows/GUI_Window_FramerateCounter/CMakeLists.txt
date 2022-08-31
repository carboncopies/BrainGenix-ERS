# Create Library (Name Should Be Parent Dir Name)
add_library(GUI_Window_FramerateCounter

            "GUI_Window_FramerateCounter.cpp"
            "GUI_Window_FramerateCounter.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(GUI_Window_FramerateCounter PRIVATE
    IMGUI
    )

# Link Internal Libs
target_link_libraries(GUI_Window_FramerateCounter PRIVATE
    )

target_include_directories(GUI_Window_FramerateCounter PUBLIC ./)
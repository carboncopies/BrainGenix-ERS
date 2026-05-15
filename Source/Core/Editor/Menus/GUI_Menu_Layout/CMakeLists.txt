########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


add_library(Menu_Layout
            "GUI_Menu_Layout.cpp"
            "GUI_Menu_Layout.h"
            ${BACKWARD_ENABLE}
            )
set_property(TARGET Menu_Layout PROPERTY CXX_STANDARD 17)

target_link_libraries(Menu_Layout
    IMGUI
    )

target_link_libraries(Menu_Layout
    bg-common-logger
    ERS_STRUCT_SystemUtils
    ERS_Editor_LayoutManager
    )

target_include_directories(Menu_Layout PUBLIC ./)

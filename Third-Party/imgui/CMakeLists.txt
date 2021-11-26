# ImGui
add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD=1)

# Set where the ImGui files are stored
set(IMGUI_PATH  ".")
    
# Compile as static library 
file(GLOB IMGUI_ROOT_SOURCES ${IMGUI_PATH}/*.cpp)
file(GLOB IMGUI_ROOT_Headers ${IMGUI_PATH}/*.h)

set(IMGUI_BACKEND_SOURCES

    "backends/imgui_impl_glfw.cpp"
    "backends/imgui_impl_opengl3.cpp"

)

set(IMGUI_BACKEND_HEADERS

    "backends/imgui_impl_glfw.h"
    "backends/imgui_impl_opengl3.h"

)

# Link Files Into Lib
add_library("ImGui" STATIC 

    ${IMGUI_ROOT_SOURCES}
    ${IMGUI_ROOT_HEADERS}

    ${IMGUI_BACKEND_SOURCES}
    ${IMGUI_BACKEND_HEADERS}

)
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})
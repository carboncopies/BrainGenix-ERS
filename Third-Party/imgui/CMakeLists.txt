# ImGui
add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD=1)

# Set where the ImGui files are stored
set(IMGUI_PATH  ".")
    
# Compile as static library 
file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp) 
add_library("ImGui" STATIC ${IMGUI_SOURCES})
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})
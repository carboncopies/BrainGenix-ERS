
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_INSTALL_PREFIX ${BIN_DIR})

# function(disable_target_warnings target)
#   target_compile_options(${target} PRIVATE
#     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
#       -w>
#     $<$<CXX_COMPILER_ID:MSVC>:
#       /w>
#     )
# endfunction()

# # Add FreeImage Library (Not Header Only)
# add_subdirectory(${LIB_DIR}/FreeImage/FreeImage)
# disable_target_warnings(FreeImage)

# find_package(FreeImage REQUIRED)
# include_directories(${FreeImage_INCLUDE})

option(FreeImage_INCLUDE "Set the internal superbuild include path for freeimage (wherever header files are located)" "")
message("********************* ARGTEST ${FreeImage_INCLUDE}")

# Add Main.cpp
add_executable(${PROJECT_NAME} "${SRC_DIR}/Main.cpp" ${BACKWARD_ENABLE})
target_include_directories(${PROJECT_NAME} PRIVATE Source)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
target_link_libraries(${PROJECT_NAME} PRIVATE
  FreeImage
  )

# Copy Images
file(COPY "${SRC_DIR}/Assets/" DESTINATION "${BIN_DIR}/Assets")

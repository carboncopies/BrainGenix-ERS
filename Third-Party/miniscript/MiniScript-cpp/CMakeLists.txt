# Modified For ERS, Miniscript Does Not Use CMake By Default

# Set Script Vars
set(MINISCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR})


# Create Lib, Add Sources
add_library(Miniscript)
target_sources(Miniscript PRIVATE
    ${MINISCRIPT_DIR}/src/
    ${MINISCRIPT_DIR}/src/Miniscript/
    ${MINISCRIPT_DIR}/src/editline/
)

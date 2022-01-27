# Set Script Vars
message("-- Getting Miniscript Source Directory")
set(MINISCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR})


# Create Lib, Add Sources
message("-- Creating Miniscript Library")
add_library(Miniscript)

message("-- Adding Targets To Library")
set_target_properties(Miniscript PROPERTIES LINKER_LANGUAGE CXX)
target_sources(Miniscript PRIVATE
    ${MINISCRIPT_DIR}/src/
    ${MINISCRIPT_DIR}/src/Miniscript/
    ${MINISCRIPT_DIR}/src/editline/
)
message("-- Finished Configuring Miniscript")
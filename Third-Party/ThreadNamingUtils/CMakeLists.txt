cmake_minimum_required(VERSION 3.5)
project(ThreadNamingUtils)

set(LIB_SOURCE_FILES 
    "ThreadNamingUtils/SetThreadName.cpp"
    "ThreadNamingUtils/GetThreadName.cpp"
)

set(LIB_HEADER_FILES 
    "ThreadNamingUtils/SetThreadName.h"
    "ThreadNamingUtils/GetThreadName.h"
)

add_library(ThreadNamingUtils

    "ThreadNamingUtils/SetThreadName.cpp"
    "ThreadNamingUtils/GetThreadName.cpp"
    
    "ThreadNamingUtils/SetThreadName.h"
    "ThreadNamingUtils/GetThreadName.h"

)

target_include_directories(ThreadNamingUtils
    PUBLIC
        ${PROJECT_SOURCE_DIR}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/ThreadNamingUtils
)
set_target_properties(ThreadNamingUtils PROPERTIES PUBLIC_HEADER ${HEADERS})
install(TARGETS ThreadNamingUtils PUBLIC_HEADER)
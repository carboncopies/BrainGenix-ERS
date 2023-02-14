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

    ${LIB_SOURCE_FILES}
    ${LIB_HEADER_FILES}

)

target_include_directories(ThreadNamingUtils
    PUBLIC
        ${PROJECT_SOURCE_DIR}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/ThreadNamingUtils
)
set_target_properties(ThreadNamingUtils PROPERTIES PUBLIC_HEADER ${LIB_HEADER_FILES})
install(TARGETS ThreadNamingUtils PUBLIC_HEADER)
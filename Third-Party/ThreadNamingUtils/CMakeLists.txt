cmake_minimum_required(VERSION 3.5)
project(ThreadNamingUtils)

add_library(ThreadNamingUtils
    "ThreadNamingUtils/SetThreadName.cpp"
    "ThreadNamingUtils/GetThreadName.cpp"
)

target_include_directories(ThreadNamingUtils
    PUBLIC
        ${PROJECT_SOURCE_DIR}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/ThreadNamingUtils
)


set_target_properties(ThreadNamingUtils PROPERTIES PUBLIC_HEADER "ThreadNamingUtils/SetThreadName.h;ThreadNamingUtils/GetThreadName.h")
install(TARGETS ThreadNamingUtils PUBLIC_HEADER)
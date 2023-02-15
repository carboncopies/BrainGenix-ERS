find_package (Threads REQUIRED)

add_executable (blah
  main.cpp)

target_link_libraries (blah
  LuaJIT
  ${CMAKE_THREAD_LIBS_INIT})

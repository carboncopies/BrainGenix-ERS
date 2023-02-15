find_package (Threads REQUIRED)

add_executable (blah
  main.cpp)

target_link_libraries (blah
  LuaJIT
  ${CMAKE_THREAD_LIBS_INIT})



file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/test.lua" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/blah/bin/")
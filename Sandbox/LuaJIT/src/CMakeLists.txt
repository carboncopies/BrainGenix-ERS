find_package (Threads REQUIRED)

add_executable (blah
  main.cpp)

target_link_libraries (blah
  LuaJIT
  ${CMAKE_THREAD_LIBS_INIT})

message(STATUS "Copying File '${CMAKE_CURRENT_SOURCE_DIR}/test.lua' To '${CMAKE_CURRENT_BINARY_DIR}/blah/bin'")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/test.lua" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/blah/bin")
message(STATUS "Copying File '${CMAKE_CURRENT_SOURCE_DIR}/Run.sh' To '${CMAKE_CURRENT_BINARY_DIR}/blah/bin'")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Run.sh" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/blah/bin")

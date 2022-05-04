project(glad)

add_library(glad
  include/glad/gl.h
  include/KHR/khrplatform.h
  src/gl.c
  )
target_include_directories(glad PUBLIC include)

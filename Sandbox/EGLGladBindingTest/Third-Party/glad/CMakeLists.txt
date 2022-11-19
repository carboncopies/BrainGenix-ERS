project(glad)

add_library(glad
  include/glad/egl.h
  include/glad/gl.h
  include/EGL/eglplatform.h
  include/KHR/khrplatform.h
  
  src/gl.c
  src/egl.c
  )

target_include_directories(glad PUBLIC include)

project(glad)

add_library(glad
  include/glad/glad.h
  include/glad/egl.h
  include/glad/gl.h
  include/EGL/eglplatform.h
  include/KHR/khrplatform.h
  src/glad.c
  src/egl.c
  )
target_include_directories(glad PUBLIC include)

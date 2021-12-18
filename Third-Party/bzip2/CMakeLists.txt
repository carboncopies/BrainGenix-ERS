# Copied from minizip cmakelists!

set(BZIP2_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}) # set current dir as the bzip src dir


# BZip2 repository does not support cmake so we have to create
# the bzip2 library ourselves
set(BZIP2_SRC
    ${BZIP2_SOURCE_DIR}/blocksort.c
    ${BZIP2_SOURCE_DIR}/bzlib.c
    ${BZIP2_SOURCE_DIR}/compress.c
    ${BZIP2_SOURCE_DIR}/crctable.c
    ${BZIP2_SOURCE_DIR}/decompress.c
    ${BZIP2_SOURCE_DIR}/huffman.c
    ${BZIP2_SOURCE_DIR}/randtable.c)

set(BZIP2_HDR
    ${BZIP2_SOURCE_DIR}/bzlib.h
    ${BZIP2_SOURCE_DIR}/bzlib_private.h)

add_library(bzip2 STATIC ${BZIP2_SRC} ${BZIP2_HDR})

target_compile_definitions(bzip2 PRIVATE -DBZ_NO_STDIO)

list(APPEND MINIZIP_DEP bzip2)
list(APPEND MINIZIP_INC ${BZIP2_SOURCE_DIR})
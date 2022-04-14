cmake_minimum_required(VERSION 2.6)

cmake_policy(SET CMP0048 NEW)
project(
    ImageLib
    VERSION "1.8.0"
    )



add_subdirectory(src-IL)
add_subdirectory(src-ILU)
add_subdirectory(src-ILUT)


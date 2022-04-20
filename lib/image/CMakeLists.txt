file(GLOB_RECURSE CFILES "${CMAKE_SOURCE_DIR}/*.c")
SET_SOURCE_FILES_PROPERTIES(${CFILES} PROPERTIES LANGUAGE CXX)

add_library(
    image
    image.h
    image.c
)

target_include_directories(image PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)")
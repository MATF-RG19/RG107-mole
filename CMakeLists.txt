cmake_minimum_required(VERSION 3.16)
project(MoleGame VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter")

file(GLOB_RECURSE CFILES "${CMAKE_SOURCE_DIR}/*.c")
SET_SOURCE_FILES_PROPERTIES(${CFILES} PROPERTIES LANGUAGE CXX)

add_library(
    image
    image.h
    image.c
)

add_library(
    mole
    mole.hpp
    mole.cpp
)

add_library(
    sargarepa
    sargarepa.hpp
    sargarepa.cpp
)

add_library(
    rotkvica
    rotkvica.hpp
    rotkvica.cpp
)

add_library(
    pecurka
    pecurka.hpp
    pecurka.cpp
)

add_library(
    coveculjak
    coveculjak.hpp
    coveculjak.cpp
)

add_library(
    iscrtavanja
    iscrtavanja.hpp
    iscrtavanja.cpp
)

add_library(
    igra
    igra.hpp
    igra.cpp
)

add_executable(main.out main.cpp)

# Deo vezan za OpenGL --------------------------------------------------
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(main.out PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(main.out PRIVATE ${GLUT_LIBRARY})
#------------------------------------------------------------------------

target_link_libraries(iscrtavanja LINK_PUBLIC image)
target_link_libraries(main.out PUBLIC image)
target_link_libraries(main.out PUBLIC mole)
target_link_libraries(main.out PUBLIC sargarepa)
target_link_libraries(main.out PUBLIC rotkvica)
target_link_libraries(main.out PUBLIC pecurka)
target_link_libraries(main.out PUBLIC coveculjak)
target_link_libraries(main.out PUBLIC iscrtavanja)
target_link_libraries(main.out PUBLIC igra)

cmake_minimum_required(VERSION 3.16)
project(MoleGame VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter")

add_subdirectory(lib/image)
add_subdirectory(lib/mole)
add_subdirectory(lib/sargarepa)
add_subdirectory(lib/rotkvica)
add_subdirectory(lib/pecurka)
add_subdirectory(lib/coveculjak)
add_subdirectory(lib/iscrtavanja)
add_subdirectory(lib/igra)

add_executable(main.out src/main.cpp)

# Deo vezan za OpenGL --------------------------------------------------
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(main.out PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(main.out PRIVATE ${GLUT_LIBRARY})
#------------------------------------------------------------------------

target_link_libraries(iscrtavanja image sargarepa rotkvica pecurka)
target_link_libraries(sargarepa mole)
target_link_libraries(rotkvica mole)
target_link_libraries(pecurka mole)
target_link_libraries(coveculjak mole sargarepa rotkvica pecurka)
target_link_libraries(igra iscrtavanja coveculjak)

target_link_libraries(main.out PUBLIC mole sargarepa rotkvica pecurka coveculjak iscrtavanja igra)

add_library(
    rotkvica
    rotkvica.hpp
    rotkvica.cpp
)

target_include_directories(rotkvica PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)")
add_library(
    igra
    igra.hpp
    igra.cpp
)

target_include_directories(igra PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)")
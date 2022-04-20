add_library(
    sargarepa
    sargarepa.hpp
    sargarepa.cpp
)

target_include_directories(sargarepa PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)")
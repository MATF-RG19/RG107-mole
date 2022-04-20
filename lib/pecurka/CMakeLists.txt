add_library(
    pecurka
    pecurka.hpp
    pecurka.cpp
)

target_include_directories(pecurka PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)")
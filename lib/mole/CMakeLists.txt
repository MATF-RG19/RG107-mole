add_library(
    mole
    mole.hpp
    mole.cpp
)

target_include_directories(mole PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)")
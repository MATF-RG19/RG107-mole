add_library(
    coveculjak
    coveculjak.hpp
    coveculjak.cpp
)

target_include_directories(coveculjak PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)")
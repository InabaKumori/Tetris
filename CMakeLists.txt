# CMakeList.txt : CMake project for Tetris_Visual_Studio, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Tetris_Visual_Studio")

# Add source to this project's executable.
add_executable (Tetris_Visual_Studio "Tetris_Visual_Studio.cpp" "Tetris_Visual_Studio.h")
include_directories(${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(Tetris_Visual_Studio ${CMAKE_SOURCE_DIR}/library/sfml-graphics.lib)
target_link_libraries(Tetris_Visual_Studio ${CMAKE_SOURCE_DIR}/library/sfml-audio.lib)
target_link_libraries(Tetris_Visual_Studio ${CMAKE_SOURCE_DIR}/library/sfml-network.lib)
target_link_libraries(Tetris_Visual_Studio ${CMAKE_SOURCE_DIR}/library/sfml-system.lib)
target_link_libraries(Tetris_Visual_Studio ${CMAKE_SOURCE_DIR}/library/sfml-window.lib)

include_directories(${CMAKE_SOURCE_DIR}/include)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tetris_Visual_Studio PROPERTY CXX_STANDARD 20)
  set_property(TARGET Tetris_Visual_Studio PROPERTY CXX_STANDARD_REQUIRED ON)
endif()

# TODO: Add tests and install targets if needed.

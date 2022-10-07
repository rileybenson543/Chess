# CMakeList.txt : CMake project for Chess, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


# Add source to this project's executable.
add_executable (Chess "src/Chess.cpp" "include/Chess.h" "include/Piece.h" "src/Game.cpp" "include/Game.h" "src/Piece.cpp" "src/data_structure.cpp")
include_directories(include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Chess PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

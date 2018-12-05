cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_FLAGS "-ggdb -std=c++11 -Wall ")
project(main)
add_executable(
  out
  src/Core/InputManager.cpp
  src/Core/MainWindow.cpp
  src/main.cpp
)	
target_link_libraries(out SDL2)

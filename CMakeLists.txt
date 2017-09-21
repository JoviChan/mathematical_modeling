cmake_minimum_required(VERSION 3.8)
project(code)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework OpenGL -framework GLUT -framework Foundation")



set(SOURCE_FILES main.cpp roadMap.cpp)
add_executable(code ${SOURCE_FILES})

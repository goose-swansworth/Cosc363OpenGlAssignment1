cmake_minimum_required(VERSION 3.16)

project(Assignment1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall)

add_executable(railway_world RailwayWorld.cpp RailModels.cpp assignmentfuncs.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(railway_world OpenGL::GL OpenGL::GLU GLUT::GLUT)

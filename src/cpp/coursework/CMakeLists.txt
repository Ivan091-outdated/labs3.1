cmake_minimum_required(VERSION 3.17)
project(coursework)

set(CMAKE_CXX_FLAGS -pthread)
find_package(OpenMP REQUIRED)
set(CMAKE_CXX_STANDARD 14)

add_executable(coursework main.cpp functions.cpp functions.h)
target_link_libraries(coursework PUBLIC OpenMP::OpenMP_CXX)
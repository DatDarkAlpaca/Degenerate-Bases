cmake_minimum_required(VERSION 3.19.2)

project(DegenerateBases)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
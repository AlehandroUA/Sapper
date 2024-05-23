cmake_minimum_required(VERSION 3.10)

project(Sapper)

set(CMAKE_CXX_STANDARD 11)

add_executable(Sapper Sapper/Sapper/Sapper.cpp)

target_link_libraries(Sapper PRIVATE time)

include_directories(${CMAKE_SOURCE_DIR})
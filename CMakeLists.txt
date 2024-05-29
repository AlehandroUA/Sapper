cmake_minimum_required(VERSION 3.10)

project(Sapper)

set(CMAKE_CXX_STANDARD 11)

option(BUILD_TESTS "Build unit tests" OFF) # Опция для сборки тестов

include_directories(${CMAKE_SOURCE_DIR})

add_executable(Sapper Sapper/Sapper/Sapper.cpp)

if(BUILD_TESTS)
    add_executable(SapperTests Sapper/SapperTests/SapperTests.cpp)
    # Добавьте другие файлы, необходимые для тестов, если нужно
endif()

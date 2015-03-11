cmake_minimum_required(VERSION 2.8.4)

enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(libraries/swears)

add_subdirectory(src)

add_subdirectory(test)

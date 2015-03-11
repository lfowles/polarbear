cmake_minimum_required(VERSION 2.8.4)

include(CTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(libraries/swears)

add_subdirectory(src)

add_subdirectory(test)

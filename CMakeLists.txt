cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# I don't know how to include an external (uninstalled) project well in CMake, so just hardcode in the path to includes and the .so

set(SWEARS_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../swears/include/)
set(SWEARS_LIBRARY )
include_directories(${SWEARS_INCLUDE_PATH})

add_subdirectory(src)

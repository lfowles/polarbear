# from http://www.kaizou.org/2014/11/gtest-cmake/
# Enable ExternalProject CMake module
include(ExternalProject)

# Get threads
find_package(Threads REQUIRED)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_library(libgtest_main IMPORTED STATIC GLOBAL)

add_dependencies(libgtest gtest)
add_dependencies(libgtest_main gtest)

# Set gtest properties
ExternalProject_Get_Property(gtest source_dir binary_dir)
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
#    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
)

set_target_properties(libgtest_main PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/libgtest_main.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
#    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/include")

# Download and install GoogleMock
#ExternalProject_Add(
#    gmock
#    URL https://googlemock.googlecode.com/files/gmock-1.7.0.zip
#    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gmock
#    # Disable install step
#    INSTALL_COMMAND ""
#)
#
# Create a libgmock target to be used as a dependency by test programs
#add_library(libgmock IMPORTED STATIC GLOBAL)
#add_dependencies(libgmock gmock)
#
# Set gmock properties
#ExternalProject_Get_Property(gmock source_dir binary_dir)
#set_target_properties(libgmock PROPERTIES
#    "IMPORTED_LOCATION" "${binary_dir}/libgmock.a"
#    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
#    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
#)
# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
#include_directories("${source_dir}/include")

# And now, the rest of the story

set(SOURCE_FILES main.cpp)
add_executable(polarbear_test ${SOURCE_FILES})
target_link_libraries(polarbear_test libgtest libgtest_main polarbear)
add_test(NAME polarbear_test COMMAND polarbear_test)
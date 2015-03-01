add_subdirectory(polarbear)

project(cursestest)

set(SOURCE_FILES main.cpp)
add_executable(cursestest ${SOURCE_FILES})
target_link_libraries(cursestest polarbear)
target_include_directories(cursestest PRIVATE ../include)

install(TARGETS cursestest EXPORT cursestest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include)

install(EXPORT cursestest DESTINATION share/cursestest/cmake)
add_subdirectory(tui)
add_subdirectory(game)

project(cursestest)

set(SOURCE_FILES main.cpp)
add_executable(cursestest ${SOURCE_FILES})
target_link_libraries(cursestest game)
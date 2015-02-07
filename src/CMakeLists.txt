add_subdirectory(tui)
add_subdirectory(game)

project(cursestest)

include_directories(".")

set(SOURCE_FILES main.cpp)
add_executable(cursestest ${SOURCE_FILES})
target_link_libraries(cursestest game)
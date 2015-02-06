project(tui)

set(SOURCE_FILES curses.cpp
                 window.cpp
                 input.cpp)
add_library(tui SHARED ${SOURCE_FILES})
target_link_libraries(tui ncurses)
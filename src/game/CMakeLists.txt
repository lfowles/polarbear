project(game)

include_directories("..")

set(SOURCE_FILES game.cpp
                 render.cpp
                 eventdispatch.cpp)
add_library(game SHARED ${SOURCE_FILES})
target_link_libraries(game tui)
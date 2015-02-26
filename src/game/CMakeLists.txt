project(game)


include_directories("..")
include_directories(".")

set(SOURCE_FILES game.cpp
                 render.cpp
                 eventdispatch.cpp
                 systems/systemmanager.cpp)
add_library(game SHARED ${SOURCE_FILES})

target_link_libraries(game ${SWEARS_LIBRARY})
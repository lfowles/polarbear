project(polarbear)


#include_directories("..")
#include_directories(".")

set(SOURCE_FILES game.cpp
                 render.cpp
                 eventdispatch.cpp
                 cursessingleton.cpp
                 systems/systemmanager.cpp)
add_library(polarbear SHARED ${SOURCE_FILES})
target_link_libraries(polarbear swears)
target_include_directories(polarbear PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/>
    $<INSTALL_INTERFACE:include/>)

install(TARGETS polarbear EXPORT polarbear
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include)

install(EXPORT polarbear DESTINATION share/polarbear/cmake)

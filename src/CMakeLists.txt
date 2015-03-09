project(polarbear)

set(SOURCE_FILES game.cpp
                 render.cpp
                 eventdispatch.cpp
                 cursessingleton.cpp
                 components/components.cpp
                 scenes/scenemanager.cpp
                 systems/systemmanager.cpp
                 systems/cursesinput.cpp
                 systems/cursesrender.cpp
                 systems/keyboardcontroller.cpp)

add_library(polarbear SHARED ${SOURCE_FILES})
target_link_libraries(polarbear swears)
target_include_directories(polarbear PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/>
    $<INSTALL_INTERFACE:include/>)

# TODO: resource loader that can be queried.
# This is so that resource paths can be set at any level of the project and multiple resource paths loaded.
target_compile_definitions(polarbear PUBLIC "-DRESOURCE_PATH=\"${CMAKE_SOURCE_DIR}/resources/\"")

install(TARGETS polarbear EXPORT polarbear
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include)

install(EXPORT polarbear DESTINATION share/polarbear/cmake)

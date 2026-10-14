# Every .cpp under engine/src is compiled into the library automatically, so a new file
# needs no CMake edit (CONFIGURE_DEPENDS re-checks the list on each build).
# Put implementation files in engine/src/<area>/ and headers in engine/include/engine/<area>/.
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(engine STATIC ${ENGINE_SOURCES})
add_library(engine::engine ALIAS engine)

target_include_directories(engine PUBLIC include)
target_link_libraries(engine PUBLIC engine_options)

add_executable(sandbox main.cpp)
add_executable(day1 day1.cpp)
target_link_libraries(sandbox PRIVATE engine::engine)
target_link_libraries(day1 PRIVATE engine::engine)
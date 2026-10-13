add_library(engine STATIC
  src/core/Assert.cpp
)
add_library(engine::engine ALIAS engine)

target_include_directories(engine PUBLIC include)
target_link_libraries(engine PUBLIC engine_options)

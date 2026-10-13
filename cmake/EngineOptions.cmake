# Shared compile/link options, applied by linking against `engine_options`.
add_library(engine_options INTERFACE)

if(MSVC)
  target_compile_options(engine_options INTERFACE /W4 /permissive-)
  if(ENGINE_WARNINGS_AS_ERRORS)
    target_compile_options(engine_options INTERFACE /WX)
  endif()
  if(ENGINE_ASAN)
    target_compile_options(engine_options INTERFACE /fsanitize=address)
  endif()
  if(ENGINE_TSAN)
    message(FATAL_ERROR "ThreadSanitizer is not available with MSVC.")
  endif()
else()
  target_compile_options(engine_options INTERFACE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wnon-virtual-dtor -Wold-style-cast)
  if(ENGINE_WARNINGS_AS_ERRORS)
    target_compile_options(engine_options INTERFACE -Werror)
  endif()

  if(ENGINE_ASAN)
    target_compile_options(engine_options INTERFACE
      -fsanitize=address,undefined -fno-omit-frame-pointer -fno-sanitize-recover=undefined)
    target_link_options(engine_options INTERFACE -fsanitize=address,undefined)
  endif()

  if(ENGINE_TSAN)
    target_compile_options(engine_options INTERFACE -fsanitize=thread -fno-omit-frame-pointer)
    target_link_options(engine_options INTERFACE -fsanitize=thread)
  endif()
endif()

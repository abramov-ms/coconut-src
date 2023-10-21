cmake_minimum_required(VERSION 3.22)

project(
  concurrency
  LANGUAGES C CXX ASM
)

set(CMAKE_C_FLAGS "-g -Wall -Wextra -Werror")
if(ASAN)
  add_compile_options(-fsanitize=address -fno-sanitize-recover=all)
  add_link_options(-fsanitize=address)
endif()
if(TSAN)
  add_compile_options(-fsanitize=thread -fno-sanitize-recover=all)
  add_link_options(-fsanitize=thread)
endif()

add_subdirectory(counter)
add_subdirectory(rw)
add_subdirectory(list)
add_subdirectory(queue)
add_subdirectory(stack)

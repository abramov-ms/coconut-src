cmake_minimum_required(VERSION 3.22)

project(
  proc
  LANGUAGES C CXX ASM
)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")
if(ASAN)
  add_compile_options(-fsanitize=address -fno-sanitize-recover=all)
  add_link_options(-fsanitize=address)
endif()

add_subdirectory(sh)
add_subdirectory(bomb)
add_subdirectory(checksum)
add_subdirectory(elf)

cmake_minimum_required(VERSION 3.22)

project(
  x86asm
  LANGUAGES C CXX ASM
)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

if(ASAN)
  add_compile_options(-fsanitize=address -fno-sanitize-recover=all)
  add_link_options(-fsanitize=address)
endif()

add_subdirectory(fibonacci)
add_subdirectory(sqrt)
add_subdirectory(linalg)
add_subdirectory(syscall)

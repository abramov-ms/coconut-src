cmake_minimum_required(VERSION 3.28)

project(ascii_matrix C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_C_FLAGS "-g -Wall -Wextra -Werror")

add_library(utf8 utf8.h utf8.c)

add_executable(utf8_test utf8_test.c)
target_link_libraries(utf8_test utf8)

add_executable(
  main
  main.c
  fs.h fs.c
  mask.h mask.c
  utf8.h utf8.c
  terminal.h terminal.c
  matrix.h matrix.c
)

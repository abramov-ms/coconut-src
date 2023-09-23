cmake_minimum_required(VERSION 3.22)

project(
  encodings
  LANGUAGES C CXX
)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -fsanitize=undefined,address")

add_subdirectory(numeric)
add_subdirectory(text)

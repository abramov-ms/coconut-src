cmake_minimum_required(VERSION 3.22)

project(
  armasm
  LANGUAGES C CXX ASM
)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

add_subdirectory(status)
add_subdirectory(fibonacci)

cmake_minimum_required(VERSION 3.22)

project(
  filesystems
  LANGUAGES C CXX
)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

add_subdirectory(io)
add_subdirectory(faulty)
add_subdirectory(fswatcher)
add_subdirectory(trollfs)

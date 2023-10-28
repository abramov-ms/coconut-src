cmake_minimum_required(VERSION 3.22)

project(
  ipc
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

add_subdirectory(cat)
add_subdirectory(pipe)
add_subdirectory(nohup)
add_subdirectory(recover)
add_subdirectory(counter)

cmake_minimum_required(VERSION 3.30)

project(trollfs C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE REQUIRED fuse3)

add_executable(trollfs main.c)
target_link_libraries(trollfs ${FUSE_LIBRARIES})

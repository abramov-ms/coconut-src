find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE REQUIRED fuse3)

add_executable(trollfs main.c)
target_link_libraries(trollfs ${FUSE_LIBRARIES})

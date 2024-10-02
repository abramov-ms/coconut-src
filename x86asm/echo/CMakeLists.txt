set(CMAKE_C_FLAGS "-g -no-pie")
add_executable(echo main.c echo.S echo.h)

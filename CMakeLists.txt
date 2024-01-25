cmake_minimum_required(VERSION 3.0.0)
project(elliotsr-simd VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 23)

add_executable(elliotsr-simd main.c)
target_link_libraries(elliotsr-simd m)
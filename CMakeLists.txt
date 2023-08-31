cmake_minimum_required(VERSION 3.23)
project(sens_calc)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(sens_calc main.cpp includes/colored_cout.h includes/colored_cout.cpp)

cmake_minimum_required(VERSION 3.2...3.5 FATAL_ERROR)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(PROJECT_NAME HW-dpcpp-3.2)
project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} src/main.cpp src/LogCommandWithObserver.hpp)

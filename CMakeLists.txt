cmake_minimum_required(VERSION 3.1)
project(GPIO_test)

set (CMAKE_CXX_STANDARD 11)
include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(gpioTest ${SOURCES})

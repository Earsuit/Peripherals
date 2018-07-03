cmake_minimum_required(VERSION 2.8)
project(gpioTest)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(gpioTest ${SOURCES})

find_package(glog 0.3.5 REQUIRED)
target_link_libraries(gpioTest glog::glog)


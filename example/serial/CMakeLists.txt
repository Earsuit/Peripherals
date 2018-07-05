cmake_minimum_required(VERSION 2.8)
project(serial)

include_directories(../../include)
file(GLOB SOURCES "../../src/*.cpp" "main.cpp")

add_executable(serial ${SOURCES})

find_package(glog 0.3.5 REQUIRED)
target_link_libraries(serial glog::glog)


cmake_minimum_required(VERSION 2.8)
project(mpu9250)

include_directories(../../include)
file(GLOB SOURCES "../../src/*.cpp" "main.cpp")

add_executable(mpu9250 ${SOURCES})

find_package(glog 0.3.5 REQUIRED)
target_link_libraries(mpu9250 glog::glog)


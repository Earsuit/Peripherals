cmake_minimum_required(VERSION 2.8)
project(peripheralTest)

include_directories(include)
file(GLOB SOURCES "src/*.cpp" "main.cpp")

add_executable(peripheralTest ${SOURCES})

find_package(glog 0.3.5 REQUIRED)
target_link_libraries(peripheralTest glog::glog)


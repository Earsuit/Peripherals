cmake_minimum_required(VERSION 2.8)
project(gpioTest)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread -ldl")

file(GLOB SOURCES "src/*.cpp")

add_executable(gpioTest ${SOURCES})

find_package(Threads)
target_link_libraries(gpioTest ${CMAKE_THREAD_LIBS_INIT}) # For pthreads
if(NOT WIN32)
    target_link_libraries(gpioTest dl) # For ldl
endif()




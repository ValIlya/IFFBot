cmake_minimum_required(VERSION 3.25)

project(glkclient)

set(CMAKE_VERBOSE_MAKEFILE ON)
# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++17")

include_directories(cheapglk)  # Add the include directory

add_executable(client client.cpp)

target_link_libraries(client PRIVATE cheapglk)  
target_include_directories(client PRIVATE cheapglk) 
target_link_directories(client PRIVATE cheapglk)


cmake_minimum_required(VERSION 3.25)

project(glkclient)

set(CMAKE_VERBOSE_MAKEFILE ON)
# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++17")

include_directories(cheapglk)  # Add the include directory

add_executable(client client.cpp)

add_library(cheapglk STATIC
        cheapglk/cgfref.c
        cheapglk/cggestal.c
        cheapglk/cgmisc.c
        cheapglk/cgstream.c
        cheapglk/cgstyle.c
        cheapglk/cgwindow.c
        cheapglk/cgschan.c
        cheapglk/cgdate.c
        cheapglk/cgunicod.c
        cheapglk/main.c
        cheapglk/gi_dispa.c
        cheapglk/gi_blorb.c
        cheapglk/gi_debug.c
        cheapglk/cgblorb.c
)

target_link_libraries(client PRIVATE cheapglk)  


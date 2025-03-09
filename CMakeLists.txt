cmake_minimum_required( VERSION 3.18.0 )
project(IFFBot)

cmake_policy(SET CMP0075 NEW)
cmake_policy(SET CMP0091 NEW)

set( CMAKE_CXX_STANDARD 20 CACHE STRING "" FORCE )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE )

add_executable( main )

add_subdirectory( "external" )
add_subdirectory( "src" )

# for glk.h
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/cheapglk)

# Link the glk library to the main executable
target_link_libraries(main PRIVATE glk)


set_target_properties( main PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME} )

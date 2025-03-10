cmake_minimum_required( VERSION 3.18.0 )
project(IFFBot)

cmake_policy(SET CMP0075 NEW)
cmake_policy(SET CMP0091 NEW)

if(POLICY CMP0069)
    cmake_policy(SET CMP0069 NEW)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT HAS_LTO)
endif()


set( CMAKE_CXX_STANDARD 20 CACHE STRING "" FORCE )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE )

add_executable( main )

# for glk.h
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/cheapglk)

add_subdirectory( "external" )
add_subdirectory( "src" )
add_subdirectory( "terps" )

# Link the glk library to the main executable
target_link_libraries(main PRIVATE glk)


set_target_properties( main PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME} )

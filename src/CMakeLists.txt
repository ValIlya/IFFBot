file(GLOB_RECURSE SRC_FILES "*.c" "*.cpp" "*.h")

target_sources( main PRIVATE ${SRC_FILES})

file(GLOB_RECURSE SRC_FILES "tglk/*.c" "tglk/*.cpp" "tglk/*.h")

add_library(glk ${SRC_FILES})

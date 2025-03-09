file(GLOB_RECURSE SRC_FILES "*.c" "*.cpp" "*.h")

target_sources( main PRIVATE ${SRC_FILES})

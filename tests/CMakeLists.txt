### Tests CMake ###

# Includes the dr4-h header #
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(test_fmt test_fmt.c)
add_test(test_fmt test_fmt)
### Tests CMake ###

# Includes the dr4-h header #
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(test_fmt test_fmt.c)
add_test(test_fmt test_fmt)

add_executable(test_read test_read.c)
add_test(test_read test_read)

add_executable(test_find test_find.c)
add_test(test_find test_find)
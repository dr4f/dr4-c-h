### Examples CMake ###

include_directories(
   ${PROJECT_SOURCE_DIR}/src
)

add_executable(magicseq magicseq.c)
add_executable(debug_and_strings debug_and_strings.c)
add_executable(row_appender row_appender.c)
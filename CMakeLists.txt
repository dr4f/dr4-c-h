cmake_minimum_required(VERSION 3.5)

# Project dr4-h begins here #
PROJECT(dr4-h)

# Single Header File Name# 
SET(dr4-h_header_file dr4-h.h)

# Version Tracker #
SET(dr4-h_version_major 0)
SET(dr4-h_version_minor 0)
SET(dr4-h_version_patch 1)
SET(dr4-h_version "${dr4-h_version_major}.${cosair_version_minor}.${dr4-h_version_patch}")

string(TIMESTAMP dr4-h_build_time)

# Enables Testing for project #
enable_testing()


add_subdirectory(tests)
add_subdirectory(examples)

# dr4-h shared lib #
add_library(Dr4hShared SHARED ${PROJECT_SOURCE_DIR}/src/dr4-h-lib.c)

## Copies the single header include to the binary dir ##
file(COPY ${PROJECT_SOURCE_DIR}/src/${dr4-h_header_file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Writes build version to receipt file.
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/build_receipt.txt "dr4-h Build\n  Version ${dr4-h_version}\n  Built at : ${dr4-h_build_time}\n")
cmake_minimum_required(VERSION 2.8)

project(JPEG)

aux_source_directory(${PROJECT_BINARY_DIR}/../src SRC_LIST)

include_directories(${PROJECT_BINARY_DIR}/../inc)

SET(CMAKE_BUILD_TYPE "Debug")

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")

SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_executable(JPEG ${SRC_LIST})

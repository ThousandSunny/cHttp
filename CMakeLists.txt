cmake_minimum_required(VERSION 3.10.2)

project(CppHttp)

set(CMAKE_CXX_STANDARD 11)

include_directories(./common)

add_subdirectory(third/log)

add_subdirectory(client)
add_subdirectory(server)
cmake_minimum_required(VERSION 3.15)

project(CppHttp)

include_directories(./common)

add_subdirectory(client)
add_subdirectory(server)
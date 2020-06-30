cmake_minimum_required(VERSION 3.10.2)

project(CppHttp)

include_directories(./common)

add_subdirectory(client)
add_subdirectory(server)
cmake_minimum_required(VERSION 3.15)

project(CppHttp)

include_directories(client)
include_directories(server)

add_executable(CppHttp server/server.cpp example/main.cpp client/client.cpp client/client.h)
cmake_minimum_required(VERSION 3.21)
project(httpServer)

set(CMAKE_CXX_STANDARD 14)

add_library(httpServer server.cpp)

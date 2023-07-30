cmake_minimum_required(VERSION 3.26.4)
project (frida)

set(CMAKE_CXX_STANDARD 17)
find_library(jsoncpp)

add_executable(frida main.cpp)

target_link_libraries(frida jsoncpp)
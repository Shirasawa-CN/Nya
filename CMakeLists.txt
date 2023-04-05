cmake_minimum_required(VERSION 3.20)
project(Nya VERSION 0.0.1 LANGUAGES CXX)
message("==================================================================")
message("C++ Standard: C++20")

#windows clang
#set(CMAKE_CXX_COMPILE "clang++")
#unix gcc
#set(CMAKE_CXX_COMPILE "gcc")
#unix clang
#set(CMAKE_CXX_COMPILE "clang")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC src/main.cpp src/cli/cli.cpp src/cli/cli.h src/lexer.cpp src/lexer.h)

#find_package(glog CONFIG REQUIRED)
#target_link_libraries(main PRIVATE glog::glog)

add_executable(${PROJECT_NAME} ${SRC})
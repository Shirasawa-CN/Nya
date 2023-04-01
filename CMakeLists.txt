cmake_minimum_required(VERSION 3.20)
project(Nya VERSION 0.0.1 LANGUAGES C)
message("==================================================================")
message("C Standard: C17")

#windows clang
#set(CMAKE_C_COMPILE "clang-cl")
#unix gcc
#set(CMAKE_C_COMPILE "gcc")
#unix clang
#set(CMAKE_C_COMPILE "clang")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SRC src/tool/result.c src/tool/result.h src/main.c src/cli/cli.c src/cli/cli.h src/lexer.h src/lexer.c)

add_executable(${PROJECT_NAME} ${SRC})
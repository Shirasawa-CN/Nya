cmake_minimum_required(VERSION 3.20)

#set vcpkg path
#in fact, the root directory environment variable for vcpkg has already been set here
set(CMAKE_TOOLCHAIN_FILE <vcpkg_dir>/scripts/buildsystems/vcpkg.cmake)
project(Nya VERSION 0.0.1 LANGUAGES C CXX)
message("==================================================================")
message("C++ Standard: C++20")

#windows clang
#set(CMAKE_CXX_COMPILE "clang++")
#windows g++
#set(CMAKE_CXX_COMPILE "g++")
#unix gcc
#set(CMAKE_CXX_COMPILE "gcc")
#unix clang
#set(CMAKE_CXX_COMPILE "clang")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC src/main.cpp src/cli/cli.cpp src/cli/cli.h src/lexer.cpp src/lexer.h src/error.cpp src/error.h src/ast.h)

find_package(LLVM CONFIG REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(HandleLLVMOptions)
add_definitions(${LLVM_DEFINITIONS})

# Find the libraries that correspond to the LLVM components that we wish to use
llvm_map_components_to_libnames(llvm_libs Support Core IRReader)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${LLVM_INCLUDE_DIRS})

# Link against LLVM libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${llvm_libs})

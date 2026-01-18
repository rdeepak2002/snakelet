cmake_minimum_required(VERSION 3.10)
project(Snakelet VERSION 1.0)

set(CMAKE_C_STANDARD 99)

# 1. Build the library 
add_library(snakelet_lib src/snakelet.c src/arena.c src/tokenizer.c)
target_include_directories(snakelet_lib PUBLIC include PRIVATE src)

# 2. Build the CLI
add_executable(snakelet cli/main.c)
target_link_libraries(snakelet PRIVATE snakelet_lib)

# 3. Build the Tests
option(BUILD_TESTING "Build the testing tree." ON)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

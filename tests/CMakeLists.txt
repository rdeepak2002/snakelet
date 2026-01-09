add_executable(test_arena test_arena.c)

# Link to the main library 
target_link_libraries(test_arena PRIVATE snakelet_lib)

# Allow test to see private headers 
target_include_directories(test_arena PRIVATE ../src)

# Register with CTest
add_test(NAME ArenaTest COMMAND test_arena)

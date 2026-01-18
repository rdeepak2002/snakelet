add_executable(test_allocator test_allocator.c)
add_executable(test_arena test_arena.c)
add_executable(test_tokenizer test_tokenizer.c)

# Link to the main library 
target_link_libraries(test_allocator PRIVATE snakelet_lib)
target_link_libraries(test_arena PRIVATE snakelet_lib)
target_link_libraries(test_tokenizer PRIVATE snakelet_lib)

# Allow test to see private headers 
target_include_directories(test_allocator PRIVATE ../src)
target_include_directories(test_arena PRIVATE ../src)
target_include_directories(test_tokenizer PRIVATE ../src)

# Register with CTest
add_test(NAME AllocatorTest COMMAND test_allocator)
add_test(NAME ArenaTest COMMAND test_arena)
add_test(NAME TokenizerTest COMMAND test_tokenizer)

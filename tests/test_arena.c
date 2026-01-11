#include <assert.h>
#include "../src/arena.h"

int main() {
	unsigned char buffer[64];
	Arena arena;
	arena_init(&arena, buffer, sizeof(buffer));
	
	// test padding, reset, and getting position
	assert(arena_get_pos(&arena) == 0);
	assert(arena_alloc(&arena, 3));
	assert(arena_get_pos(&arena) == 3);
	assert(arena_alloc_zero(&arena, 4));
	assert(arena_get_pos(&arena) == 12);
	arena_reset(&arena);
	assert(arena_get_pos(&arena) == 0);
	
	// test writing data
	char* ptr = arena_alloc_zero(&arena, 10);
	for (int i = 0; i < 10; ++i) {
		assert(ptr[i] == 0);
		ptr[i] = i * 3;
	}
	for (int i = 0; i < 10; ++i) {
		assert(ptr[i] == i * 3);
	}

	assert(arena_alloc_zero(&arena, 48));
	assert(arena_alloc_zero(&arena, 1) == NULL);
}

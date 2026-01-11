#include <stdio.h>
#include <assert.h>
#include "../src/allocator.h"

int main() {
	unsigned char buffer[64];
	Arena arena;
	arena_init(&arena, buffer, sizeof(buffer));
	Allocator alloc = arena_allocator(&arena);
	char* ptr = alloc.calloc(alloc.user_data, 63);
	// test data is correctly written, updated then read
	for (int i = 0; i < 63; ++i) {
		ptr[i] = i;
	}
	for (int i = 0; i < 63; ++i) {
		assert(ptr[i] == i);
	}
	for (int j = 0; j < 23; ++j) {
		ptr[j] = 2 * j;
	}
	for (int j = 0; j < 23; ++j) {
		assert(ptr[j] == 2 * j);
	}
	// test scenario where we ask for more than what buffer allows
	assert(alloc.calloc(alloc.user_data, 1) == NULL);
	return 0;
}

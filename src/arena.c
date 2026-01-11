#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "arena.h"

#define DEFAULT_ALIGNMENT 8

void arena_init(Arena *arena, unsigned char *buffer, size_t buffer_length) {
	assert(arena != NULL);
	assert(buffer != NULL);

	arena->buffer = buffer;
	arena->buffer_length = buffer_length;
	arena->offset = 0;
}

void arena_reset(Arena *arena) {
	assert(arena != NULL);
	arena->offset = 0;
}

void* arena_alloc(Arena* arena, size_t size) {
	assert(arena != NULL);

	size_t byte_alignment = DEFAULT_ALIGNMENT;

	// calculate padding needed for byte alignment
	uintptr_t curr_ptr = (uintptr_t) arena->buffer + arena->offset;
	uintptr_t offset = curr_ptr % byte_alignment;
	uintptr_t padding = (offset == 0) ? 0 : (byte_alignment - offset);
	
	// account for requested size being too large
	// also account for size causing overflow
	if (arena->offset + padding > arena->buffer_length || 
    		size > arena->buffer_length - (arena->offset + padding)) {
    		return NULL;
	}
	
	arena->offset += padding;
	void* start = (void*) (arena->buffer + arena->offset);
	arena->offset += size;
	return start;
}

void* arena_alloc_zero(Arena* arena, size_t size) {
	void* start = arena_alloc(arena, size);
	if (start != NULL) {
		memset(start, 0, size);
	}
	return start;
}

size_t arena_get_pos(Arena *arena) {
	assert(arena != NULL);

	return arena->offset;
}

void arena_set_pos(Arena *arena, size_t pos) {
	assert(pos >= 0 && pos <= arena->buffer_length);
	arena->offset = pos;
}

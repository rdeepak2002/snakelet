#ifndef SNAKELET_ALLOCATOR_H
#define SNAKELET_ALLOCATOR_H

#include <stddef.h>
#include "arena.h"

typedef struct Allocator {
	void *user_data;

	void* (*malloc)(void *user_data, size_t size);
	void* (*calloc)(void *user_data, size_t size);
	void (*free)(void *user_data, void *ptr);
} Allocator;

static inline void* arena_malloc_impl(void *user_data, size_t size) {
	return arena_alloc((Arena*) user_data, size);
}

static inline void* arena_calloc_impl(void *user_data, size_t size) {
	return arena_alloc_zero((Arena*) user_data, size);
}

static inline void arena_free(void *user_data, void *ptr) {
	(void)user_data;
	(void)ptr;
}

static inline Allocator arena_allocator(Arena *arena) {
	return (Allocator){
		.user_data = arena,
		.malloc = arena_malloc_impl,
		.calloc = arena_calloc_impl,
		.free = arena_free
	};
}

#endif // SNAKELET_ALLOCATOR_H

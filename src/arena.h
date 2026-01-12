#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct {
	unsigned char* buffer;
	size_t buffer_length;
	size_t offset;
} Arena;

void arena_init(Arena* arena, unsigned char* buffer, size_t buffer_length);

void arena_reset(Arena* arena);

void* arena_alloc(Arena* arena, size_t size);

void* arena_alloc_zero(Arena* arena, size_t size);

size_t arena_get_pos(Arena* arena);

void arena_set_pos(Arena* a, size_t pos);

#endif // ARENA_H

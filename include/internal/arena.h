#pragma once
#include "tokenise.h"

#define ARENA_BLOCK_SIZE (sizeof(token) * 512)

struct arena_t
{
    void* start;
    void* next;
    size_t size_in_bytes;
} typedef arena_t;

arena_t* new_arena();
void* arena_alloc(arena_t* arena, size_t size);
void arena_free(arena_t* arena);

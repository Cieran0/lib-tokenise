#include "arena.h"
#include "stdlib.h"
#include "string.h"

void arena_grow(arena_t* arena, size_t size) {
    size_t current_size = arena->next - arena->start;
    void* new_start = malloc(arena->size_in_bytes + size);
    void* old_arena = arena->start;
    memcpy(new_start, old_arena, arena->size_in_bytes);
    free(old_arena);
    arena->start = new_start;
    arena->next = new_start+current_size;
    arena->size_in_bytes += size;
}

void* arena_alloc(arena_t* arena, size_t size) {
    size_t current_size = arena->next - arena->start;
    if(current_size + size > arena->size_in_bytes) {
        arena_grow(arena, size > ARENA_BLOCK_SIZE ? size : ARENA_BLOCK_SIZE);
    }

    void* start = arena->next;
    arena->next += size;

    return start;
}


void arena_free(arena_t* arena) {
    free(arena->start);
    free(arena);
}

arena_t* new_arena() {
    arena_t* arena = malloc(sizeof(arena));
    arena->start = malloc(ARENA_BLOCK_SIZE);
    arena->next = arena->start;
    arena->size_in_bytes = ARENA_BLOCK_SIZE;

    return arena;
}
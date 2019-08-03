#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

void vector_init(Vector* vec)
{
    vec->capacity = VECTOR_INIT_CAPACITY;
    vec->total = 0;
    vec->items = malloc(sizeof(void*) * vec->capacity);
}

int vector_total(Vector* vec)
{
    return vec->total;
}

static void vector_resize(Vector* vec, int capacity)
{
    void **items = realloc(vec->items, sizeof(void*) * capacity);
    if (items) {
        vec->items = items;
        vec->capacity = capacity;
    }
}

void vector_add(Vector* vec, void* item)
{
    if (vec->capacity == vec->total)
        vector_resize(vec, vec->capacity * 2);
    vec->items[vec->total++] = item;
}

void vector_set(Vector* vec, int index, void* item)
{
    if (index >= 0 && index < vec->total)
        vec->items[index] = item;
}

void *vector_get(Vector* vec, int index)
{
    if (index >= 0 && index < vec->total)
        return vec->items[index];
    return NULL;
}

void vector_delete(Vector* vec, int index)
{
    if (index < 0 || index >= vec->total)
        return;

    vec->items[index] = NULL;

    for (int i = index; i < vec->total - 1; i++) {
        vec->items[i] = vec->items[i + 1];
        vec->items[i + 1] = NULL;
    }

    vec->total--;

    if (vec->total > 0 && vec->total == vec->capacity / 4)
        vector_resize(vec, vec->capacity / 2);
}

void vector_free(Vector* vec)
{
    free(vec->items);
}

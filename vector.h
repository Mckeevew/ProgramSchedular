/*
 * Author: William Mckeever
 */

#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_CAPACITY 10

#define VECTOR_INIT(vec) Vector vec; vector_init(&vec)
#define VECTOR_ADD(vec, item) vector_add(&vec, (void*) item)
#define VECTOR_SET(vec, id, item) vector_set(&vec, id, (void*) item)
#define VECTOR_GET(vec, type, id) (type) vector_get(&vec, id)
#define VECTOR_DELETE(vec, id) vector_delete(&vec, id)
#define VECTOR_TOTAL(vec) vector_total(&vec)
#define VECTOR_FREE(vec) vector_free(&vec)

typedef struct Vector {
    void **items;
    int capacity;
    int total;
} Vector;

void vector_init(Vector* vec);
int vector_total(Vector* vec);
static void vector_resize(Vector* vec, int capacity);
void vector_add(Vector* vec, void* item);
void vector_set(Vector* vec, int index, void* item);
void* vector_get(Vector* vec, int index);
void vector_delete(Vector* vec, int index);
void vector_free(Vector* vec);

#endif //VECTOR_H

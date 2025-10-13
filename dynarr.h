// Humble implementation of a dynamic array

#ifndef DYNARR_H
#define DYNARR_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifndef DYNARR_ALIGNMENT
#define DYNARR_ALIGNMENT 8
#endif

#ifndef DYNARR_DEFAULT_GROW_SIZE
#define DYNARR_DEFAULT_GROW_SIZE 8
#endif

typedef enum dynarr_code{
    OK_DYNARR_CODE,
    ALLOC_ERR_DYNARR_CODE,
    SIZE_MISMATCH_ERR_DYNARR_CODE,
    DYNARR_EMPTY_ERR_DYNARR_CODE,
    IDX_OUT_OF_BOUNDS_ERR_DYNARR_CODE,
}DynArrCode;

typedef struct dynarr_allocator{
    void *ctx;
    void *(*alloc)(size_t size, void *ctx);
    void *(*realloc)(void *ptr, size_t old_size, size_t new_size, void *ctx);
    void (*dealloc)(void *ptr, size_t size, void *ctx);
}DynArrAllocator;

typedef int (*DynArrComparator)(const void *a, const void *b);
typedef int (*DynArrPredicate)(const void *item, void *ctx);
typedef struct dynarr DynArr;

// PUBLIC INTERFACE DYNARR
DynArr *dynarr_create(size_t item_size, const DynArrAllocator *allocator);
DynArr *dynarr_create_by(size_t item_size, size_t item_count, const DynArrAllocator *allocator);
#define DYNARR_CREATE_TYPE(_type, _allocator)(dynarr_create(sizeof(_type), _allocator))
#define DYNARR_CREATE_PTR(_allocator) DYNARR_CREATE_TYPE(uintptr_t, _allocator)
#define DYNARR_CREATE_TYPE_BY(_type, _count, _allocator)(dynarr_create_by(sizeof(_type), _count, _allocator))
#define DYNARR_CREATE_PTR_BY(_count, _allocator) DYNARR_CREATE_TYPE_BY(uintptr_t, _count, _allocator)

void dynarr_destroy(DynArr *dynarr);

size_t dynarr_capacity(const DynArr *dynarr);
size_t dynarr_len(const DynArr *dynarr);
size_t dynarr_available(const DynArr *dynarr);
int dynarr_reduce(DynArr *dynarr);
void dynarr_reverse(DynArr *dyarr);
void dynarr_sort(DynArr *dynarr, DynArrComparator comparator);
int dynarr_find(const DynArr *dynarr, const void *item, DynArrComparator comparator);
#define DYNARR_FIND(_dynarr, _comparator, _type, ...) dynarr_find((_dynarr), (_comparator), &(_type){__VA_ARGS__})

void *dynarr_get_raw(const DynArr *dynarr, size_t idx);
void *dynarr_get_ptr(const DynArr *dynarr, size_t idx);
#define DYNARR_GET_AS(_dynarr, _as, _idx)(*(_as *)(dynarr_get_raw((_dynarr), (_idx))))
#define DYNARR_GET_PTR_AS(_dynarr, _as, _idx) ((_as *)dynarr_get_ptr((_dynarr), (_idx)))

int dynarr_set_at(DynArr *dynarr, size_t idx, const void *item);
int dynarr_set_ptr(DynArr *dynarr, size_t idx, const void *ptr);
#define DYNARR_SET_AT(_dynarr, _idx, _type, ...) dynarr_set_at((_dynarr), (_idx), &(_type){__VA_ARGS__})

int dynarr_insert(DynArr *dynarr, const void *item);
int dynarr_insert_at(DynArr *dynarr, size_t idx, const void *item);
int dynarr_insert_ptr(DynArr *dynarr, const void *ptr);
int dynarr_insert_ptr_at(DynArr *dynarr, size_t idx, const void *ptr);
#define DYNARR_INSERT(_dynarr, _type, ...) dynarr_insert((_dynarr), &(_type){__VA_ARGS__})
#define DYNARR_INSERT_AT(_dynarr, _index, _type, ...) dynarr_insert_at((_dynarr), (_index), &(_type){__VA_ARGS__})

int dynarr_append(const DynArr *from, DynArr *to);
int dynarr_append_new(
    const DynArr *a_dynarr,
    const DynArr *b_dynarr,
    const DynArrAllocator *allocator,
    DynArr **out_new_dynarr
);

int dynarr_remove_index(DynArr *dynarr, size_t idx);
int dynarr_remove_if(DynArr *dynarr, DynArrPredicate predicate, void *ctx);
void dynarr_remove_all(DynArr *dynarr);

#endif
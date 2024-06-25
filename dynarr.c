#include "dynarr.h"

// public implementation
struct _dynarr_ *dynarr_create(size_t item_size, struct _dynarr_allocator_ *allocator)
{
    size_t bytes = sizeof(struct _dynarr_);
    struct _dynarr_ *vector = (struct _dynarr_ *)(allocator == NULL ? malloc(bytes) : allocator->dynarr_alloc(bytes, 0));

    vector->used = 0;
    vector->count = 0;
    vector->size = item_size;
    vector->items = NULL;
    vector->allocator = allocator;

    return vector;
}

void dynarr_destroy(struct _dynarr_ *dynarr)
{
    if (!dynarr)
        return;

    if (dynarr->allocator)
        dynarr->allocator->dynarr_dealloc(dynarr->items, 1);
    else
        free(dynarr->items);

    dynarr->used = 0;
    dynarr->count = 0;
    dynarr->items = NULL;

    if (dynarr->allocator)
        dynarr->allocator->dynarr_dealloc(dynarr, 0);
    else
        free(dynarr);

    dynarr = NULL;
}

size_t dynarr_padding(size_t item_size)
{
    size_t modulo = item_size & (DYNARR_ALIGNMENT - 1);
    return DYNARR_ALIGNMENT - modulo;
}

int dynarr_resize(size_t padding, size_t new_count, struct _dynarr_ *dynarr)
{
    void *items = NULL;

    if (dynarr->allocator)
        items = dynarr->allocator->dynarr_realloc(dynarr->items, DYNARR_SIZE(padding, new_count, dynarr));
    else
        items = realloc(dynarr->items, DYNARR_SIZE(padding, new_count, dynarr));

    if (!items)
        return 1;

    dynarr->items = items;
    dynarr->count = new_count;

    return 0;
}

void *dynarr_get(size_t index, struct _dynarr_ *dynarr)
{
    void *value = DYNARR_POSITION(index, dynarr);
    return value;
}

void dynarr_set(void *item, size_t index, struct _dynarr_ *dynarr)
{
    memcpy(DYNARR_POSITION(index, dynarr), item, dynarr->size);
}

int dynarr_insert(void *item, struct _dynarr_ *dynarr)
{
    if (dynarr->used >= dynarr->count && dynarr_resize(dynarr_padding(dynarr->size), DYNARR_DETERMINATE_GROW(dynarr->count), dynarr))
        return 1;

    memcpy(DYNARR_POSITION(dynarr->used++, dynarr), item, dynarr->size);

    return 0;
}

void dynarr_remove_index(size_t index, struct _dynarr_ *dynarr)
{
    if (index < dynarr->count - 1)
    {
        void *in = DYNARR_POSITION(index, dynarr);
        void *from = DYNARR_POSITION(index + 1, dynarr);
        size_t padding = dynarr_padding(dynarr->size);
        size_t count = dynarr->used - 1 - index;
        size_t size = DYNARR_SIZE(padding, count, dynarr);

        memmove(in, from, size);
    }

    if (dynarr->used - 1 > DYNARR_DEFAULT_GROW_SIZE && dynarr->used - 1 < dynarr->count / 2)
    {
        size_t padding = dynarr_padding(dynarr->size);
        size_t new_count = dynarr->count / 2;

        dynarr_resize(padding, new_count, dynarr);
    }

    dynarr->used--;
}

struct _dynarr_ptr_ *dynarr_ptr_create(struct _dynarr_allocator_ *allocator)
{
    struct _dynarr_ptr_ *dynarr = (struct _dynarr_ptr_ *)(allocator == NULL ? malloc(sizeof(struct _dynarr_ptr_)) : allocator->dynarr_alloc(sizeof(struct _dynarr_ptr_), 0));

    if (!dynarr)
        return NULL;

    dynarr->used = 0;
    dynarr->count = 0;
    dynarr->items = NULL;
    dynarr->allocator = allocator;

    return dynarr;
}

void dynarr_ptr_destroy(struct _dynarr_ptr_ *dynarr)
{
    if (!dynarr)
        return;

    if (dynarr->allocator)
        dynarr->allocator->dynarr_dealloc(dynarr->items, 1);
    else
        free(dynarr->items);

    dynarr->used = 0;
    dynarr->count = 0;
    dynarr->items = NULL;

    if (dynarr->allocator)
        dynarr->allocator->dynarr_dealloc(dynarr, 0);
    else
        free(dynarr);
}

int dynarr_ptr_resize(size_t new_count, struct _dynarr_ptr_ *dynarr)
{
    void **items = NULL;

    if (dynarr->allocator)
        items = (void **)dynarr->allocator->dynarr_realloc(dynarr->items, sizeof(void *) * new_count);
    else
        items = (void **)realloc(dynarr->items, sizeof(void *) * new_count);

    if (!items)
        return 1;

    for (size_t i = dynarr->count; i < new_count; i++)
    {
        items[i] = NULL;
    }

    dynarr->items = items;
    dynarr->count = new_count;

    return 0;
}

void dynarr_ptr_set(size_t index, void *value, struct _dynarr_ptr_ *dynarr)
{
    *DYNARR_PTR_POSITION(index, dynarr) = value;
}

int dynarr_ptr_insert(void *ptr, struct _dynarr_ptr_ *dynarr)
{
    if (dynarr->used >= dynarr->count && dynarr_ptr_resize(DYNARR_DETERMINATE_GROW(dynarr->count), dynarr))
        return 1;

    *(dynarr->items + (dynarr->used++)) = ptr;

    return 0;
}

void dynarr_ptr_move(size_t index, size_t from, size_t to, struct _dynarr_ptr_ *dynarr)
{
    for (size_t o = index, i = from; i < to; o++, i++)
        dynarr->items[o] = dynarr->items[i];
}

void dynarr_ptr_remove_index(size_t index, struct _dynarr_ptr_ *dynarr)
{
    if (index < dynarr->used - 1)
        dynarr_ptr_move(index, index + 1, dynarr->used, dynarr);

    if (dynarr->used - 1 > DYNARR_DEFAULT_GROW_SIZE && dynarr->used - 1 < dynarr->count / 2)
        dynarr_ptr_resize(dynarr->count / 2, dynarr);

    dynarr->used--;
}

void dynarr_ptr_remove_ptr(void *ptr, struct _dynarr_ptr_ *dynarr)
{
    for (size_t i = 0; i < dynarr->used; i++)
    {
        if (*(dynarr->items + i) == ptr)
        {
            dynarr_ptr_remove_index(i, dynarr);
            return;
        }
    }
}
#include "dynarr.h"

#include <stdio.h>
#include <limits.h>
#include <assert.h>

#define PRT_TEST_BEIGN() printf("%s...", __func__)
#define PRT_TEST_END() printf(" success!\n")

void test_dynarr_test_0(){
    PRT_TEST_BEIGN();

    char raw_values[dynarr_size()];
    DynArr *values = DYNARR_INIT_TYPE(raw_values, int, NULL);

    assert(dynarr_len(values) == 0);
    assert(dynarr_capacity(values) == 0);

    dynarr_deinit(values);

    PRT_TEST_END();
}

void test_dynarr_create_by_0(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE_BY(NULL, int, 21);

    assert(dynarr_len(values) == 0);
    assert(dynarr_capacity(values) % DYNARR_DEFAULT_GROW_SIZE == 0);

    dynarr_destroy(values);

    PRT_TEST_END();
}

void test_dynarr_set_at_0(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE(NULL, int);

    assert(DYNARR_SET_AT(values, 0, int, 9) == IDX_OUT_OF_BOUNDS_ERR_DYNARR_CODE);

    dynarr_destroy(values);

    PRT_TEST_END();
}

void test_dynarr_set_at_1(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE(NULL, int);

    assert(DYNARR_INSERT(values, int, 9) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(values, int, 8) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(values, int, 7) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(values, int, 6) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(values, int, 5) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(values, int, 4) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(values, int, 3) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(values, int, 2) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(values, int, 1) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(values, int, 0) == OK_DYNARR_CODE);

    assert(DYNARR_SET_AT(values, 4, int, 11) == OK_DYNARR_CODE);
    assert(DYNARR_GET_AS(values, int, 4) == 11);

    dynarr_destroy(values);

    PRT_TEST_END();
}

void test_dynarr_insert_0(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE(NULL, int);

    assert(DYNARR_INSERT(values, int, 5) == OK_DYNARR_CODE);
    assert(dynarr_len(values) == 1);
    assert(dynarr_capacity(values) == DYNARR_DEFAULT_GROW_SIZE);
    assert(DYNARR_GET_AS(values, int, 0) == 5);

    dynarr_destroy(values);

    PRT_TEST_END();
}

void test_dynarr_insert_1(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE(NULL, int);
    size_t itms_count = DYNARR_DEFAULT_GROW_SIZE;

    for (size_t i = 0; i < itms_count; i++){
        assert(DYNARR_INSERT(values, int, (int)(i + 1)) == OK_DYNARR_CODE);
    }

    assert(dynarr_len(values) == itms_count);
    assert(dynarr_capacity(values) == DYNARR_DEFAULT_GROW_SIZE);

    for (size_t i = 0; i < itms_count; i++){
        assert(DYNARR_GET_AS(values, int, i) == (int)(i + 1));
    }

    dynarr_destroy(values);

    PRT_TEST_END();
}

void test_dynarr_insert_2(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE(NULL, int);
    size_t itms_count = DYNARR_DEFAULT_GROW_SIZE + DYNARR_DEFAULT_GROW_SIZE / 2;

    for (size_t i = 0; i < itms_count; i++){
        assert(DYNARR_INSERT(values, int, (int)(i + 1)) == OK_DYNARR_CODE);
    }

    assert(dynarr_len(values) == itms_count);
    assert(dynarr_capacity(values) == DYNARR_DEFAULT_GROW_SIZE * 2);

    for (size_t i = 0; i < itms_count; i++){
        assert(DYNARR_GET_AS(values, int, i) == (int)(i + 1));
    }

    dynarr_destroy(values);

    PRT_TEST_END();
}

void test_dynarr_insert_at_0(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE(NULL, int);

    assert(DYNARR_INSERT_AT(values, 1, int, 5) == IDX_OUT_OF_BOUNDS_ERR_DYNARR_CODE);

    dynarr_destroy(values);

    PRT_TEST_END();
}

void test_dynarr_insert_at_1(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE(NULL, int);

    assert(DYNARR_INSERT_AT(values, 0, int, 5) == OK_DYNARR_CODE);
    assert(dynarr_len(values) == 1);
    assert(dynarr_capacity(values) == DYNARR_DEFAULT_GROW_SIZE);
    assert(DYNARR_GET_AS(values, int, 0) == 5);

    dynarr_destroy(values);

    PRT_TEST_END();
}

void test_dynarr_insert_at_2(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE(NULL, int);
    size_t itms_count = DYNARR_DEFAULT_GROW_SIZE;

    for (size_t i = 0; i < itms_count; i++){
        assert(DYNARR_INSERT(values, int, (int)(i + 1)) == OK_DYNARR_CODE);
    }

    assert(dynarr_len(values) == itms_count);
    assert(dynarr_capacity(values) == DYNARR_DEFAULT_GROW_SIZE);

    for (size_t i = 0; i < itms_count; i++){
        assert(DYNARR_SET_AT(values, i, int, (int)i) == OK_DYNARR_CODE);
    }

    assert(dynarr_len(values) == itms_count);
    assert(dynarr_capacity(values) == DYNARR_DEFAULT_GROW_SIZE);

    for (size_t i = 0; i < itms_count; i++){
        assert(DYNARR_GET_AS(values, int, i) == (int)i);
    }

    dynarr_destroy(values);

    PRT_TEST_END();
}

void test_dynarr_insert_at_3(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE(NULL, int);
    size_t itms_count = DYNARR_DEFAULT_GROW_SIZE + DYNARR_DEFAULT_GROW_SIZE / 2;

    for (size_t i = 0; i < itms_count; i++){
        assert(DYNARR_INSERT(values, int, (int)(i + 1)) == OK_DYNARR_CODE);
    }

    assert(dynarr_len(values) == itms_count);
    assert(dynarr_capacity(values) == DYNARR_DEFAULT_GROW_SIZE * 2);

    for (size_t i = 0; i < itms_count; i++){
        assert(DYNARR_SET_AT(values, i, int, (int)i) == OK_DYNARR_CODE);
    }

    assert(dynarr_len(values) == itms_count);
    assert(dynarr_capacity(values) == DYNARR_DEFAULT_GROW_SIZE * 2);

    for (size_t i = 0; i < itms_count; i++){
        assert(DYNARR_GET_AS(values, int, i) == (int)i);
    }

    dynarr_destroy(values);

    PRT_TEST_END();
}

void test_dynarr_append_0(){
    PRT_TEST_BEIGN();

    DynArr *a = DYNARR_CREATE_TYPE(NULL, int);
    DynArr *b = DYNARR_CREATE_TYPE(NULL, int);

    assert(dynarr_append(a, b) == DYNARR_EMPTY_ERR_DYNARR_CODE);

    dynarr_destroy(a);
    dynarr_destroy(b);

    PRT_TEST_END();
}

void test_dynarr_append_1(){
    PRT_TEST_BEIGN();

    DynArr *a = DYNARR_CREATE_TYPE(NULL, int);
    DynArr *b = DYNARR_CREATE_TYPE(NULL, int);

    DYNARR_INSERT(b, int, 2);
    DYNARR_INSERT(b, int, 3);
    DYNARR_INSERT(b, int, 5);
    DYNARR_INSERT(b, int, 7);
    DYNARR_INSERT(b, int, 11);
    DYNARR_INSERT(b, int, 13);
    DYNARR_INSERT(b, int, 17);
    DYNARR_INSERT(b, int, 23);

    assert(dynarr_append(a, b) == OK_DYNARR_CODE);
    assert(dynarr_len(a) == dynarr_len(b));

    for (size_t i = 0; i < dynarr_len(a); i++){
        int a_value = DYNARR_GET_AS(a, int, i);
        int b_value = DYNARR_GET_AS(b, int, i);

        assert(a_value == b_value);
    }

    dynarr_destroy(a);
    dynarr_destroy(b);

    PRT_TEST_END();
}

void test_dynarr_append_2(){
    PRT_TEST_BEIGN();

    DynArr *a = DYNARR_CREATE_TYPE(NULL, int);
    DynArr *b = DYNARR_CREATE_TYPE(NULL, int);
    DynArr *c = DYNARR_CREATE_TYPE(NULL, int);

    DYNARR_INSERT(b, int, 2);
    DYNARR_INSERT(b, int, 3);
    DYNARR_INSERT(b, int, 5);
    DYNARR_INSERT(b, int, 7);
    DYNARR_INSERT(b, int, 11);
    DYNARR_INSERT(b, int, 13);
    DYNARR_INSERT(b, int, 17);
    DYNARR_INSERT(b, int, 23);

    assert(dynarr_append(a, b) == OK_DYNARR_CODE);
    assert(dynarr_len(a) == dynarr_len(b));

    for (size_t i = 0; i < dynarr_len(a); i++){
        int a_value = DYNARR_GET_AS(a, int, i);
        int b_value = DYNARR_GET_AS(b, int, i);

        assert(a_value == b_value);
    }

    DYNARR_INSERT(c, int, 100);
    DYNARR_INSERT(c, int, 99);
    DYNARR_INSERT(c, int, 98);
    DYNARR_INSERT(c, int, 97);
    DYNARR_INSERT(c, int, 96);
    DYNARR_INSERT(c, int, 95);
    DYNARR_INSERT(c, int, 94);
    DYNARR_INSERT(c, int, 93);

    assert(dynarr_append(a, c) == OK_DYNARR_CODE);
    assert(dynarr_len(a) == dynarr_len(b) + dynarr_len(c));

    for (size_t i = dynarr_len(b); i < dynarr_len(a); i++){
        int a_value = DYNARR_GET_AS(a, int, i);
        int c_value = DYNARR_GET_AS(c, int, i - dynarr_len(b));

        assert(a_value == c_value);
    }

    dynarr_destroy(a);
    dynarr_destroy(b);
    dynarr_destroy(c);

    PRT_TEST_END();
}

void test_dynarr_join_0(){
    PRT_TEST_BEIGN();

    DynArr *a = DYNARR_CREATE_TYPE(NULL, char);
    DynArr *b = DYNARR_CREATE_TYPE(NULL, int);

    assert(DYNARR_INSERT(a, char, CHAR_MAX) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(b, int, INT_MAX) == OK_DYNARR_CODE);
    assert(dynarr_join(a, b, NULL, NULL) == SIZE_MISMATCH_ERR_DYNARR_CODE);

    dynarr_destroy(a);
    dynarr_destroy(b);

    PRT_TEST_END();
}

void test_dynarr_join_1(){
    PRT_TEST_BEIGN();

    DynArr *a = DYNARR_CREATE_TYPE(NULL, int);
    DynArr *b = DYNARR_CREATE_TYPE(NULL, int);
    DynArr *c = NULL;

    assert(DYNARR_INSERT(a, int, 1) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(a, int, 2) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(a, int, 3) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(a, int, 4) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(a, int, 5) == OK_DYNARR_CODE);

    assert(DYNARR_INSERT(b, int, 6) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(b, int, 7) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(b, int, 8) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(b, int, 9) == OK_DYNARR_CODE);
    assert(DYNARR_INSERT(b, int, 10) == OK_DYNARR_CODE);

    assert(dynarr_join(a, b, NULL, &c) == OK_DYNARR_CODE);

    assert(DYNARR_GET_AS(c, int, 0) == 1);
    assert(DYNARR_GET_AS(c, int, 1) == 2);
    assert(DYNARR_GET_AS(c, int, 2) == 3);
    assert(DYNARR_GET_AS(c, int, 3) == 4);
    assert(DYNARR_GET_AS(c, int, 4) == 5);
    assert(DYNARR_GET_AS(c, int, 5) == 6);
    assert(DYNARR_GET_AS(c, int, 6) == 7);
    assert(DYNARR_GET_AS(c, int, 7) == 8);
    assert(DYNARR_GET_AS(c, int, 8) == 9);
    assert(DYNARR_GET_AS(c, int, 9) == 10);

    dynarr_destroy(a);
    dynarr_destroy(b);
    dynarr_destroy(c);

    PRT_TEST_END();
}

void test_dynarr_remove_index_0(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE(NULL, int);

    assert(dynarr_remove_index(values, 0) == IDX_OUT_OF_BOUNDS_ERR_DYNARR_CODE);

    dynarr_destroy(values);

    PRT_TEST_END();
}

void test_dynarr_remove_index_1(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE(NULL, int);
    size_t itms_len = DYNARR_DEFAULT_GROW_SIZE;
    size_t idx_to_remove = DYNARR_DEFAULT_GROW_SIZE / 2;

    for (size_t i = 0; i < itms_len; i++){
        assert(DYNARR_INSERT(values, int, i + 1) == OK_DYNARR_CODE);
    }

    int value_to_remove = DYNARR_GET_AS(values, int, idx_to_remove);

    assert(dynarr_remove_index(values, idx_to_remove) == OK_DYNARR_CODE);
    assert(dynarr_len(values) == itms_len - 1);
    assert(dynarr_capacity(values) == DYNARR_DEFAULT_GROW_SIZE);

    for (size_t i = 0; i < itms_len - 1; i++){
        assert(DYNARR_GET_AS(values, int, i) != value_to_remove);
    }

    dynarr_destroy(values);

    PRT_TEST_END();
}

void test_dynarr_remove_index_2(){
    PRT_TEST_BEIGN();

    DynArr *values = DYNARR_CREATE_TYPE(NULL, int);
    size_t itms_len = DYNARR_DEFAULT_GROW_SIZE;

    for (size_t i = 0; i < itms_len; i++){
        assert(DYNARR_INSERT(values, int, i + 1) == OK_DYNARR_CODE);
    }

    for (size_t i = 0; i < itms_len; i++){
        assert(dynarr_remove_index(values, 0) == OK_DYNARR_CODE);
    }

    assert(dynarr_len(values) == 0);
    assert(dynarr_capacity(values) == DYNARR_DEFAULT_GROW_SIZE);

    dynarr_destroy(values);

    PRT_TEST_END();
}

int main(void) {
    test_dynarr_test_0();
    test_dynarr_create_by_0();

    test_dynarr_set_at_0();
    test_dynarr_set_at_1();

    test_dynarr_insert_0();
    test_dynarr_insert_1();
    test_dynarr_insert_2();

    test_dynarr_insert_at_0();
    test_dynarr_insert_at_1();
    test_dynarr_insert_at_2();
    test_dynarr_insert_at_3();

    test_dynarr_append_0();
    test_dynarr_append_1();
    test_dynarr_append_2();

    test_dynarr_join_0();
    test_dynarr_join_1();

    test_dynarr_remove_index_0();
    test_dynarr_remove_index_1();
    test_dynarr_remove_index_2();

    return 0;
}
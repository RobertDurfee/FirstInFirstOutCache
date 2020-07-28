#include <stdio.h>
#include <assert.h>
#include "tests.h"
#include "cache.h"

void reset(void) {
    for (unsigned int i = 0; i < NODE_POOL_SIZE + 1; i++) {
        node_pool[i].key = 0;
        node_pool[i].tag = 0;
        node_pool[i].is_first = false;
        node_pool[i].value.value = 0;
        node_pool[i].len = 0;
    }
    next_node_ptr = 1;
    for (unsigned int i = 0; i < NODE_CACHE_SIZE; i++) {
        node_cache[i] = 0;
    }
}

void test_1(void) {
    value_t vs[3] = { { 0x00 }, { 0x01 }, { 0x02 } };
    for (unsigned int i = 0x00; i < 0x03; i++) {
        put(0x00, 0xF0, &vs[i]);
    }
    assert(next_node_ptr == 0x04);
    node_ptr_t node_ptr = node_cache[0x00];
    assert(node_ptr == 0x01);
    assert(node_pool[node_ptr].key == 0x00);
    assert(node_pool[node_ptr].tag == 0xF0);
    assert(node_pool[node_ptr].is_first == true);
    assert(node_pool[node_ptr].value.value == 0x00);
    assert(node_pool[node_ptr].len == 0x03);
    node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
    if (!node_ptr) node_ptr++;
    for (unsigned int i = 0x01; i < 0x03; i++) {
        assert(node_pool[node_ptr].is_first == false);
        assert(node_pool[node_ptr].value.value == i);
        node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
        if (!node_ptr) node_ptr++;
    }
    reset();
}

void test_2(void) {
    value_t vs1[8] = { { 0x00 }, { 0x01 }, { 0x02 }, { 0x03 }, { 0x04 }, { 0x05 }, { 0x06 }, { 0x07 } };
    for (unsigned int i = 0x00; i < 0x08; i++) {
        put(0x00, 0xF0, &vs1[i]);
    }
    assert(next_node_ptr == 0x09);
    node_ptr_t node_ptr = node_cache[0x00];
    assert(node_ptr == 0x01);
    assert(node_pool[node_ptr].key == 0x00);
    assert(node_pool[node_ptr].tag == 0xF0);
    assert(node_pool[node_ptr].is_first == true);
    assert(node_pool[node_ptr].value.value == 0x00);
    assert(node_pool[node_ptr].len == 0x08);
    node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
    if (!node_ptr) node_ptr++;
    for (unsigned int i = 0x01; i < 0x08; i++) {
        assert(node_pool[node_ptr].is_first == false);
        assert(node_pool[node_ptr].value.value == i);
        node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
        if (!node_ptr) node_ptr++;
    }
    value_t vs2[7] = { { 0x08 }, { 0x09 }, { 0x0A }, { 0x0B }, { 0x0C }, { 0x0D }, { 0x0E } };
    for (unsigned int i = 0x00; i < 0x07; i++) {
        put(0x01, 0xF1, &vs2[i]);
    }
    assert(next_node_ptr == 0x01);
    node_ptr = node_cache[0x01];
    assert(node_ptr == 0x09);
    assert(node_pool[node_ptr].key == 0x01);
    assert(node_pool[node_ptr].tag == 0xF1);
    assert(node_pool[node_ptr].is_first == true);
    assert(node_pool[node_ptr].value.value == 0x08);
    assert(node_pool[node_ptr].len == 0x07);
    node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
    if (!node_ptr) node_ptr++;
    for (unsigned int i = 0x01; i < 0x07; i++) {
        assert(node_pool[node_ptr].is_first == false);
        assert(node_pool[node_ptr].value.value == i + 0x08);
        node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
        if (!node_ptr) node_ptr++;
    }
    node_ptr = node_cache[0x00];
    assert(node_ptr == 0x01);
    assert(node_pool[node_ptr].key == 0x00);
    assert(node_pool[node_ptr].tag == 0xF0);
    assert(node_pool[node_ptr].is_first == true);
    assert(node_pool[node_ptr].value.value == 0x00);
    assert(node_pool[node_ptr].len == 0x08);
    node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
    if (!node_ptr) node_ptr++;
    for (unsigned int i = 0x01; i < 0x08; i++) {
        assert(node_pool[node_ptr].is_first == false);
        assert(node_pool[node_ptr].value.value == i);
        node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
        if (!node_ptr) node_ptr++;
    }
    reset();
}

void test_3(void) {
    value_t vs1[8] = { { 0x00 }, { 0x01 }, { 0x02 }, { 0x03 }, { 0x04 }, { 0x05 }, { 0x06 }, { 0x07 } };
    for (unsigned int i = 0x00; i < 0x08; i++) {
        put(0x00, 0xF0, &vs1[i]);
    }
    assert(next_node_ptr == 0x09);
    node_ptr_t node_ptr = node_cache[0x00];
    assert(node_ptr == 0x01);
    assert(node_pool[node_ptr].key == 0x00);
    assert(node_pool[node_ptr].tag == 0xF0);
    assert(node_pool[node_ptr].is_first == true);
    assert(node_pool[node_ptr].value.value == 0x00);
    assert(node_pool[node_ptr].len == 0x08);
    node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
    if (!node_ptr) node_ptr++;
    for (unsigned int i = 0x01; i < 0x08; i++) {
        assert(node_pool[node_ptr].is_first == false);
        assert(node_pool[node_ptr].value.value == i);
        node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
        if (!node_ptr) node_ptr++;
    }
    value_t vs2[8] = { { 0x08 }, { 0x09 }, { 0x0A }, { 0x0B }, { 0x0C }, { 0x0D }, { 0x0E }, { 0x0F } };
    for (unsigned int i = 0x00; i < 0x08; i++) {
        put(0x01, 0xF1, &vs2[i]);
    }
    assert(next_node_ptr == 0x02);
    node_ptr = node_cache[0x01];
    assert(node_ptr == 0x09);
    assert(node_pool[node_ptr].key == 0x01);
    assert(node_pool[node_ptr].tag == 0xF1);
    assert(node_pool[node_ptr].is_first == true);
    assert(node_pool[node_ptr].value.value == 0x08);
    assert(node_pool[node_ptr].len == 0x08);
    node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
    if (!node_ptr) node_ptr++;
    for (unsigned int i = 0x01; i < 0x08; i++) {
        assert(node_pool[node_ptr].is_first == false);
        assert(node_pool[node_ptr].value.value == i + 0x08);
        node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
        if (!node_ptr) node_ptr++;
    }
    node_ptr = node_cache[0x00];
    assert(node_ptr == 0);
    reset();
}

void test_4(void) {
    value_t vs1[7] = { { 0x00 }, { 0x01 }, { 0x02 }, { 0x03 }, { 0x04 }, { 0x05 }, { 0x06 } };
    for (unsigned int i = 0x00; i < 0x07; i++) {
        put(0x00, 0xF0, &vs1[i]);
    }
    assert(next_node_ptr == 0x08);
    node_ptr_t node_ptr = node_cache[0x00];
    assert(node_ptr == 0x01);
    assert(node_pool[node_ptr].key == 0x00);
    assert(node_pool[node_ptr].tag == 0xF0);
    assert(node_pool[node_ptr].is_first == true);
    assert(node_pool[node_ptr].value.value == 0x00);
    assert(node_pool[node_ptr].len == 0x07);
    node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
    if (!node_ptr) node_ptr++;
    for (unsigned int i = 0x01; i < 0x07; i++) {
        assert(node_pool[node_ptr].is_first == false);
        assert(node_pool[node_ptr].value.value == i);
        node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
        if (!node_ptr) node_ptr++;
    }
    value_t vs2[7] = { { 0x07 }, { 0x08 }, { 0x09 }, { 0x0A }, { 0x0B }, { 0x0C }, { 0x0D } };
    for (unsigned int i = 0x00; i < 0x07; i++) {
        put(0x00, 0xE0, &vs2[i]);
    }
    assert(next_node_ptr == 0x0F);
    node_ptr = node_cache[0x00];
    assert(node_ptr == 0x08);
    assert(node_pool[node_ptr].key == 0x00);
    assert(node_pool[node_ptr].tag == 0xE0);
    assert(node_pool[node_ptr].is_first == true);
    assert(node_pool[node_ptr].value.value == 0x07);
    assert(node_pool[node_ptr].len == 0x07);
    node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
    if (!node_ptr) node_ptr++;
    for (unsigned int i = 0x01; i < 0x07; i++) {
        assert(node_pool[node_ptr].is_first == false);
        assert(node_pool[node_ptr].value.value == i + 0x07);
        node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
        if (!node_ptr) node_ptr++;
    }
    value_t vs3[2] = { { 0x0E }, { 0x0F } };
    for (unsigned int i = 0x00; i < 0x02; i++) {
        put(0x01, 0xF1, &vs3[i]);
    }
    assert(next_node_ptr == 0x02);
    node_ptr = node_cache[0x01];
    assert(node_ptr == 0x0F);
    assert(node_pool[node_ptr].key == 0x01);
    assert(node_pool[node_ptr].tag == 0xF1);
    assert(node_pool[node_ptr].is_first == true);
    assert(node_pool[node_ptr].value.value == 0x0E);
    assert(node_pool[node_ptr].len == 0x02);
    node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
    if (!node_ptr) node_ptr++;
    for (unsigned int i = 0x01; i < 0x02; i++) {
        assert(node_pool[node_ptr].is_first == false);
        assert(node_pool[node_ptr].value.value == i + 0x0E);
        node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
        if (!node_ptr) node_ptr++;
    }
    node_ptr = node_cache[0x00];
    assert(node_ptr == 0x08);
    assert(node_pool[node_ptr].key == 0x00);
    assert(node_pool[node_ptr].tag == 0xE0);
    assert(node_pool[node_ptr].is_first == true);
    assert(node_pool[node_ptr].value.value == 0x07);
    assert(node_pool[node_ptr].len == 0x07);
    node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
    if (!node_ptr) node_ptr++;
    for (unsigned int i = 0x01; i < 0x07; i++) {
        assert(node_pool[node_ptr].is_first == false);
        assert(node_pool[node_ptr].value.value == i + 0x07);
        node_ptr = (node_ptr + 1) % (NODE_POOL_SIZE + 1);
        if (!node_ptr) node_ptr++;
    }
    reset();
}

void run_tests(void) {
    printf("Running test_1 ...\n");
    test_1();
    printf("               ... Passed\n");

    printf("Running test_2 ...\n");
    test_2();
    printf("               ... Passed\n");

    printf("Running test_3 ...\n");
    test_3();
    printf("               ... Passed\n");

    printf("Running test_4 ...\n");
    test_4();
    printf("               ... Passed\n");
}

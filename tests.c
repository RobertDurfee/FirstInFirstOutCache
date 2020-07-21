#include <stdio.h>
#include <assert.h>
#include "tests.h"
#include "cache.h"

void reset(void) {
    for (unsigned int i = 0; i < POOL_SIZE + 1; i++) {
        POOL[i].tag = 0;
        POOL[i].key = 0;
        POOL[i].state = INVALID;
        POOL[i].value.value = 0;
        POOL[i].len = 0;
    }
    next_kv = 1;
    for (unsigned int i = 0; i < CACHE_SIZE; i++) {
        CACHE[i] = 0;
    }
}

void test_1(void) {
    struct Value vs[3] = { { 0x00 }, { 0x01 }, { 0x02 } };
    for (unsigned int i = 0x00; i < 0x03; i++) {
        put(0xF0, 0x00, &vs[i]);
    }
    assert(next_kv == 0x04);
    kv_ptr kv = CACHE[0x00];
    assert(kv == 0x01);
    assert(POOL[kv].tag == 0xF0);
    assert(POOL[kv].key == 0x00);
    assert(POOL[kv].state == VALID);
    assert(POOL[kv].value.value == 0x00);
    assert(POOL[kv].len == 0x03);
    kv = (kv + 1) % (POOL_SIZE + 1);
    if (!kv) kv++;
    for (unsigned int i = 0x01; i < 0x03; i++) {
        assert(POOL[kv].state == INVALID);
        assert(POOL[kv].value.value == i);
        kv = (kv + 1) % (POOL_SIZE + 1);
        if (!kv) kv++;
    }
    reset();
}

void test_2(void) {
    struct Value vs1[8] = { { 0x00 }, { 0x01 }, { 0x02 }, { 0x03 }, { 0x04 }, { 0x05 }, { 0x06 }, { 0x07 } };
    for (unsigned int i = 0x00; i < 0x08; i++) {
        put(0xF0, 0x00, &vs1[i]);
    }
    assert(next_kv == 0x09);
    kv_ptr kv = CACHE[0x00];
    assert(kv == 0x01);
    assert(POOL[kv].tag == 0xF0);
    assert(POOL[kv].key == 0x00);
    assert(POOL[kv].state == VALID);
    assert(POOL[kv].value.value == 0x00);
    assert(POOL[kv].len == 0x08);
    kv = (kv + 1) % (POOL_SIZE + 1);
    if (!kv) kv++;
    for (unsigned int i = 0x01; i < 0x08; i++) {
        assert(POOL[kv].state == INVALID);
        assert(POOL[kv].value.value == i);
        kv = (kv + 1) % (POOL_SIZE + 1);
        if (!kv) kv++;
    }
    struct Value vs2[7] = { { 0x08 }, { 0x09 }, { 0x0A }, { 0x0B }, { 0x0C }, { 0x0D }, { 0x0E } };
    for (unsigned int i = 0x00; i < 0x07; i++) {
        put(0xF1, 0x01, &vs2[i]);
    }
    assert(next_kv == 0x01);
    kv = CACHE[0x01];
    assert(kv == 0x09);
    assert(POOL[kv].tag == 0xF1);
    assert(POOL[kv].key == 0x01);
    assert(POOL[kv].state == VALID);
    assert(POOL[kv].value.value == 0x08);
    assert(POOL[kv].len == 0x07);
    kv = (kv + 1) % (POOL_SIZE + 1);
    if (!kv) kv++;
    for (unsigned int i = 0x01; i < 0x07; i++) {
        assert(POOL[kv].state == INVALID);
        assert(POOL[kv].value.value == i + 0x08);
        kv = (kv + 1) % (POOL_SIZE + 1);
        if (!kv) kv++;
    }
    kv = CACHE[0x00];
    assert(kv == 0x01);
    assert(POOL[kv].tag == 0xF0);
    assert(POOL[kv].key == 0x00);
    assert(POOL[kv].state == VALID);
    assert(POOL[kv].value.value == 0x00);
    assert(POOL[kv].len == 0x08);
    kv = (kv + 1) % (POOL_SIZE + 1);
    if (!kv) kv++;
    for (unsigned int i = 0x01; i < 0x08; i++) {
        assert(POOL[kv].state == INVALID);
        assert(POOL[kv].value.value == i);
        kv = (kv + 1) % (POOL_SIZE + 1);
        if (!kv) kv++;
    }
    reset();
}

void test_3(void) {
    struct Value vs1[8] = { { 0x00 }, { 0x01 }, { 0x02 }, { 0x03 }, { 0x04 }, { 0x05 }, { 0x06 }, { 0x07 } };
    for (unsigned int i = 0x00; i < 0x08; i++) {
        put(0xF0, 0x00, &vs1[i]);
    }
    assert(next_kv == 0x09);
    kv_ptr kv = CACHE[0x00];
    assert(kv == 0x01);
    assert(POOL[kv].tag == 0xF0);
    assert(POOL[kv].key == 0x00);
    assert(POOL[kv].state == VALID);
    assert(POOL[kv].value.value == 0x00);
    assert(POOL[kv].len == 0x08);
    kv = (kv + 1) % (POOL_SIZE + 1);
    if (!kv) kv++;
    for (unsigned int i = 0x01; i < 0x08; i++) {
        assert(POOL[kv].state == INVALID);
        assert(POOL[kv].value.value == i);
        kv = (kv + 1) % (POOL_SIZE + 1);
        if (!kv) kv++;
    }
    struct Value vs2[8] = { { 0x08 }, { 0x09 }, { 0x0A }, { 0x0B }, { 0x0C }, { 0x0D }, { 0x0E }, { 0x0F } };
    for (unsigned int i = 0x00; i < 0x08; i++) {
        put(0xF1, 0x01, &vs2[i]);
    }
    assert(next_kv == 0x02);
    kv = CACHE[0x01];
    assert(kv == 0x09);
    assert(POOL[kv].tag == 0xF1);
    assert(POOL[kv].key == 0x01);
    assert(POOL[kv].state == VALID);
    assert(POOL[kv].value.value == 0x08);
    assert(POOL[kv].len == 0x08);
    kv = (kv + 1) % (POOL_SIZE + 1);
    if (!kv) kv++;
    for (unsigned int i = 0x01; i < 0x08; i++) {
        assert(POOL[kv].state == INVALID);
        assert(POOL[kv].value.value == i + 0x08);
        kv = (kv + 1) % (POOL_SIZE + 1);
        if (!kv) kv++;
    }
    kv = CACHE[0x00];
    assert(kv == NONE);
    reset();
}

void test_4(void) {
    struct Value vs1[7] = { { 0x00 }, { 0x01 }, { 0x02 }, { 0x03 }, { 0x04 }, { 0x05 }, { 0x06 } };
    for (unsigned int i = 0x00; i < 0x07; i++) {
        put(0xF0, 0x00, &vs1[i]);
    }
    assert(next_kv == 0x08);
    kv_ptr kv = CACHE[0x00];
    assert(kv == 0x01);
    assert(POOL[kv].tag == 0xF0);
    assert(POOL[kv].key == 0x00);
    assert(POOL[kv].state == VALID);
    assert(POOL[kv].value.value == 0x00);
    assert(POOL[kv].len == 0x07);
    kv = (kv + 1) % (POOL_SIZE + 1);
    if (!kv) kv++;
    for (unsigned int i = 0x01; i < 0x07; i++) {
        assert(POOL[kv].state == INVALID);
        assert(POOL[kv].value.value == i);
        kv = (kv + 1) % (POOL_SIZE + 1);
        if (!kv) kv++;
    }
    struct Value vs2[7] = { { 0x07 }, { 0x08 }, { 0x09 }, { 0x0A }, { 0x0B }, { 0x0C }, { 0x0D } };
    for (unsigned int i = 0x00; i < 0x07; i++) {
        put(0xE0, 0x00, &vs2[i]);
    }
    assert(next_kv == 0x0F);
    kv = CACHE[0x00];
    assert(kv == 0x08);
    assert(POOL[kv].tag == 0xE0);
    assert(POOL[kv].key == 0x00);
    assert(POOL[kv].state == VALID);
    assert(POOL[kv].value.value == 0x07);
    assert(POOL[kv].len == 0x07);
    kv = (kv + 1) % (POOL_SIZE + 1);
    if (!kv) kv++;
    for (unsigned int i = 0x01; i < 0x07; i++) {
        assert(POOL[kv].state == INVALID);
        assert(POOL[kv].value.value == i + 0x07);
        kv = (kv + 1) % (POOL_SIZE + 1);
        if (!kv) kv++;
    }
    struct Value vs3[2] = { { 0x0E }, { 0x0F } };
    for (unsigned int i = 0x00; i < 0x02; i++) {
        put(0xF1, 0x01, &vs3[i]);
    }
    assert(next_kv == 0x02);
    kv = CACHE[0x01];
    assert(kv == 0x0F);
    assert(POOL[kv].tag == 0xF1);
    assert(POOL[kv].key == 0x01);
    assert(POOL[kv].state == VALID);
    assert(POOL[kv].value.value == 0x0E);
    assert(POOL[kv].len == 0x02);
    kv = (kv + 1) % (POOL_SIZE + 1);
    if (!kv) kv++;
    for (unsigned int i = 0x01; i < 0x02; i++) {
        assert(POOL[kv].state == INVALID);
        assert(POOL[kv].value.value == i + 0x0E);
        kv = (kv + 1) % (POOL_SIZE + 1);
        if (!kv) kv++;
    }
    kv = CACHE[0x00];
    assert(kv == 0x08);
    assert(POOL[kv].tag == 0xE0);
    assert(POOL[kv].key == 0x00);
    assert(POOL[kv].state == VALID);
    assert(POOL[kv].value.value == 0x07);
    assert(POOL[kv].len == 0x07);
    kv = (kv + 1) % (POOL_SIZE + 1);
    if (!kv) kv++;
    for (unsigned int i = 0x01; i < 0x07; i++) {
        assert(POOL[kv].state == INVALID);
        assert(POOL[kv].value.value == i + 0x07);
        kv = (kv + 1) % (POOL_SIZE + 1);
        if (!kv) kv++;
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

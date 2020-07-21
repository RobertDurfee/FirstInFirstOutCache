#ifndef CACHE_H
#define CACHE_H

struct Value {
    unsigned int value;
};

typedef unsigned int kv_ptr;

enum State {
    INVALID,
    VALID,
};

struct KV {
    unsigned int tag;
    unsigned int key;
    enum State state;
    struct Value value;
    unsigned int len;
};

#define POOL_SIZE 0x0F

extern struct KV POOL[POOL_SIZE + 1];

extern kv_ptr next_kv;

#define CACHE_SIZE 0x0F

extern kv_ptr CACHE[CACHE_SIZE];

void put(unsigned int t, unsigned int k, struct Value * v);

#define NONE 0

#endif // CACHE_H

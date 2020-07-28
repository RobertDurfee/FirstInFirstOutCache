#ifndef CACHE_H
#define CACHE_H

#define NODE_POOL_SIZE 0x0F
#define NODE_CACHE_SIZE 0x0F

typedef enum { false, true } bool;
typedef unsigned int node_ptr_t;
typedef unsigned int key_t;
typedef unsigned long tag_t;

typedef struct {
    unsigned int value;
} value_t;

typedef struct {
    tag_t tag;
    key_t key;
    bool is_first;
    value_t value;
    unsigned int len;
} node_t;

extern node_t node_pool[NODE_POOL_SIZE + 1];
extern node_ptr_t node_cache[NODE_CACHE_SIZE];
extern node_ptr_t next_node_ptr;

// only this function should be used to mutate the cache
void put(key_t key, tag_t tag, value_t * value);

#endif // CACHE_H

#include <string.h>
#include "cache.h"

struct KV POOL[POOL_SIZE + 1];
kv_ptr next_kv = 1;
kv_ptr CACHE[CACHE_SIZE];

// insert a sequence of values into the cache with the given tag and key
void insert(unsigned int t, unsigned int k, struct Value * vs, unsigned int n) {

    // if kv about to be overwritten is valid and in the cache, clear the cache entry
    if (POOL[next_kv].state == VALID && POOL[CACHE[POOL[next_kv].key]].tag == POOL[next_kv].tag) {
        CACHE[POOL[next_kv].key] = NONE;
    }

    // set kv header information
    POOL[next_kv].tag = t;
    POOL[next_kv].key = k;
    POOL[next_kv].state = VALID;
    memcpy(&POOL[next_kv].value, &vs[0], sizeof(struct Value));
    POOL[next_kv].len = n;

    // insert into cache, don't care about overwrites (this is handled on insert)
    CACHE[k] = next_kv;

    // get next kv from pool
    next_kv = (next_kv + 1) % (POOL_SIZE + 1);

    // zero is a reserved pointer
    if (!next_kv) next_kv++;

    // insert remaining values, don't care about header information
    for (unsigned int i = 1; i < n; i++) {

        // if kv about to be overwritten is valid and in the cache, clear the cache entry
        if (POOL[next_kv].state == VALID) {
            if (POOL[CACHE[POOL[next_kv].key]].tag == POOL[next_kv].tag) {
                CACHE[POOL[next_kv].key] = NONE;
            }

            // clear the state either way
            POOL[next_kv].state = INVALID;
        }

        // copy the value
        memcpy(&POOL[next_kv].value, &vs[i], sizeof(struct Value));

        // get next kv from pool
        next_kv = (next_kv + 1) % (POOL_SIZE + 1);

        // zero is a reserved pointer
        if (!next_kv) next_kv++;
    }
}

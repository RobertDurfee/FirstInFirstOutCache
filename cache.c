#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "cache.h"

struct KV POOL[POOL_SIZE + 1];
kv_ptr next_kv = 1;
kv_ptr CACHE[CACHE_SIZE];

void put(unsigned int t, unsigned int k, struct Value * v) {

    // if the cache has this key with a matching tag
    if (CACHE[k] != NONE && POOL[CACHE[k]].tag == t) {

        // get the head from the cache
        kv_ptr head = CACHE[k];

        // make sure these are consecutive additions to the same cache entry
        // assert(next_kv == (head + POOL[head].len) ? (head + POOL[head].len) % (POOL_SIZE + 1) : (head + POOL[head].len) % (POOL_SIZE + 1) + 1);

        // this cache entry is longer now
        POOL[head].len++;

        // if kv about to be overwritten is valid ... 
        if (POOL[next_kv].state == VALID) {

            // ... and in the cache, clear the cache entry
            if (POOL[CACHE[POOL[next_kv].key]].tag == POOL[next_kv].tag) {
                CACHE[POOL[next_kv].key] = NONE;
            }

            // clear the state either way
            POOL[next_kv].state = INVALID;
        }

        // copy the value
        memcpy(&POOL[next_kv].value, v, sizeof(struct Value));

    // otherwise this corresponds to an empty cache entry
    } else {

        // if kv about to be overwritten is valid and in the cache, clear the cache entry
        if (POOL[next_kv].state == VALID && POOL[CACHE[POOL[next_kv].key]].tag == POOL[next_kv].tag) {
            CACHE[POOL[next_kv].key] = NONE;
        }

        // set kv header information
        POOL[next_kv].tag = t;
        POOL[next_kv].key = k;
        POOL[next_kv].state = VALID;
        memcpy(&POOL[next_kv].value, v, sizeof(struct Value));
        POOL[next_kv].len = 1;

        // insert into cache, don't care about overwrites (this is handled on insert)
        CACHE[k] = next_kv;
    }

    // get next kv from pool
    next_kv = (next_kv + 1) % (POOL_SIZE + 1);

    // zero is a reserved pointer
    if (!next_kv) next_kv++;
}

#include <string.h>
#include "cache.h"

node_t node_pool[NODE_POOL_SIZE + 1];
node_ptr_t next_node_ptr = 1;
node_ptr_t node_cache[NODE_CACHE_SIZE];

void put(key_t key, tag_t tag, value_t * value) {
    // if the cache has this key with a matching tag
    if (node_cache[key] != 0 && node_pool[node_cache[key]].tag == tag) {
        // get the first node from the cache
        node_ptr_t first_node_ptr = node_cache[key];
        // this cache entry is longer now
        node_pool[first_node_ptr].len++;
        // if node about to be overwritten is first ... 
        if (node_pool[next_node_ptr].is_first) {
            // ... and in the cache, clear the cache entry
            if (node_cache[node_pool[next_node_ptr].key] == next_node_ptr) {
                node_cache[node_pool[next_node_ptr].key] = 0;
            }
            // unset as first either way
            node_pool[next_node_ptr].is_first = false;
        }
        // copy the value
        memcpy(&node_pool[next_node_ptr].value, value, sizeof(value_t));
    // otherwise this corresponds to an empty cache entry
    } else {
        // if node about to be overwritten is first and in the cache, clear the cache entry
        if (node_pool[next_node_ptr].is_first && node_cache[node_pool[next_node_ptr].key] == next_node_ptr) {
            node_cache[node_pool[next_node_ptr].key] = 0;
        }
        // set kv header information
        node_pool[next_node_ptr].tag = tag;
        node_pool[next_node_ptr].key = key;
        node_pool[next_node_ptr].is_first = true;
        memcpy(&node_pool[next_node_ptr].value, value, sizeof(value_t));
        node_pool[next_node_ptr].len = 1;
        // insert into cache, don't care about overwrites (this is handled on insert)
        node_cache[key] = next_node_ptr;
    }
    // get next kv from pool
    next_node_ptr = (next_node_ptr + 1) % (NODE_POOL_SIZE + 1);
    // zero is a reserved pointer
    if (!next_node_ptr) next_node_ptr++;
}

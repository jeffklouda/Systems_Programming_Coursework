/* fnv.c: fnv hash function */

#include "map.h"

// http://isthe.com/chongo/tech/comp/fnv/

#define FNV_OFFSET_BASIS    (0xcbf29ce484222325ULL)
#define FNV_PRIME           (0x100000001b3ULL)

/**
 * Compute FNV-1 hash.
 * @param   d               Data to hash.
 * @param   n               Number of bytes in data.
 * @return  Computed hash.
 */
uint64_t	fnv_hash(const void *d, size_t n) {
    uint8_t* p = (uint8_t*) d;
    uint64_t hash = FNV_OFFSET_BASIS;
    for (size_t i = 0; i < n; i++) {
        hash = hash ^ (p[i]);
        hash = hash * FNV_PRIME;
    }
    return hash;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

/* map.c: separate chaining hash table */

#include "map.h"
#include <string.h>

/**
 * Create map data structure.
 * @param   capacity        Number of buckets in the hash table.
 * @param   load_factor     Maximum load factor before resizing.
 * @return  Allocated Map structure.
 */
Map *	        map_create(size_t capacity, double load_factor) {
    
    Map* newMap = calloc(1, sizeof(Map));
    
    if (!newMap)
        return NULL;

    newMap->size = 0;
    if (capacity == 0)
        capacity = DEFAULT_CAPACITY;
    newMap->capacity = capacity;
    
    if (load_factor <= 0)
        load_factor = DEFAULT_LOAD_FACTOR;
    newMap->load_factor = load_factor;
    
    newMap->buckets = calloc (newMap->capacity, sizeof(Entry));
    return newMap;
}

/**
 * Delete map data structure.
 * @param   m               Map data structure.
 * @return  NULL.
 */
Map *	        map_delete(Map *m) {
    for (size_t i = 0; i < m->capacity; i++) {
        entry_delete(m->buckets[i].next, true);
        free(m->buckets[i].key);
    }
    free(m->buckets);
    free(m);
    return NULL;
}

/**
 * Insert or update entry into map data structure.
 * @param   m               Map data structure.
 * @param   key             Entry's key.
 * @param   value           Entry's value.
 * @param   type            Entry's value's type.
 */
void            map_insert(Map *m, const char *key, const Value value, Type type) {
    size_t bucket = fnv_hash(key, strlen(key)) % m->capacity;
    Entry* existingEntry = map_search(m, key);
    if (!existingEntry) { 
        m->buckets[bucket].next = entry_create(key, value, 
            m->buckets[bucket].next, type);
        m->size++;
    }
    else {
        entry_update(existingEntry, value, type);
    }
    if ((double)(m->size / m->capacity) >= m->load_factor) {
        map_resize(m, m->capacity * 2);
    }
}

/**
 * Search map data structure by key.
 * @param   m               Map data structure.
 * @param   key             Key of the entry to search for.
 * @param   Pointer to the entry with the specified key (or NULL if not found).
 */
Entry *         map_search(Map *m, const char *key) {
    size_t bucket = fnv_hash(key, strlen(key)) % m->capacity;
    Entry* tempEntry = m->buckets[bucket].next;
    while (tempEntry) {
        if (!strcmp(tempEntry->key, key)) {
            return tempEntry;
        }
        tempEntry = tempEntry->next;
    }
    return NULL;
}

/**
 * Remove entry from map data structure with specified key.
 * @param   m               Map data structure.
 * @param   key             Key of the entry to remove.
 * return   Whether or not the removal was successful.
 */
bool            map_remove(Map *m, const char *key) {
    size_t bucket = fnv_hash(key, strlen(key)) % m->capacity;
    if (m->buckets[bucket].next) {
        Entry* tempEntry = m->buckets[bucket].next;
        Entry* removeEntry;
        if (!strcmp(m->buckets[bucket].next->key, key)) {
            removeEntry = m->buckets[bucket].next;
            m->buckets[bucket].next = removeEntry->next;
            entry_delete(removeEntry, false);
            m->size--;
            return true;
        }
        while (tempEntry->next) {
            if (!strcmp(tempEntry->next->key, key)) {
                removeEntry = tempEntry->next;
                tempEntry->next = tempEntry->next->next;
                entry_delete(removeEntry, false);
                m->size--;
                return true;
            }
            tempEntry = tempEntry->next;
        }   
    }
    return false;
}

/**
 * Dump all the entries in the map data structure.
 * @param   m               Map data structure.
 * @param   stream          File stream to write to.
 * @param   mode            Dump mode to use.
 */
void		map_dump(Map *m, FILE *stream, const DumpMode mode) {
    Entry* dumpEntry;
    for (size_t i = 0; i < m->capacity; i++) {
        if (m->buckets[i].next) {
            dumpEntry = m->buckets[i].next;
            while (dumpEntry) {
                entry_dump(dumpEntry, stream, mode);
                dumpEntry = dumpEntry->next;
            }
        }
    }
}

/**
 * Resize the map data structure.
 * @param   m               Map data structure.
 * @param   new_capacity    New capacity for the map data structure.
 */
void            map_resize(Map *m, size_t new_capacity) {
    Entry* old_buckets = m->buckets;
    size_t old_capacity = m->capacity;
    Entry* new_buckets = calloc(new_capacity, sizeof(Entry));
    m->buckets = new_buckets;
    m->capacity = new_capacity;
    for (int i = 0; i < old_capacity; i++) {
        
        if (old_buckets[i].next) {
            
            Entry* addEntry = old_buckets[i].next;
            size_t new_bucket;
            
            while (addEntry) {
                Entry* tempEntry = addEntry->next;
                new_bucket = fnv_hash(addEntry->key, 
                    strlen(addEntry->key)) % new_capacity;
                addEntry->next = m->buckets[new_bucket].next;
                m->buckets[new_bucket].next = addEntry;
                addEntry = tempEntry;
            }
        }
    }
    free(old_buckets);
}

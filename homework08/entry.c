/* entry.c: map entry */

#include "map.h"

/**
 * Create entry structure.
 * @param   key             Entry's key.
 * @param   value           Entry's value.
 * @param   next            Reference to next entry.
 * @param   type            Entry's value's type.
 * @return  Allocate Entry structure.
 */
Entry *		entry_create(const char *key, const Value value, Entry *next, Type type) {
    Entry* newEntry = malloc(sizeof(Entry));
    if (!newEntry)
        return NULL;
    newEntry->value.string = strdup("temp");
    newEntry->type = STRING;
    newEntry->key = strdup(key);
    newEntry->next = next;
    entry_update(newEntry, value, type);
    return newEntry;
}

/**
 * Delete entry structure.
 * @param   e               Entry structure.
 * @param   recursive       Whether or not to delete remainder of entries.
 * return   NULL.
 */
Entry *		entry_delete(Entry *e, bool recursive) {
    Entry* nextEntry;
    if (!e) {
        return NULL;
    }
    if (recursive) {
        while (e->next) {
            nextEntry = e->next;
            if (e->type == STRING)
                free(e->value.string);
            free(e->key);
            free(e);
            e = nextEntry;
        }
        if (e->type == STRING)
            free(e->value.string);
        free(e->key);
        free(e);
        return NULL;
    }
    if (e->type == STRING)
        free(e->value.string);
    free(e->key);
    free (e);
    return NULL;
}

/**
 * Update entry's value.
 * @param   e               Entry structure.
 * @param   value           New value for entry.
 * @param   type            New value's type.
 */
void            entry_update(Entry *e, const Value value, Type type) {
    if (e->type == STRING)
        free(e->value.string);
    e->type = type;
    if (type == STRING) {
        e->value.string = strdup(value.string);
    }
    else {
        e->value = value;
    }
}

/**
 * Dump entry.
 * @param   e               Entry structure.
 * @param   stream          File stream to write to.
 * @param   mode            Dump mode to use.
 */
void            entry_dump(Entry *e, FILE *stream, const DumpMode mode) {
    switch (mode) {
        case KEY:
            fprintf(stream, "%s\n", e->key);
            break;
        case KEY_VALUE:
            if (e->type == STRING)
                fprintf(stream, "%s\t%s\n", e->key, e->value.string);
            else
                fprintf(stream, "%s\t%d\n", e->key, e->value.number);
            break;
        case VALUE:
            if (e->type == STRING)
                fprintf(stream, "%s\n",e->value.string);
            else
                fprintf(stream, "%d\n",e->value.number);
            break;
        case VALUE_KEY:
            if (e->type == STRING)
                fprintf(stream, "%s\t%s\n", e->value.string, e->key);
            if (e->type == NUMBER)
                fprintf(stream, "%d\t%s\n", e->value.number, e->key);
            break;
        default:
            debug("DEFAULT");
            break;
    }
}

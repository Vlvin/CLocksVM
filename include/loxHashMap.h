#ifndef LOX_HASH_MAP_H
#define LOX_HASH_MAP_H

#include "loxObject.h"
#include <oneFileSTD.h>


#include <loxValue.h>

#define TABLE_MAX_LOAD 0.75

typedef struct Entry {
  LoxString *key;
  LoxValue value;
} Entry;

typedef struct LoxHashMap {
  size_t size, capacity;
  Entry* entries;
} LoxHashMap;

#define LOAD_FACTOR(hashmap_p) ((hashmap_p->capacity) / ((float)hashmap_p->size))

Entry* _LoxHashMap_find(LoxHashMap* self, LoxString* key);

void LoxHashMap_init(LoxHashMap* self);
void LoxHashMap_free(LoxHashMap* self);
bool LoxHashMap_set(LoxHashMap* self, LoxString* key, LoxValue value);
void LoxHashMap_adjust(LoxHashMap* self, size_t new_size);
bool LoxHashMap_insert(LoxHashMap* self, Entry entry);
LoxValue* LoxHashMap_get(LoxHashMap* self, const char* key);






#endif

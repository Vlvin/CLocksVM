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
  // with tombstones
  size_t size;
  // without tombsones
  size_t count;
  size_t capacity;
  Entry* entries;
} LoxHashMap;

#define LOAD_FACTOR(hashmap_p) ((hashmap_p->capacity) / ((float)hashmap_p->size))

Entry* _LoxHashMap_find(LoxHashMap* self, LoxString* key);

void LoxHashMap_init(LoxHashMap* self);
void LoxHashMap_free(LoxHashMap* self);
bool LoxHashMap_set(LoxHashMap* self, LoxString* key, LoxValue value);
/// @brief 
/// @param self in
/// @param key in
/// @param value out 
/// @return true if found false otherwise
bool LoxHashMap_get(LoxHashMap* self, LoxString* key, LoxValue* value);
bool LoxHashMap_delete(LoxHashMap* self, LoxString* key);
void LoxHashMap_adjust(LoxHashMap* self, size_t new_size);
// shallow copy
void LoxHashMap_copy(LoxHashMap* self, LoxHashMap* dest);
LoxString* LoxHashMap_findString(LoxHashMap* self, const char* begin, size_t size, uint32_t hash);

#endif

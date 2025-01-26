#include "loxObject.h"
#include <loxHashMap.h>

#include <loxMemory.h>
#include <string.h>

void LoxHashMap_init(LoxHashMap *self) {
  *self = (LoxHashMap){0};
}

void LoxHashMap_free(LoxHashMap *self) {
  FREE_ARRAY(Entry, self->entries, self->size);
  LoxHashMap_init(self);
}

void LoxHashMap_adjust(LoxHashMap* self, size_t new_size) {
  LoxHashMap alt = (LoxHashMap){
    self->size,
    new_size,
    ALLOCATE(Entry, new_size)
  };

  for (size_t i = 0; i < self->capacity; i++) {
    Entry* cur = &self->entries[i];
    if (cur->key != NULL) { // not empty
      *_LoxHashMap_find(self, cur->key) = *cur;
    }
  }

  FREE_ARRAY(Entry, self->entries, self->capacity);
  *self = alt;
}

bool LoxHashMap_set(LoxHashMap* self, LoxString* key, LoxValue value) {
  if (self->size + 1 > self->capacity * TABLE_MAX_LOAD) {
    int capacity = GROW_CAPACITY(capacity);
    LoxHashMap_adjust(self, capacity);
  }
  Entry* cur = _LoxHashMap_find(self, key);
  
  const bool isNewKey = cur->key == NULL;

  if (isNewKey) {
    // insert
    self->size++;
  }
  
  cur->key = key;
  cur->value = value;
  
  return isNewKey;
}


Entry* _LoxHashMap_find(LoxHashMap* self, LoxString* key) {
  size_t index = key->hash % self->capacity;
  for (;;)
  {
    Entry* cur = &self->entries[index];
    if (strcmp(cur->key->bytes, key->bytes) || cur->key == NULL) 
      return cur;
    index = index + 1 % self->capacity;
    if (index == key->hash % self->capacity - 1) // only false
      break;
  }
  return NULL;
}

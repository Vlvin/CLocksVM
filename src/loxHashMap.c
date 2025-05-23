#include "loxObject.h"
#include "loxValue.h"
#include <loxHashMap.h>

#include <loxMemory.h>
#include <stdint.h>
#include <string.h>

#define TABLE_INITIAL_SIZE 8

#define TOMBSTONE LOX_BOOL_VAL(true)

void LoxHashMap_init(LoxHashMap *self) {
  self->entries = ALLOCATE(Entry, TABLE_INITIAL_SIZE);
  self->capacity = TABLE_INITIAL_SIZE;
  for (size_t i = 0; i < self->capacity; i++) {
    self->entries[i].value = LOX_NIL_VAL;
    self->entries[i].key = NULL;
  }
  self->size = 0;
  self->count = 0;
}

void LoxHashMap_free(LoxHashMap *self) {
  FREE_ARRAY(Entry, self->entries, self->size);
  LoxHashMap_init(self);
}

void LoxHashMap_adjust(LoxHashMap *self, size_t new_size) {
  LoxHashMap dest = (LoxHashMap){0, 0, new_size, ALLOCATE(Entry, new_size)};

  for (int i = 0; i < new_size; i++) {
    dest.entries[i].key = NULL;
    dest.entries[i].value = LOX_NIL_VAL;
  }

  LoxHashMap_copy(self, &dest);

  FREE_ARRAY(Entry, self->entries, self->capacity);
  *self = dest;
}

bool LoxHashMap_get(LoxHashMap *self, LoxString *key, LoxValue *value) {
  if (self->count == 0)
    return false;
  Entry *cur = _LoxHashMap_find(self, key);
  if (cur->key == NULL)
    return false;
  *value = cur->value;
  return true;
}

// @return false if key is new
bool LoxHashMap_set(LoxHashMap *self, LoxString *key, LoxValue val) {
  if (self->size + 1 > self->capacity * TABLE_MAX_LOAD) {
    LoxHashMap_adjust(self, GROW_CAPACITY(self->capacity));
  }
  Entry *cur = _LoxHashMap_find(self, key);
  const bool isNewKey = cur->key == NULL;

  if (isNewKey) {
    // insert
    self->count++;
    if (IS_LOX_NIL(cur->value)) // tombstone
      self->size++;
  }

  cur->key = key;
  cur->value = val;

  return !isNewKey;
}

bool LoxHashMap_delete(LoxHashMap *self, LoxString *key) {
  Entry *cur = _LoxHashMap_find(self, key);
  if (cur == NULL)
    return false;
  self->count--;
  cur->key = NULL;
  cur->value = TOMBSTONE;
  return true;
}

Entry *_LoxHashMap_find(LoxHashMap *self, LoxString *key) {
  size_t index = key->hash % self->capacity;
  Entry *tombstone = NULL;
  for (;;) {
    Entry *cur = &(self->entries[index]);
    if (cur->key == NULL || cur->key == key) { // has same key or just empty
      if (IS_LOX_NIL(cur->value))
        return tombstone != NULL ? tombstone : cur;
      return cur;
    }
    if (tombstone == NULL && cur->key == NULL &&
        !IS_LOX_NIL(
            cur->value)) // cur is tombstone and 2nd line tombstone is null
      tombstone = cur;
    index = (index + 1) % self->capacity;
    if (index == key->hash % self->capacity - 1) { // only false
      assert(false && "You messed up with hashmap again");
      break;
    }
  }
  return NULL;
}

Entry *_LoxHashMap_findByChars(LoxHashMap *self, const char *begin,
                               const size_t size, const uint32_t hash) {
  char *temp = malloc(size);
  strncpy(temp, begin, size);
  LoxString key =
      (LoxString){// this is untracked string object
                  (LoxObject){LOX_OBJECT_STRING, NULL}, size, temp, hash};
  Entry *value = _LoxHashMap_find(self, &key);
  free(temp);
  return value;
}

void LoxHashMap_copy(LoxHashMap *self, LoxHashMap *dest) {
  dest->size = dest->count = 0;
  for (size_t i = 0; i < self->capacity; i++) {
    Entry *cur = &self->entries[i];
    if (cur->key != NULL) { // not empty
      LoxHashMap_set(dest, cur->key, cur->value);
      dest->size++;
      dest->count++;
    }
  }
}

LoxString *LoxHashMap_findString(LoxHashMap *self, const char *begin,
                                 size_t size, uint32_t hash) {
  if (self->size == 0)
    return NULL;
  size_t index = hash % self->capacity;
  for (;;) {
    Entry *cur = &self->entries[index];
    if (cur->key == NULL) {
      if (IS_LOX_NIL(cur->value))
        return NULL;
    } else if (cur->key->size == size && cur->key->hash == hash &&
               !memcmp(cur->key->bytes, begin, size)) {
      return cur->key;
    }
    index = (index + 1) % self->capacity;
  }
  return NULL;
}

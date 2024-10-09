#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#define LIST(type)\
struct {\
    int size;\
    int capacity;\
    type *data;\
}

#define LIST_INIT(type) { 0, 0, NULL };

#define LIST_PUSH(type, code, list)\
    ((list->data == NULL) ? list->data = (type*)malloc(sizeof(type)*(list->capacity=8)) : NULL); \
    ((list->size >= list->capacity) ? \
        list->data = (type*)realloc(list->data, sizeof(type)*list->capacity*2) : NULL ); \
    list->data[list->size++] = code;

#define LIST_POP(type, list)\
    ((list->size > 0) ? \
        list->size-- : NULL);

#define LIST_FREE(list)\
    free(list->data);\
    list->size = list->capacity = 0; \
    list->data = NULL;


#endif
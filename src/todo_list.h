#ifndef TODO_LIST_H
#define TODO_LIST_H

#define DEFAULT_CAPACITY 10
#define DEFAULT_LOAD_FACTOR 0.75f

#include "todo.h"

typedef struct todo_list_t todo_list_t;

int _resize(size_t new_capacity, todo_list_t* list);
todo_list_t* todo_list_init();
void todo_list_free(todo_list_t* list);
int todo_list_put(int key, todo_t* item, todo_list_t* list);
todo_t* todo_list_get(int key, todo_list_t* list);
todo_t* todo_list_remove(int key, todo_list_t* list);
int todo_list_is_empty(todo_list_t* list);
size_t todo_list_size(todo_list_t* list);

#endif

#ifndef TODO_H
#define TODO_H

#include "imports.h"

typedef struct todo_t todo_t;


todo_t* todo_init(int id, char* text, time_t* timestamp, char* due_date);
int todo_get_id(todo_t* task);
char* todo_get_text(todo_t* task);
int todo_get_status(todo_t* task);
time_t todo_get_timestamp(todo_t* task);
char* todo_get_create_date(todo_t* task);
char* todo_get_modified_date(todo_t* task);
char* todo_get_due_date(todo_t* task);
int todo_mark_done(todo_t* task);
void todo_free(todo_t* task);

#endif

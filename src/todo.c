#include "todo.h"

struct todo_t{
    int id;
    char* text;
    int status;
    char* create_date;
    char* modified_date;
    char* due_date;
};

char* _date_str(time_t* time){
    char* date;
    if(!(date = malloc(DATE_STRING_BUFF))){
        fprintf(stderr, "ERROR: todo init malloc failed\n");
        return NULL;
    }
    struct tm* local = localtime(time);
    strftime(date, DATE_STRING_BUFF, "%Y-%m-%d", local); 
    return date;
}

struct todo_t* todo_init(int id, char* text, time_t* timestamp, char* due_date){
    struct todo_t* out;
    if(!(out = malloc(sizeof(*out)))){
        fprintf(stderr, "ERROR: todo init malloc failed\n");
        return NULL;
    }
    out->id = id;
    out->text = text;
    out->status = !TASK_DONE;
    if(!(out->create_date = _date_str(timestamp))){
        free(out);
        return NULL;
    }
    out->modified_date = out->create_date;
    out->due_date = due_date;
    return out;
}

int todo_get_id(struct todo_t* task){
    return task->id;
}

char* todo_get_text(struct todo_t* task){
    return task->text;
}

int todo_get_status(struct todo_t* task){
    return task->status;
}

char* todo_get_create_date(struct todo_t* task){
    return task->create_date;
}

char* todo_get_modified_date(struct todo_t* task){
    return task->modified_date;
}

char* todo_get_due_date(struct todo_t* task){
    return task->due_date;
}

int todo_mark_done(struct todo_t* task){
    time_t now = time(NULL);
    if(!(task->modified_date = _date_str(&now))){
        return -1;
    }
    task->status = TASK_DONE;
    return 0;
}

void todo_free(struct todo_t* task){
    free(task->create_date);
    free(task->modified_date);
    free(task);
}




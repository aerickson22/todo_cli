#include "todo.h"
#include <time.h>

int main(int argc, char** argv){
    time_t now;
    time(&now);
    todo_t* new_task = todo_init(1, "Do Homework", &now, "2026-11-9");
    if(!new_task){
        return -1;
    }
    printf("%s\n", todo_get_create_date(new_task));
    printf("%s\n", todo_get_modified_date(new_task));
    if(todo_mark_done(new_task)){
        return -1;
    }
    printf("%s\n", todo_get_modified_date(new_task));
    todo_free(new_task);
    return 0;
}


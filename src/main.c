#include "todo_list.h"

int main(int argc, char** argv){
    todo_list_t* list = todo_list_init();
    if(!list){
        return -1;
    }
    time_t now;
    time(&now);
    for(int i = 0; i < 100; i++){
        todo_t* t;
        if(!(t = todo_init(i, "Do Homework", &now, "2026-11-9"))){
            todo_list_free(list);
            return -1;
        }
        if(todo_list_put(i, t, list)){
            todo_free(t);
            todo_list_free(list);
            return -1;
        }
    }
    todo_t* target = todo_list_get(1, list);
    if(!target){
        printf("Not Found!\n");
        todo_list_free(list);
        return -1;
    }
    printf("%s\n", todo_get_create_date(target));
    target = todo_list_remove(45, list);
    printf("%s\n", todo_get_create_date(target));
    todo_list_free(list);
    return 0;
}


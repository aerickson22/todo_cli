#include "todo_list.h"

int main(int argc, char** argv){
    todo_list_t* list = todo_list_init();
    todo_list_free(list);
    return 0;
}


#include "todo_list.h"

struct todo_list_item_t{
    int key;
    todo_t* task;
    struct todo_list_item_t* next; 
};

struct todo_list_t{
    struct todo_list_item_t** tasks;
    size_t size;
    size_t capacity;
    float load_factor;
};

int _resize(size_t new_capacity, todo_list_t* list){
    return 0;
}

struct todo_list_t* todo_list_init(){
    struct todo_list_t* out;
    if(!(out = malloc(sizeof(*out)))){
        fprintf(stderr, "ERROR: todo_list_init failed");
        return NULL;
    }
    if(!(out->tasks = malloc(sizeof(*out->tasks) * DEFAULT_CAPACITY))){
        free(out);
        fprintf(stderr, "ERROR: todo_list_init failed");
        return NULL;
    }
    out->capacity = DEFAULT_CAPACITY;
    out->size = 0;
    out->load_factor = DEFAULT_LOAD_FACTOR;
    return out;
}

void todo_list_free(todo_list_t* list){
    for(int i = 0; i < list->capacity; i++){
        if(!*(list->tasks + (i * sizeof(*list->tasks)))){
            struct todo_list_item_t* curr = *(list->tasks + (i * sizeof(*list->tasks)));
            struct todo_list_item_t* prev;
            while(curr){
                prev = curr;
                curr = curr->next;
                todo_free(prev->task);
                free(prev);
            }
        }
    }
    free(list->tasks);
    free(list);
}

int todo_list_put(int key, todo_t* item, struct todo_list_t* list){
    return 0;
}

todo_t* todo_list_get(int key, struct todo_list_t* list){
    return NULL;
}

todo_t* todo_list_remove(int key, struct todo_list_t* list){
    return NULL;
}

int todo_list_is_empty(struct todo_list_t* list){
    return list->size == 0;
}

size_t todo_list_size(struct todo_list_t* list){
    return list->size;
}

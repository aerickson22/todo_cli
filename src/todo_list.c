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

size_t _hash(int key, todo_list_t* list){
    return key % list->capacity;
}

int _resize(size_t new_capacity, todo_list_t* list){
    struct todo_list_item_t** tmp = (struct todo_list_item_t**)realloc(list->tasks, (sizeof(*list->tasks) * new_capacity));
    if(!tmp){
        fprintf(stderr, "ERROR: resizing todo list failed\n");
        return -1;
    }
    size_t old_capacity = list->capacity;
    memset(tmp + old_capacity, 0, (new_capacity - old_capacity) * sizeof(*tmp));
    list->capacity = new_capacity;
    for(size_t i = 0; i < old_capacity; i++){
        struct todo_list_item_t* curr_bucket = tmp[i];
        tmp[i] = NULL;
        while(curr_bucket){
            struct todo_list_item_t* next = curr_bucket->next;
            size_t index = _hash(curr_bucket->key, list);
            curr_bucket->next = NULL;
            if(!tmp[index]){
                tmp[index] = curr_bucket;
            }else{
                struct todo_list_item_t* p = tmp[index];
                while(p->next) p = p->next;
                p->next = curr_bucket;
            }
            curr_bucket = next;
        }
    }
    list->tasks = tmp;
    return 0;
}

struct todo_list_t* todo_list_init(){
    struct todo_list_t* out;
    if(!(out = malloc(sizeof(*out)))){
        fprintf(stderr, "ERROR: todo_list_init failed\n");
        return NULL;
    }
    if(!(out->tasks = calloc(DEFAULT_CAPACITY, sizeof(*out->tasks)))){
        free(out);
        fprintf(stderr, "ERROR: todo_list_init failed\n");
        return NULL;
    }
    out->capacity = DEFAULT_CAPACITY;
    out->size = 0;
    out->load_factor = DEFAULT_LOAD_FACTOR;
    return out;
}

void todo_list_free(todo_list_t* list){
    for(int i = 0; i < list->capacity; i++){
       struct todo_list_item_t* curr = list->tasks[i];
       struct todo_list_item_t* prev;
       while(curr){
            prev = curr;
            curr = curr->next;
            todo_free(prev->task);
            free(prev);
       }
    }
    free(list->tasks);
    free(list);
}

int todo_list_put(int key, todo_t* item, struct todo_list_t* list){
    if(((float)list->size / (float)list->capacity) >= list->load_factor){
        if(_resize(list->capacity * 2, list)){
            return -1;
        }
    }
    size_t i = _hash(key, list);
    struct todo_list_item_t* new_item = list->tasks[i];
    if(!new_item){
        if(!(new_item = malloc(sizeof(*new_item)))){
            fprintf(stderr, "ERROR: failed to allocate new todo item.\n");
            return -1;
        }
        new_item->key = key;
        new_item->task = item;
        new_item->next = NULL;
        list->tasks[i] = new_item;
    }else{
        struct todo_list_item_t* curr = new_item; 
        while(curr->next){
            curr = curr->next;
        }
        if(!(new_item = malloc(sizeof(*new_item)))){
            fprintf(stderr, "ERROR: failed to allocate new todo item.\n");
            return -1;
        }
        new_item->key = key;
        new_item->task = item;
        new_item->next = NULL;
        curr->next = new_item;
    }
    list->size++;
    return 0;
}

todo_t* todo_list_get(int key, struct todo_list_t* list){
    size_t i = _hash(key, list);
    struct todo_list_item_t* bucket = list->tasks[i];
    while(bucket){
        if(bucket->key == key){
            return bucket->task;
        }
        bucket = bucket->next;
    }
    return NULL;
}

todo_t* todo_list_remove(int key, struct todo_list_t* list){
    size_t i = _hash(key, list);
    struct todo_list_item_t* curr_bucket = list->tasks[i];
    struct todo_list_item_t* prev = NULL;
    while(curr_bucket){
        if(curr_bucket->key == key){
           if(!prev){
               list->tasks[i] = curr_bucket->next;
           }else{
                prev->next = curr_bucket->next;
                curr_bucket->next = NULL;  
            }
            return curr_bucket->task;  
        }
        prev = curr_bucket;
        curr_bucket = curr_bucket->next;
    }
    return NULL;
}

int todo_list_is_empty(struct todo_list_t* list){
    return list->size == 0;
}

size_t todo_list_size(struct todo_list_t* list){
    return list->size;
}

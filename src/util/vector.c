#include "vector.h" 
#include "error.h" 
#include <stdlib.h> 
#include <stdio.h> 

vector make_vec(){
    vector temp; 

    temp.size = 0; 
    temp.capacity = 10; 
    temp.data = (int*)malloc(sizeof(int) * temp.capacity); 

    return temp; 
}

void add(vector * v, int element){
    if (v->capacity == v->size){
        grow(v); 
    }

    v->data[v->size] = element; 
    v->size += 1; 
}

void erase(vector * v, int idx){
    if (idx < 0 || idx >= v->size){
        // idx is out of bounds 
        raise_out_of_bounds_error(); 
    }

    // we guarantee the idx is within bounds 
    for (int i = idx; i < v->size - 1; i++){
        v->data[i] = v->data[i+1]; 
    }
    v->size -= 1; 

    // shrink if we have unnecessary space 
    if (v->size <= v->capacity/2){
        shrink(v); 
    }
}

void grow(vector * v){
    int * temp_array = (int*)malloc(sizeof(int) * v->capacity * 2); 

    for (int i = 0; i < v->size; i++){
        temp_array[i] = v->data[i]; 
    }

    free(v->data); 
    v->data = temp_array; 
}

void shrink(vector * v){
    int * temp_array = (int*)malloc(sizeof(int) * v->capacity / 2); 

    for (int i = 0; i < v->size; i++){
        temp_array[i] = v->data[i]; 
    }

    free(v->data); 
    v->data = temp_array; 
}

int get(vector * v, int idx){
    if (idx < 0 || idx >= v->size){
        // idx is out of bounds 
        raise_out_of_bounds_error(); 
    }

    return v->data[idx]; 
}

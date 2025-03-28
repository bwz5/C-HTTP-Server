#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    int size; 
    int capacity; 
    int * data; 
} vector; 

/* Creates a vector with initial_capacity 10 and size 0, allocating the necessary bytes for data. */
vector make_vec(); 

/* Adds [element] to vector. */
void add(vector * v, int element); 

/* Removes the element at index [idx] and shifts over the elements.
    If [idx] is out-of-bounds then handles the error via exiting and writing 
    to stderr. 
*/
void erase(vector * v, int idx); 

/* Dynamically grows the vector. */
void grow(vector * v); 

/* Dynamically shrinks the vector. */
void shrink(vector * v); 

/* Gets the idx'th element of our vector. 
    If idx is not within bounds, handles the error via exiting and writing 
    to stderr. 
*/
int get(vector * v, int idx); 

#endif 
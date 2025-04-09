// #ifndef HASHMAP_H
// #define HASHMAP_H

// #include <stdio.h>
// #include <stdbool.h>

// #define MAX_LOAD_FACTOR 0.70

// /* 
// Represents an hash map entry, with a key and value element. 
// */
// typedef struct Element {
//     const char * key; 
//     const char * value; 
//     bool empty; 
// } Element; 

// /*
// The implementation of our hash map, using the Open Addressing method 
// */
// typedef struct hash_map_implementation{
//     Element * list; 
//     int num_buckets; 
//     int num_entries; 
//     unsigned int (*hash)(const char * key); 
// } hash_map_implementation; 

// typedef struct HashMap HashMap; 
// /*
// HashMap struct. 
// Note: There is no need to have a removal function, as the http parser does not require it. 
// */
// typedef struct{
//     hash_map_implementation hm; 

//     /* 
//     Adds the Element [key,value] to the HashMap
//     */
//     void (*put)(struct HashMap *self, const char * key, const char * value);

//     /*
//     Gets the (const char *) value from [key] in the HashMap
//     */
//     const char * (*get)(struct HashMap *self, const char * key);
//     /*
//     Returns true if HashMap contains [key], false otherwise. 
//     */
//     bool (*containsKey)(HashMap *self, const char * key);

//     /*
//     Returns the current number of filled entries. 
//     */
//     unsigned int (*size)(HashMap *self);
//     /*
//     Returns true is the HashMap has no entries. 
//     */
//     bool (*isEmpty)(HashMap *self);

//     /*
//     Cleans up all allocated Memory. 
//     */
//     void (*destroy)(HashMap *self);

// } HashMap; 

// /* 
// Initializes an empty HashMap, where NULL represents an unused entry. 
// */
// HashMap* createHashMap(); 

// #endif 
// #include "hashmap.h"

// static unsigned int hash(const char * key, int num_buckets){

// }

// static void put(HashMap *self, const char * key, const char * value){
//     if ((self->hm.num_entries + 1)/self->hm.num_buckets >= MAX_LOAD_FACTOR){
//         // if the load factor would be off, then we need to resize entire 
//         // TODO: 

//     }

//     unsigned int idx = hash(key, self->hm.num_buckets); 
//     while (1){
//         if (self->hm.list[0].empty){
//             self->hm.list[0].key = key; 
//             self->hm.list[0].value = value; 
//             self->hm.list[0].empty = false; 

//             self->hm.num_entries += 1; 
//         } else {
//             idx += 1; 
//             if (idx >= self->hm.num_buckets){ // wrap back around 
//                 idx = 0; 
//             }
//         }
//     }
// }

// static const char * get(HashMap *self, const char * key){
    
// }

// static bool containsKey(HashMap *self, const char * key){

// }

// static unsigned int size(HashMap * self){

// }

// static bool isEmpty(HashMap * self){

// }

// static void destroy(HashMap * self){

// }

// HashMap * createHashMap(){

// }
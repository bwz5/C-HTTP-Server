#ifndef HASHSET_H
#define HASHSET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100  // Number of buckets in our hash set

// Node structure for the linked list in each bucket.
typedef struct Node {
    char *key;
    struct Node *next;
} Node;

// HashSet structure containing an array of linked list pointers.
typedef struct HashSet {
    Node **buckets;
    int size;  // Total number of buckets
} HashSet;

// Hash function (djb2 algorithm) to calculate a hash for a given string.
unsigned int hash(const char *str);

// Create a hash set with a specified number of buckets.
HashSet* create_set(int size);

// Add a key to the hash set.
void add(HashSet *set, const char *key);

// Check whether a key is in the hash set. Returns 1 if found, 0 otherwise.
int contains(HashSet *set, const char *key) ;

// Free all memory associated with the hash set.
void free_set(HashSet *set);

#endif 
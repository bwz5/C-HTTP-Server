#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashset.h"

// Hash function (djb2 algorithm) to calculate a hash for a given string.
unsigned int hash(const char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    return hash;
}

// Create a hash set with a specified number of buckets.
HashSet* create_set(int size) {
    HashSet *set = malloc(sizeof(HashSet));
    if (!set) {
        perror("Failed to allocate memory for HashSet");
        exit(EXIT_FAILURE);
    }
    set->size = size;
    // Allocate memory for buckets and initialize them to NULL.
    set->buckets = calloc(size, sizeof(Node*));
    if (!set->buckets) {
        perror("Failed to allocate memory for buckets");
        free(set);
        exit(EXIT_FAILURE);
    }
    return set;
}

// Add a key to the hash set.
void add(HashSet *set, const char *key) {
    unsigned int index = hash(key) % set->size;
    Node *current = set->buckets[index];

    // Check if the key already exists in the set.
    while (current) {
        if (strcmp(current->key, key) == 0)
            return;  // Key already present, so do nothing.
        current = current->next;
    }

    // Create a new node for the key.
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    new_node->key = strdup(key);
    if (!new_node->key) {
        perror("Failed to allocate memory for key copy");
        free(new_node);
        exit(EXIT_FAILURE);
    }

    // Insert the new node at the beginning of the chain.
    new_node->next = set->buckets[index];
    set->buckets[index] = new_node;
}

// Check whether a key is in the hash set. Returns 1 if found, 0 otherwise.
int contains(HashSet *set, const char *key) {
    unsigned int index = hash(key) % set->size;
    Node *current = set->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0)
            return 1;
        current = current->next;
    }
    return 0;
}

// Free all memory associated with the hash set.
void free_set(HashSet *set) {
    for (int i = 0; i < set->size; ++i) {
        Node *node = set->buckets[i];
        while (node) {
            Node *tmp = node;
            node = node->next;
            free(tmp->key);
            free(tmp);
        }
    }
    free(set->buckets);
    free(set);
}
#include "chain.h"
#include <stdio.h>
#include <stdlib.h>


HashTableNode* hashTable[TABLE_SIZE] = {NULL};

// Hash function to store solutions uniquely
int hashFunction(Solution sol) {
    int hash = (sol.x * 73856093 ^ sol.y * 19349663 ^ sol.z * 83492791) % TABLE_SIZE;
    return abs(hash);  // Ensure positive index
}

// Check if solution exists in the hash table
int solutionExists(Solution sol) {
    int index = hashFunction(sol);
    HashTableNode* entry = hashTable[index];
    while (entry) {
        if (entry->sol.x == sol.x && entry->sol.y == sol.y && entry->sol.z == sol.z) {
            return 1;  // Found duplicate
        }
        entry = entry->next;
    }
    return 0;
}

// Insert a solution into the hash table
void insertSolution(Solution sol) {
    if (solutionExists(sol)) return; // Don't insert duplicates

    int index = hashFunction(sol);
    HashTableNode* newEntry = (HashTableNode*)malloc(sizeof(HashTableNode));
    newEntry->sol = sol;
    newEntry->next = hashTable[index];
    hashTable[index] = newEntry;
}

// Function to print a solution
void printSolution(Solution sol, FILE* toFile) {

    fprintf(toFile, "(%d, %d, %d)\n", sol.x, sol.y, sol.z);

    printf("(%d, %d, %d)\n", sol.x, sol.y, sol.z);
}

// Generate new nodes based on transformations
Node* generateNextNode(Solution sol, int mode, FILE* toFile) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) exit(1);

    // Apply transformations
    if (mode == 1) sol.z = 3 * sol.x * sol.y - sol.z;
    if (mode == 2) sol.y = 3 * sol.z * sol.x - sol.y;
    if (mode == 3) sol.x = 3 * sol.z * sol.y - sol.x;

    // If solution already exists, free memory and return NULL
    if (solutionExists(sol)) {
        free(newNode);
        return NULL;
    }

    insertSolution(sol);
    newNode->sol = sol;
    newNode->firstBranch = newNode->secondBranch = newNode->thirdBranch = NULL;

    // Debugging: Print new nodes being created
    printf("New Node: ");
    printSolution(sol, toFile);

    return newNode;
}

// Append child nodes while preventing duplicates
void appendNodes(Node** root, int depth, int maxDepth, FILE* toFile) {
    if (!(*root) || depth >= maxDepth) return;

    (*root)->firstBranch = generateNextNode((*root)->sol, 1, toFile);
    (*root)->secondBranch = generateNextNode((*root)->sol, 2, toFile);
    (*root)->thirdBranch = generateNextNode((*root)->sol, 3, toFile);

    appendNodes(&(*root)->firstBranch, depth + 1, maxDepth, toFile);
    appendNodes(&(*root)->secondBranch, depth + 1, maxDepth,toFile);
    appendNodes(&(*root)->thirdBranch, depth + 1, maxDepth, toFile);
}

// Print the tree in a structured format
void printTree(Node* root, int depth, FILE* toFile) {
    if (!root) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printSolution(root->sol, toFile);
    printTree(root->firstBranch, depth + 1, toFile);
    printTree(root->secondBranch, depth + 1, toFile);
    printTree(root->thirdBranch, depth + 1, toFile);
}

// Free the hash table memory
void freeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashTableNode* entry = hashTable[i];
        while (entry) {
            HashTableNode* temp = entry;
            entry = entry->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

// Free the tree memory
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->firstBranch);
    freeTree(root->secondBranch);
    freeTree(root->thirdBranch);
    free(root);
}
#include <stdio.h>

#define TABLE_SIZE 10007  // Prime number for hash table

typedef struct Solution {
    int x, y, z;
} Solution;

typedef struct Node {
    Solution sol;
    struct Node* firstBranch;
    struct Node* secondBranch;
    struct Node* thirdBranch;
} Node;

typedef struct HashTableNode {
    Solution sol;
    struct HashTableNode* next;
} HashTableNode;

extern HashTableNode* hashTable[TABLE_SIZE];

int hashFunction(Solution sol);
int solutionExists(Solution sol);
void insertSolution(Solution sol);
void printSolution(Solution sol, FILE* toFile);
Node* generateNextNode(Solution sol, int mode, FILE* toFile);
void appendNodes(Node** root, int depth, int maxDepth, FILE* toFile);
void printTree(Node* root, int depth, FILE* toFile);
void freeHashTable();
void freeTree(Node* root);
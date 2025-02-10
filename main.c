#include <stdio.h>
#include <stdlib.h>
#include "chain.h"





int main() {



    Solution trivialSolution = {1, 1, 1};

    FILE* toFile = fopen("solutions.txt", "w");
    if(!toFile) {
        fprintf(stderr, "Can not open file solutions.txt in the function generateNextNode!");
        return 0;
    }

    Node* trivialNode = (Node*)malloc(sizeof(Node));
    if (!trivialNode) exit(1);

    trivialNode->sol = trivialSolution;
    trivialNode->firstBranch = trivialNode->secondBranch = trivialNode->thirdBranch = NULL;

    insertSolution(trivialSolution);  // Add first solution to hash table

    int maxDepth = 5;  // Control depth of recursion
    appendNodes(&trivialNode, 0, maxDepth, toFile);

    printf("\nTree of Unique Solutions:\n");

    

    printTree(trivialNode, 0, toFile);

    freeTree(trivialNode);
    freeHashTable();

    fclose(toFile);

    return 0;
}

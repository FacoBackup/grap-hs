#include <stdio.h>
#include <stdlib.h>
#include "../common.h"


void dfs(Item *current, int *count, Vertex *prevVertex) {
     Vertex *vertex = current->value;
    if (vertex->isVisited) {
        return;
    }
    vertex->isVisited = 1;
    vertex->insertionTime = *count;
    vertex->lowTime = *count;
    *count = *count + 1;

    struct LinkedList *children = vertex->neighbours;

    Item *currentChild = children->start;
    while (currentChild != NULL) {
        if (currentChild->value != prevVertex) {
            if (currentChild->value->isVisited) {
                // BACK EDGE
                vertex->lowTime = min(vertex->lowTime, currentChild->value->insertionTime);
            } else {
                dfs(currentChild, count, vertex);
                if (vertex->insertionTime < currentChild->value->lowTime) {
                    printf(
                            "\nBRIDGE %d->%d (INSERTION TIME: %d LOW: %d)",
                            vertex->value,
                            currentChild->value->value,
                            vertex->insertionTime,
                            currentChild->value->lowTime
                    );
                }
                vertex->lowTime = min(vertex->lowTime, currentChild->value->lowTime);
            }
        }
        currentChild = currentChild->next;
    }
}

char *FILE_NAME = "C:\\Users\\russi\\CLionProjects\\grafos2\\files\\bridge.txt";

int main() {
    int edgesSize;
    LinkedList *graph = loadFile(FILE_NAME, &edgesSize, 1);
    if (graph == NULL) {
        printf("FILE NOT FOUND");
        return 0;
    }
    int count = 1;
    struct Item *current = graph->start;
    dfs(current, &count, NULL);
    printf("\n\n");
    while (current != NULL) {
        printf("\n N: %d | LOW: %d | INS: %d", current->value->value, current->value->lowTime,
               current->value->insertionTime);
        current = current->next;
    }
}


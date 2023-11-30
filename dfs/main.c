#include <stdio.h>
#include <stdlib.h>
#include "../common.h"


void dfs(Item *current, int depth, int *isCyclical, int *isBipartite, int color) {

    struct Vertex *vertex = current->value;

    if (depth > 0) {
        printf("\n    ->%d", vertex->value);
    } else {
        printf("\n------%d", vertex->value);
    }

    if (vertex->isVisited == 1) {
        return;
    }

    vertex->color = color;
    vertex->isVisited = 1;

    struct LinkedList *children = vertex->neighbours;
    Item *currentChild = children->start;
    while (currentChild != NULL) {
        if (currentChild->value->isVisited == 1 && currentChild->value->color == color) {
            *isBipartite = 0;
        }
        if (currentChild->value->isVisited == 0 && currentChild->value->firstVisit == NULL) {
            currentChild->value->firstVisit = current->value;
        } else if (depth > 0 && currentChild->value->isVisited == 1 &&
                   (currentChild->value->firstVisit == NULL || currentChild->value->firstVisit != current->value)) {
            *isCyclical = 1;
        }
        dfs(currentChild, depth + 1, isCyclical, isBipartite, 1 - color);
        currentChild = currentChild->next;
    }
}
char *FILE_NAME = "C:\\Users\\russi\\CLionProjects\\grafos2\\files\\tree.txt";
int main() {
    int edgesSize;

    LinkedList *graph = loadFile(FILE_NAME, &edgesSize, 1);
    if (graph == NULL) {
        printf("FILE NOT FOUND");
        return 0;
    } else {
        printf("\n\n GRAPH INFO:\nVERTICES: %d;\nEDGES: %d;", graph->size, edgesSize);
    }
    Item *current = graph->start;
    int isBipartite = 1;
    int isCyclical = 0;
    while (current != NULL) {
        dfs(current, 0, &isCyclical, &isBipartite, 0);
        current = current->next;
    }

    showResult(edgesSize, graph->size, isCyclical, isBipartite);
}


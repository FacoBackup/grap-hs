#include <stdio.h>
#include <stdlib.h>
#include "../common.h"


typedef struct Queue {
    struct Item *start;
    struct Item *end;
    int totalSize;
    int size;
} Queue;

Item *enqueue(Queue *queue) {
    Item *item = calloc(1, sizeof(struct Item));
    if (queue->start == NULL) {
        queue->start = item;
        queue->end = item;
    } else {
        item->next = queue->start;
        item->next->previousOptional = item;
        queue->start = item;
    }
    queue->totalSize += 1;
    queue->size += 1;
    return item;
}

Item *dequeue(Queue *queue) {
    if (queue->start == NULL) {
        return NULL;
    }
    Item *current = queue->end;
    queue->end = current->previousOptional;
    if (queue->end == NULL) {
        queue->start = NULL;
    }
    queue->size -= 1;
    return current;
}

Queue *allocateQueue() {
    return calloc(1, sizeof(Queue));
}

void bfs(struct Item *pItem, Queue *pQueue, int level, int *distance, int *distantItem) {
    if(level == 0 && distance == NULL){
        *distance = 0;
        *distantItem = 0;
    }
    struct Vertex *vertex = pItem->value;
    if (vertex->isVisited == 1) {
        return;
    }

    if (pItem->queueLevel > 0) {
        if (*distance < pItem->queueLevel) {
            *distance = pItem->queueLevel;
            *distantItem = pItem->value->value;
        }
        for (int i = 0; i < pItem->queueLevel; i++) {
            printf("\t");
        }
        printf("->%d\n", vertex->value);
    } else {
        printf("\n%d", vertex->value);
    }
    vertex->isVisited = 1;

    struct LinkedList *neighbours = vertex->neighbours;
    Item *child = neighbours->start;
    while (child != NULL) {
        Item *childItem = enqueue(pQueue);
        childItem->value = child->value;
        childItem->queueLevel = level + 1;
        child = child->next;
    }

    child = dequeue(pQueue);
    while (child != NULL) {
        bfs(child, pQueue, child->queueLevel, distance, distantItem);
        child = dequeue(pQueue);
    }

}
char *FILE_NAME = "C:\\Users\\russi\\CLionProjects\\grafos2\\files\\bridge.txt";

int main() {
    int edgesSize;
    LinkedList *list = loadFile(FILE_NAME, &edgesSize, 1);
    struct Item *current = list->start;
    Queue *executionQueue = allocateQueue();
    int distance;
    int mostDistantItem;
    while (current != NULL) {

        bfs(current, executionQueue, 0, &distance, &mostDistantItem);
        current = current->next;
    }

    printf("INITIAL DISTANCE: %d", distance);
    Item *pItem = searchByValue(list, mostDistantItem);
    if (pItem != NULL) {
        mostDistantItem = -1;
        distance = -1;
        bfs(pItem, executionQueue, 0, &distance, &mostDistantItem);
        printf("\nDISTANce: %d; MOST DISTANT: %d", distance, mostDistantItem);
    }

    return 0;
}



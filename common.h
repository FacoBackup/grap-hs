//
// Created by russi on 9/27/2023.
//

#ifndef GRAFOS2_COMMON_H
#define GRAFOS2_COMMON_H
char *FILE_NAME = "C:\\Users\\russi\\CLionProjects\\grafos2\\files\\tree.txt";

typedef struct Item {
    struct Vertex *value;
    struct Item *next;
    struct Item *previousOptional;
    int queueLevel;
} Item;

typedef struct LinkedList {
    struct Item *start;
    int size;
} LinkedList;

typedef struct Vertex {
    struct LinkedList *neighbours;
    int isVisited;
    int color;
    int value;
    struct Vertex *firstVisit;
} Vertex;


LinkedList *allocateListOfVertices() {
//    printf("ALLOCATING LIST OF VERTICES\n");
    return calloc(1, sizeof(LinkedList));
}

Item *findEnd(LinkedList *pList) {
//    printf("FINDING END OF LINKED LIST\n");

    Item *current = pList->start;
    while (current != NULL) {
        if (current->next == NULL) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Item *allocateListItem(LinkedList *pList) {
//    printf("ALLOCATING LIST ITEM\n");
    Item *item = calloc(1, sizeof(Item));
    Item *endItem = findEnd(pList);
    if (endItem != NULL) {
        endItem->next = item;
    } else {
        pList->start = item;
    }
    pList->size++;
    return item;
}

Vertex *allocateVertex() {
//    printf("ALLOCATING VERTEX\n");
    return calloc(1, sizeof(Vertex));
}

void showResult(int edgesSize, int size, int isCyclical, int isBipartite) {
    printf("\n\n");
    if (isBipartite == 1) {
        printf("IS BIPARTITE");
    } else {
        printf("NOT BIPARTITE");
    }

    if (isCyclical == 1) {
        printf("\nIS CYCLICAL");
    } else {
        printf("\nNOT CYCLICAL");
    }

    if (edgesSize + 1 == size && isCyclical == 0) {
        printf("\nIS TREE");
    } else {
        printf("\nNOT TREE");
    }
}


Item *searchByValue(LinkedList *pList, int value) {
//    printf("SEARCHING BY VALUE\n");
    Item *current = pList->start;
    while (current != NULL) {
        if (current->value->value == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

LinkedList *loadFile(int *edgesSize, int bidirectional) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        return NULL;
    }
    LinkedList *pList = allocateListOfVertices();
    int qtd;
    *edgesSize = 0;
    fscanf(file, "%d", &qtd);
    for (int i = 0; i < qtd; i++) {
        int v1, v2;
        fscanf(file, "%d %d", &v1, &v2);
        Item *v1Item = searchByValue(pList, v1);
        Item *v2Item = searchByValue(pList, v2);

        if (v1Item == NULL)
            v1Item = allocateListItem(pList);
        if (v2Item == NULL)
            v2Item = allocateListItem(pList);

        if (v1Item->value == NULL) {
            v1Item->value = allocateVertex();
            v1Item->value->neighbours = allocateListOfVertices();
        }
        if (v2Item->value == NULL) {
            v2Item->value = allocateVertex();
            v2Item->value->neighbours = allocateListOfVertices();
        }
        v1Item->value->value = v1;
        v2Item->value->value = v2;
        Item *v1Neighbours = allocateListItem(v1Item->value->neighbours);
        v1Neighbours->value = v2Item->value;

        if (bidirectional == 1) {
            Item *v2Neighbours = allocateListItem(v2Item->value->neighbours);
            v2Neighbours->value = v1Item->value;
        }
        *edgesSize += 1;
    }
    return pList;
}
#endif //GRAFOS2_COMMON_H

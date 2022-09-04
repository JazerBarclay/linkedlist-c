#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

int main() {

    tNode *node1 = (tNode *) malloc(sizeof(tNode));
    tNode *node2 = (tNode *) malloc(sizeof(tNode));
    tNode *node3 = (tNode *) malloc(sizeof(tNode));

    node1->data = "1";
    node2->data = "2";
    node3->data = "3";

    node1 = insertStart(node1, node2);
    node1 = insertEnd(node1, node3);

    printList(node1);

    tNode *popped = pop(&node1);

    printList(popped);
    printList(node1);

    node1 = insertEnd(node1, node2);

    printList(node1);

    printf("Size: %d\n", getListSize(node1));

    clearList(&node1);

    if (node1 == NULL)
    {
        printf("Head is NULL\n");
    }
    else
    {
        printf("Head is not empty: %s\n", (char *)node1->data);
    }


    return(0);
}
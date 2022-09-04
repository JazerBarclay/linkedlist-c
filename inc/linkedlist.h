/*
 * Linked List
 */

#include <stdint.h>

/*
 * Linked List Nodes
 */
typedef struct tNode {
    void *data;
    struct tNode *next;
} tNode;

/* 
 * Insert a new node at the end given a head node to reference
 * Returns the head node of the list
 */
tNode * insert(tNode *head, tNode *newNode);

/*
 * Insert a new node at the start given a head node to reference
 * Returns the head node of the list
 */
tNode * insertStart(tNode *head, tNode *newNode);

/*
 * Insert a new node at the end given a head node to reference
 * Returns the head node of the list
 */
tNode * insertEnd(tNode *head, tNode *newNode);

/*
 * Insert a new node after the given node referenced
 * Returns the head node of the list
 */
tNode * insertAt(tNode *node, tNode *newNode);

/* 
 * Remove the head node from a list
 * Returns the new head node of the list and updates the reference to new head
 */
tNode * pop(tNode **head);

/* 
 * Prints the list starting at the head node referenced
 */
void printList(tNode *head);

/*
 * Frees all memebers in a list removing all nodes including the head node
 */
void clearList(tNode **head);

uint32_t getListSize(tNode *head);

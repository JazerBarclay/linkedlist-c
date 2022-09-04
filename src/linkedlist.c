#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "linkedlist.h"

/* 
 * Insert a new node at the end given a head node to reference
 * Returns the head node of the list
 */
tNode * insert(tNode *head, tNode *newNode)
{
    // Perform an insert at start by default
    return insertStart(head, newNode);
}

/*
 * Insert a new node at the start given a head node to reference
 * Returns the head node of the list
 */
tNode * insertStart(tNode *head, tNode *newNode)
{
    // Add the head to the new node's next
    newNode->next = (struct tNode *)head;

    // Return the new node as the new head
    return newNode;
}

/*
 * Insert a new node at the end given a head node to reference
 * Returns the head node of the list
 */
tNode * insertEnd(tNode *head, tNode *newNode)
{
    // Store pointer for tracking in while loop
    tNode *currentNode = head;

    // While the currently checked node is not null
    while (currentNode->next != NULL)
    {
        // Move to next node
        currentNode = currentNode->next;
    }

    // Add new node to end of last node
    currentNode->next = newNode;

    // Return head reference
    return head;
}

/* 
 * Remove the head node from a list
 * Returns the popped node from the list and updates the reference to new head
 */
tNode * pop(tNode **head)
{
    // Store first node as the de-referenced address of head
    tNode *popped = *head;

    // De-referenced head param is replaced with the popped node's next node
    *head = popped->next;

    // Clear the next refernce in the popped node to NULL
    popped->next = NULL;

    // Return the popped reference node
    return popped;
}

/* 
 * Prints the list starting at the head node referenced
 */
void printList(tNode *head)
{
    // If head is null then just return
    if (head == NULL) 
    {
        return;
    }

    // Store track refernce to head
    tNode *currrent = head;

    // While the current node is not null
    while (currrent != NULL)
    {
        // Print the char data stored in the current node
        printf("%s", (char*)currrent->data);
        
        // Move to next node
        currrent = (tNode *)currrent->next;
    }

    // Print new line to end the print
    printf("\n");
}

uint32_t getListSize(tNode *head)
{
    if (head == NULL)
    {
        return 0;
    }
    if (head->next == NULL)
    {
        return 1;
    }
    return 1+getListSize(head->next);
}

void clearList(tNode **head)
{
    if ( *head == NULL )
    {
        return;
    }

    if ( (*head)->next != NULL )
    {
        clearList( &(*head)->next );
    }

    free( *head );
    *head = NULL;
}
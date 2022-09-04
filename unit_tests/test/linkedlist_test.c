#include <stdlib.h>
#include <stdint.h>
#include "unity.h"
#include "linkedlist.h"

void setUp(void)
{

}

void tearDown(void)
{

}

/* Test the creation of a new node containing string data */
void test_linkedlist_createCharNode(void)
{
    // Create a new node using tNode struct
    tNode *node = (tNode *) malloc(sizeof(tNode));
    
    // Set the node's data value to "Test"
    node->data = (char *)"Test";

    // Ensure nodes data matches the string "Test"
    TEST_ASSERT_EQUAL("Test", (char *)node->data);
}


/* Test the creation of a new node containing integer data */
void test_linkedlist_createIntNode(void)
{
    // Create a new node using tNode struct
    tNode *node = (tNode *) malloc(sizeof(tNode));
    
    // Set the node's data value to 1
    node->data = (uint32_t *)1;

    // Ensure nodes data matches the integer 1
    TEST_ASSERT_EQUAL(1, (uint32_t *)node->data);
}


/* Test the insertion of a new node at the start of a list */
void test_linkedlist_insertStart(void)
{
    // Original head (our starting node)
    tNode *head = (tNode *) malloc(sizeof(tNode));
    
    // The next node to be added (will be added in front of head)
    tNode *nextNode = (tNode *) malloc(sizeof(tNode));
    
    // Set the data for the nodes
    head->data = (char *)"Head Node";
    nextNode->data = (char *)"New Node";

    // Ensure both have no next pointer assigned
    TEST_ASSERT_EQUAL(head->next, NULL);
    TEST_ASSERT_EQUAL(nextNode->next, NULL);

    // Perform insertion of next node at start of head
    insertStart(head, nextNode);

    // Ensure next node points to head
    TEST_ASSERT_EQUAL(nextNode->next, head);
    
    // Ensure head is end of list
    TEST_ASSERT_EQUAL(head->next, NULL);
}


/* Test the insertion of a new node at the end of a list */
void test_linkedlist_insertEnd(void)
{
    // Our starting node
    tNode *head = (tNode *) malloc(sizeof(tNode));
    
    // The next node to be added (will be added after head)
    tNode *nextNode = (tNode *) malloc(sizeof(tNode));
    
    // Set the data for the nodes
    head->data = (char *)"Head Node";
    nextNode->data = (char *)"New Node";

    // Ensure both have no next pointer assigned
    TEST_ASSERT_EQUAL(head->next, NULL);
    TEST_ASSERT_EQUAL(nextNode->next, NULL);

    // Perform insertion of next node at start of head
    insertEnd(head, nextNode);

    // Ensure head node points to next
    TEST_ASSERT_EQUAL(head->next, nextNode);
    
    // Ensure next node is end of list
    TEST_ASSERT_EQUAL(nextNode->next, NULL);
}

/* Test the retrieval and removal of the top node in a list using pop */
void test_linkedlist_pop(void)
{
    // Our nodes
    tNode *root = (tNode *) malloc(sizeof(tNode));
    tNode *nextNode = (tNode *) malloc(sizeof(tNode));
    
    // Set the data for the nodes
    root->data = (char *)"Root Node";
    nextNode->data = (char *)"New Node";

    // Ensure both have no next pointer assigned
    TEST_ASSERT_EQUAL(NULL, root->next);
    TEST_ASSERT_EQUAL(NULL, nextNode->next);

    // Perform insertion of next node at start of head
    insertEnd(root, nextNode);

    // Ensure head node points to next
    TEST_ASSERT_EQUAL(root->next, nextNode);
    
    // Ensure next node is end of list
    TEST_ASSERT_EQUAL(NULL, nextNode->next);

    // Pop the top node from the list and store it
    tNode *poppedNode = pop(&root);

    /** NOTE: poppedNode contains the old root and *root is now the nextNode **/

    // Ensure both nodes now point to null
    TEST_ASSERT_EQUAL(NULL, poppedNode->next);
    TEST_ASSERT_EQUAL(NULL, root->next);

    // Ensure the values stored in the nodes match
    TEST_ASSERT_EQUAL("Root Node", ((char *)poppedNode->data));
    TEST_ASSERT_EQUAL("New Node", ((char *)root->data));
}


/* Test the checking of a list's size */
void test_linkedlist_getListSize(void)
{
    // Create nodes to test sizes with
    tNode *root = (tNode *) malloc(sizeof(tNode));
    tNode *nextNode = (tNode *) malloc(sizeof(tNode));

    // Insert the next node after root
    insertEnd(root, nextNode);

    // Ensure null = 0, next is 1 (itself), root is 2 (itself and next)
    TEST_ASSERT_EQUAL(0, getListSize(NULL));
    TEST_ASSERT_EQUAL(1, getListSize(nextNode));
    TEST_ASSERT_EQUAL(2, getListSize(root));

    // Pop the root value from the list
    tNode *popped = pop(&root);
    
    // Now all nodes are individual, ensure all are 1
    TEST_ASSERT_EQUAL(1, getListSize(root));
    TEST_ASSERT_EQUAL(1, getListSize(popped));
}

/* Test the removal of all nodes from a root node */
void test_linkedlist_clearList(void)
{
    // Create nodes to test sizes with
    tNode *root = (tNode *) malloc(sizeof(tNode));
    tNode *nextNode = (tNode *) malloc(sizeof(tNode));

    // Insert the next node after root
    insertEnd(root, nextNode);

    // Ensure root has a size of 2
    TEST_ASSERT_EQUAL(2, getListSize(root));

    // Pop the root value from the list
    clearList(&root);
    
    // Now the list is cleared, ensure size = 0
    TEST_ASSERT_EQUAL(0, getListSize(root));
}
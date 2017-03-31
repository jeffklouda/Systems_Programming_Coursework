/* list.c */

#include "list.h"
#include <stdlib.h>

/* Internal Function Prototypes */

static struct node*	reverse(struct node *curr, struct node *next);
static struct node *	msort(struct node *head, node_compare f);
static void		split(struct node *head, struct node **left, struct node **right);
static struct node *	merge(struct node *left, struct node *right, node_compare f);

/**
 * Create list.
 *
 * This allocates a list that the user must later deallocate.
 * @return  Allocated list structure.
 */
struct list *	list_create() {
    struct list* newList = malloc(sizeof(struct list));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

/**
 * Delete list.
 *
 * This deallocates the given list along with the nodes inside the list.
 * @param   l	    List to deallocate.
 * @return  NULL pointer.
 */
struct list *	list_delete(struct list *l) {
    // recursively delete all nodes
    node_delete(l->head, true);
    // deallocate list memory
    free(l);
    return NULL;
}

/**
 * Push front.
 *
 * This adds a new node containing the given string to the front of the list.
 * @param   l	    List structure.
 * @param   s	    String.
 */
void		list_push_front(struct list *l, char *s) {
    struct node* newNode;

    // Make new node and set is as head node
    if (l->head) {
        newNode = node_create(s, l->head);
    }
    else {
        newNode = node_create(s, NULL);
    }
    
    // set head of list to this node
    l->head = newNode;
    l->size += 1;
    // first node is also last if list is empty
    if (!l->tail)
        l->tail = newNode;
}

/**
 * Push back.
 *
 * This adds a new node containing the given string to the back of the list.
 * @param   l	    List structure.
 * @param   s	    String.
 */
void		list_push_back(struct list *l, char *s) {
    struct node* newNode = node_create(s, NULL);
    l->size += 1;
    if (l->tail) {
        (l->tail)->next = newNode;
        l->tail = newNode;
    }
    else { // list is empty
        l->head = newNode;
        l->tail = newNode;
    }
}

/**
 * Dump list to stream.
 *
 * This dumps out all the nodes in the list to the given stream.
 * @param   l	    List structure.
 * @param   stream  File stream.
 */
void		list_dump(struct list *l, FILE *stream) {
    struct node* currNode = l->head;
    while (currNode) {
        node_dump(currNode, stream);
        fprintf(stream, "\n");
        if (currNode->next == NULL )
            break;
        currNode = currNode->next;
    }
}

/**
 * Convert list to array.
 *
 * This copies the pointers to nodes in the list to a newly allocate array that
 * the user must later deallocate.
 * @param   l	    List structure.
 * @return  Allocate array of pointers to nodes.
 */
struct node **	list_to_array(struct list *l) {
    struct node** arr = malloc((l->size) * sizeof(struct node*));
    struct node* node = l->head;
    int i = 0;
    /*struct node** w = arr; // writer pointer*/
    while (node) {
        arr[i] = node;
        i++;
        node = node->next;
    }
    return arr;
}

/**
 * Sort list using qsort.
 *
 * This sorts the list using the qsort function from the standard C library.
 * @param   l	    List structure.
 * @param   f	    Node comparison function.
 */
void		list_qsort(struct list *l, node_compare f) {
    
    if (l->size < 2)
        return;
 
    struct node** arr = list_to_array(l);
    
    qsort(arr, l->size, sizeof(struct node*), f);

    for (size_t i = 0; i < l->size - 1; i++) {
        (arr[i])->next = arr[i+1];
    }

    (arr[l->size - 1])->next = NULL;
    l->head = arr[0];
    l->tail = arr[l->size - 1];
    free(arr);
}

/**
 * Reverse list.
 *
 * This reverses the list.
 * @param   l	    List structure.
 */
void		list_reverse(struct list *l) {
    l->tail = l->head;
    l->head = reverse(l->head, NULL);   
}

/**
 * Reverse node.
 *
 * This internal function recursively reverses the node.
 * @param   curr    The current node.
 * @param   prev    The previous node.
 * @return  The new head of the singly-linked list.
 */
struct node*	reverse(struct node *curr, struct node *prev) {
    struct node* tail = curr;
    if (curr->next)
        tail = reverse(curr->next, curr);
    curr->next = prev;
    return tail;
}

/**
 * Sort list using merge sort.
 *
 * This sorts the list using a custom implementation of merge sort.
 * @param   l	    List structure.
 * @param   f	    Node comparison function.
 */
void		list_msort(struct list *l, node_compare f) {
    struct node* ptr;
    l->head = msort(l->head, f);
    ptr = l->head;
    while (ptr->next)
        ptr = ptr->next;
    l->tail = ptr;
    
}

/**
 * Performs recursive merge sort.
 *
 * This internal function performs a recursive merge sort on the singly-linked
 * list starting with head.
 * @param   head    The first node in a singly-linked list.
 * @param   f	    Node comparison function.
 * @return  The new head of the list.
 */
struct node *	msort(struct node *head, node_compare f) {
    
    /* Divide */
    struct node* left = head;
    struct node* right = head;
    
    if (head->next) {
        split(head, &left, &right);
        
        /* Conquer */
        left = msort(left, f);
        right = msort(right, f);

        /* Combine */
        head = merge(left, right, f);
    }
    return head;
}

/**
 * Splits the list.
 *
 * This internal function splits the singly-linked list starting with head into
 * left and right sublists.
 * @param   head    The first node in a singly-linked list.
 * @param   left    The left sublist.
 * @param   right   The right sublist.
 */
void	split(struct node *head, struct node **left, struct node **right) {
    if (!head->next)
        return;
    struct node* fastPtr = head;
    struct node* slowPtr = head;
    while (fastPtr != NULL && fastPtr->next != NULL) {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
    }
    *left = head;
    while (head->next != slowPtr)
        head = head->next;
    head->next = NULL;
    *right = slowPtr;
}

/**
 * Merge sublists.
 *
 * This internal function merges the left and right sublists into one ordered
 * list.
 * @param   left    The left sublist.
 * @param   right   The right sublist.
 * @param   f	    Node comparison function.
 * @return  The new head of the list.
 */
struct node *	merge(struct node *left, struct node *right, node_compare f) {
    struct node* head = node_create("tempHead", NULL);
    struct node* tail = head;
    while (right && left) {
        if ( f(&left, &right) > 0 ) {
            tail->next = right;
            tail = tail->next;
            right = right->next;
        }
        else if ( f(&left, &right) < 0 ) {
            tail->next = left;
            tail = tail->next;
            left = left->next;
        }
        else {  /* Nodes are equal */
            tail->next = left;
            tail = tail->next;
            tail->next = right;
            tail = tail->next;
            left = left->next;
            right = right->next;
        }
    }
    while (left) {
        tail->next = left;
        tail = tail->next;
        left = left->next;
    }
    while (right) {
        tail->next = right;
        tail = tail->next;
        right = right->next;
    }
    
    tail->next = NULL;
    tail = head->next;
    node_delete(head, false);
    return tail;
}

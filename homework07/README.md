Homework 07
===========

### Activity 1: Singly-Linked List Library

**1.** Describe what memory you allocated in `node_create` and what memory 
you deallocated in `node_delete`. How did you handle the recursive flag? 

In `node_create` I allocated memory for the node itself with 
`malloc(sizeof(struct node))` as well as space for the node's string with
`strdup(string)`.  In `delete_node` I deallocated the memory for the 
string with `free(n->string)` and then the memory for the node with 
`free(n)`.  I handled the recursive flag by taking each node `n`, creating 
a `tempNode` pointer that points to `n`'s next node, and then freeing the
memory for n and its string before doing the same for the node now stored in
`tempNode`.  The base case for this process is when `n->next` is NULL, which
is the last node in the list.

**2.** Describe what memory you allocated in `list_create` and what memory 
you deallocated in `list_delete`. How did you handle internal struct nodes?

In `list_create()` I allocated only the memory for the list itself with 
`malloc(sizeof(struct list))` the memory for the nodes is allocated in
`push_front` and `push_back` where `node_create` is called.  In `list_delete`
I deallocated the memory for the list with `free(l)` after freeing the 
memory for all the nodes with `node_delete(l->head, true)`, deleting all the
nodes recursively.  As mentioned before, internal `struct nodes` were 
handled by calling `node_create` when adding a new node to the list.

**3.** Describe how your `list_qsort` function works and analyze its time 
complexity and space complexity in terms of Big-O notation (both average and 
worst case).

My `list_qsort` begins by calling creating an array of the list by calling
`list_to_array` This makes an array of all the `struct node` pointers
contained in the list.  It then calls `qsort` on that array with the input
comparison function as the comparison argument.  Once the nodes are in the
sorted array, the function points each node's `next` pointer to the next
node in the array. It the sets the head and tail pointers to the beginning
and end of the array before deallocataing the memory used for the array.
The space complexity for this function will always be O(n) because it 
stores all of the pointers from the list in a new array for the sorting.
Because the function uses the quick sort alogorithm, its best case time
complexity is O(nlogn) and its worst case if O(n^2).  All the assignments I
do in addition to the quick sort are O(n) so they do not affect the time 
complexity in either average or worst case.

**4.** Describe how your `list_reverse` function works and analyze its time 
complexity and space complexity in terms of Big-O notation (both average and 
worst case).

My `list_reverse` calls the `reverse` function with the head pointer and NULL
as arguments.  `reverse` recursively reverses a list by setting a `tail`
pointer at the `curr` node and then setting that pointer to the result of 
`reverse(curr->next, curr)` if `curr->next` exists (the base case).  After
this, it sets `curr`'s next pointer to `prev` and returns the `tail` pointer
which now points to the end of the original list.  Since this function
effectively iterates through the list and then sets each node's next pointer
to the node before it, its time complexity is O(n) in the average and worst
case since a constant number of assignments are made for each node in the
list.  Its space complexity is O(n) because a new tail pointer is allocated
for each recurrsion and the function recurses for each node.  No memory 
other than the pointers is allocated because all the assignments are done
in place.

**5.** Describe how your `list_msort` function works and analyze its time 
complexity and space complexity in terms of Big-O notation (both average and 
worst case).

My `list_msort` function operates by calling the `msort` function on its
head node.  `msort` performs a recursive merge sort.  It begins by splitting
the list up into two lists `left` and `right` with the `split` function and
then calls `msort` on those two lists.  It then merges those two lists 
together with the `merge` function.  The `merge` function takes in two 
sorted lists and then compares the first value in each list, the lower value
is added to a new list and then this process repeats, adding the smaller
value to the end of this list.  In the base case, this list will only 
consist of two nodes, so they will be sorted properly, and then each level
above that both input lists will be sorted, so the final list will be 
properly sorted.  This operation is O(nlogn) in average and worst cases 
because of how each recursion splits the lists in half to be sorted and then
sorts those halfs together.  The space complexity is O(logn) because of the
constant number pointers and nodes needed to organize the list that are 
generated at each recursion.

### Activity 2: List Sort

| NITEMS   | SORT     | TIME     | SPACE    |
| -------- | -------- | -------- | -------- |
| 1        | Merge    | 0.0      | 0.5      |
| 1        | Quick    | 0.0      | 0.5      |
| 10       | Merge    | 0.0      | 0.5      |
| 10       | Quick    | 0.0      | 0.5      |
| 100      | Merge    | 0.0      | 0.5      |
| 100      | Quick    | 0.0      | 0.5      |
| 1000     | Merge    | 0.0      | 0.6      |
| 1000     | Quick    | 0.0      | 0.6      |
| 10000    | Merge    | 0.0      | 1.1      |
| 10000    | Quick    | 0.0      | 1.3      |
| 100000   | Merge    | 0.1      | 6.6      |
| 100000   | Quick    | 0.1      | 8.2      |
| 1000000  | Merge    | 2.4      | 61.5     |
| 1000000  | Quick    | 1.3      | 76.8     |
| 10000000 | Merge    | 33.5     | 610.8    |
| 10000000 | Quick    | 19.1     | 763.5    |

**1.** Based on your experiments, what is the overall trend in terms of time 
and space as the number of items increases for both of your sorting methods?

Are the results surprising to you? Explain why or why not.

Based on my experiments the time and space required by each sort increases
with the input size as expected and the memory used by the quicksort is 
greater than that used by the mergesort which is to be expected considering
their big-O memory complexities, but the quicksort ran faster than the merge
sort in every test, which I did not expect given quicksort's O(n^2) worst
case time complexity vs. mergesort's O(nlogn).

**2.** Given what you said about the space complexity and time complexity of 
`list_msort` and `list_qsort` in Activity 1 and the experimental results in 
Activity 2, what can you say is the relationship between theoretical 
complexity and real world performance? Explain.

Given my results and earlier complexity analysis it would seem that worst 
case complexity is not necessarily a good indicator of real world performance
as my function with higher worst case time complexity performed faster than
the other.  Average case complexity does seem to be a fair indicator of 
real performance since the two functions were relatively close in runtime.
but it is difficult to predict how this would change as the input size
grows beyond what I tested.

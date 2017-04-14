Homework 08
===========

### Activity 1: Map Library

**1.** Briefly describe what memory you allocated in `entry_create` and what 
memory you deallocated in `entry_delete`. How did you handle the recursive 
flag?

In `entry_create` I allocated the memory for the new entry with `newEntry =
malloc(sizeof(Entry))` and memory for the entry's key with `strdup`, and 
memory for the entry's value if the type is STRING with `strdup`.  I 
deallocated this same memory in `entry_delete` and handled the recursive flag
by incrementing through each entry's next pointer and deleting that entry.

**2.** Briefly describe what memory you allocated in `map_create` and what 
memory you deallocated in `map_create`. How did you handle internal entries?

In `map_create` I allocated the memory for the map itself and then the 
memory for the array of Entries `buckets`.  In `map_delete` I deallocated
all the entries in the map, then the memory for the `buckets` array, and 
then the memory for the map itself.  I handled the internal entries by
incrementing through the linked lists in each bucket and calling 
`entry_delete` on each entry.

**3.** Briefly describe what memory you allocated, copied, and deallocated in
`map_resize`. When is this function called and what exactly does it do to 
grow the map?

In `map_resize` I allocate a `new_buckets` array of the new size. The entries
are all relinked, so they do not to be copied.  Finally I deallocated the 
`old_buckets` array which was the `buckets` array of the original map.  This
function is called when the load factor is greater than the max load factor
of the array.  It essentially creates a new map of a larger size and then
adds all the entries from the old map to the new one.

**4.** Briefly describe how your `map_insert` function works and analyze its 
time complexity and space complexity in terms of Big-O notation (both average
and worst case).

My `map_insert` computes the hash function for the key of the new entry and
then searches for that entry in the bucket corresponding to that hash value.
If that entry exists, its value is updated, otherwise that entry is added to
that list.  This function is O(1) in time and space complexity in average 
case because the function will always calculate exactly which bucket to add 
the entry to and additional memory is allocated other than a constant number 
of pointers.  In worst case, the time complexity is O(n), because the worst
case would be if all the entries are in one buckets, so we must iterate 
through the entire data as a linked list to search for a value that is not
yet in the map.

**5.** Briefly describe how your `map_search` function works and analyze its 
time complexity and space complexity in terms of Big-O notation (both average
and worst case).

My `map_search` function calculates the hash value for the key in question
and then increments through that bucket until it finds an entry with that
key or a null entry.  It then returns either the found entry or the NULL 
pointer.  This function will be O(1) in time complexity and space complexity
in average case because once again the hash values tells the program exactly 
where to look for the key and only a constant number of variables are used to
find it.  Its worst case time complexity will be O(n) like insert because the
function would have to search though all the entries as a linked list in the
worst case.

**6.** Briefly describe how your `map_remove` function works and analyze its 
time complexity and space complexity in terms of Big-O notation (both average and worst case).

`map_remove` searches for a specific value in much the same way as 
`map_search` does.  When it finds the entry, it relinks the entries around
it to each other and then deletes that entry.  This will have the same 
time and space complexity as `map_search` because it functions in exactly 
the same way and allocates a constant amount of memory.

### Activity 2: Word Frequencies

**1.** Based on your experiments, what is the overall trend in terms of time 
and space as the number of items increases for the different load factors?

Are the results surprising to you? Explain why or why not.

Looking at the results, both time and space increase with the number of 
items computed, while time increases with rising alpha and space decreases
with rising alpha values.  This is to be expected because the lower alpha is,
the more likely the map is to be resized, which uses much more memory, but
will make the operations more efficient because fewer entries will be placed
in the same bucket.

**2.** There is no such thing as a perfect data structure. Compare this hash 
table to the treap you are creating in your data structures class. What are 
the advantages and disadvantages of both? If you had to use one as the 
underlying data structure for a map, which one would you choose and why?

Both the table and the treap are very efficient for searching and determining
membership, but this map is more efficient in terms of time because of its
O(1) search vs. the treap's O(logn).  The treap is more efficient in space
because it allocates only the memory for the entries while the table has to
allocate memory for a large array of buckets for the most efficient searches.
If I were to use one of these as the underlying data structure for a map, 
I would use the hash table as long as space is not a concern because of its
more efficient insert and search operations.  If space was a major concern, 
then I would go for the treap instead.

|   NITEMS   |   ALPHA    |    TIME    |   SPACE    |
|------------|------------|------------|------------|
|          1 |       0.50 |       0.00 |       0.58 |
|          1 |       0.75 |       0.00 |       0.57 |
|          1 |       0.90 |       0.00 |       0.58 |
|          1 |       1.00 |       0.00 |       0.58 |
|          1 |       2.00 |       0.00 |       0.58 |
|          1 |       4.00 |       0.00 |       0.58 |
|          1 |       8.00 |       0.00 |       0.58 |
|          1 |      16.00 |       0.00 |       0.57 |
|         10 |       0.50 |       0.00 |       0.58 |
|         10 |       0.75 |       0.00 |       0.58 |
|         10 |       0.90 |       0.00 |       0.58 |
|         10 |       1.00 |       0.00 |       0.57 |
|         10 |       2.00 |       0.00 |       0.57 |
|         10 |       4.00 |       0.00 |       0.58 |
|         10 |       8.00 |       0.00 |       0.57 |
|         10 |      16.00 |       0.00 |       0.57 |
|        100 |       0.50 |       0.00 |       0.59 |
|        100 |       0.75 |       0.00 |       0.58 |
|        100 |       0.90 |       0.00 |       0.58 |
|        100 |       1.00 |       0.00 |       0.58 |
|        100 |       2.00 |       0.00 |       0.58 |
|        100 |       4.00 |       0.00 |       0.58 |
|        100 |       8.00 |       0.00 |       0.58 |
|        100 |      16.00 |       0.00 |       0.57 |
|       1000 |       0.50 |       0.00 |       0.66 |
|       1000 |       0.75 |       0.00 |       0.66 |
|       1000 |       0.90 |       0.00 |       0.65 |
|       1000 |       1.00 |       0.00 |       0.66 |
|       1000 |       2.00 |       0.00 |       0.65 |
|       1000 |       4.00 |       0.00 |       0.65 |
|       1000 |       8.00 |       0.00 |       0.65 |
|       1000 |      16.00 |       0.00 |       0.66 |
|      10000 |       0.50 |       0.01 |       1.89 |
|      10000 |       0.75 |       0.01 |       1.89 |
|      10000 |       0.90 |       0.01 |       1.89 |
|      10000 |       1.00 |       0.01 |       1.89 |
|      10000 |       2.00 |       0.01 |       1.56 |
|      10000 |       4.00 |       0.01 |       1.44 |
|      10000 |       8.00 |       0.01 |       1.36 |
|      10000 |      16.00 |       0.01 |       1.34 |
|     100000 |       0.50 |       0.16 |      12.18 |
|     100000 |       0.75 |       0.16 |      12.18 |
|     100000 |       0.90 |       0.16 |      12.18 |
|     100000 |       1.00 |       0.16 |      12.18 |
|     100000 |       2.00 |       0.15 |      10.18 |
|     100000 |       4.00 |       0.16 |       9.18 |
|     100000 |       8.00 |       0.17 |       8.68 |
|     100000 |      16.00 |       0.21 |       8.43 |
|    1000000 |       0.50 |       1.79 |     108.84 |
|    1000000 |       0.75 |       2.07 |     108.84 |
|    1000000 |       0.90 |       2.01 |     108.84 |
|    1000000 |       1.00 |       2.01 |     108.84 |
|    1000000 |       2.00 |       2.07 |      92.84 |
|    1000000 |       4.00 |       2.20 |      84.84 |
|    1000000 |       8.00 |       2.71 |      80.84 |
|    1000000 |      16.00 |       3.62 |      78.84 |
|   10000000 |       0.50 |      23.70 |    1408.51 |
|   10000000 |       0.75 |      23.92 |    1408.52 |
|   10000000 |       0.90 |      25.49 |    1408.52 |
|   10000000 |       1.00 |      24.65 |    1408.51 |
|   10000000 |       2.00 |      24.21 |    1024.51 |
|   10000000 |       4.00 |      25.63 |     891.48 |
|   10000000 |       8.00 |      36.22 |     827.49 |
|   10000000 |      16.00 |      50.01 |     795.49 |

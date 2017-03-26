Reading 08
==========

### Activity 1

Given the following lines of code in C99:

```
struct point {
    double x;
    double y;
};

...

1. int            i = 0;
2. int          a[] = {4, 6, 6, 3, 7};
3. char          *s = "pgui";
4. struct point   p = {0, 0};
5. struct point  *q = NULL;
6. struct point  *x = malloc(sizeof(struct point));
7. struct point  *y = malloc(10*sizeof(struct point));
8. struct point **z = malloc(10*sizeof(struct point *));
```

How much memory (in terms of bytes) is allocated or reserved for each of the 
8 declarations above (assume a 64 bit Linux machine such as the student 
machines)?

1 allocates memory for only the single int i so it allocates 4 bytes.  2 
allocates 5 times that because it creates an array of 5 ints, so it allocates
20 bytes.  3 allocates 4 chars as well as a pointer to the first char so it
allocates 5 \* 1 = 5 bytes for the chars (including the null character) and 
8 for the pointer, 13 bytes in total.  4 allocates memory for the struct 
`point` which contains 2 doubles at 8 bytes each, so it allocates 16 bytes.
5 allocates memory for only a `struct point` pointer, 8 bytes.  6 allocates
memory for one pointer (8) and one struct point (16), 24 bytes in total.
7 allocates memory for one pointer(8) and the space of 10 struct points (16),
168 bytes.  8 allocates memory for a pointer to a pointer (8) and space for
10 pointers (8), 88 bytes in total.

### Activity 2

**1.** Describe what the memory error was in Task 4 and how you fixed it.

The memory error in Task 4 was caused by how the malloc function was used to
allocate the memory for the randoms array.  The function was allocating n 
bytes when it should have been allocating memory for n ints.  I fixed this
by changing `malloc(n)` to `malloc(n*sizeof(int))`.  To allocate the proper
amount of memory.

**2.** Describe what the memory leak was in Task 5 and how you fixed it.

The memory leak in Task 5 was caused by the memory allocated for `randoms`
never being freed because of how duplicates() was written.  duplicates() 
called `free(randoms)` at the end of the function, just before returning
false.  If any duplicates were contained in `randoms` then this command
would never run.  By adding `%1000` to rand() we guaranteed that the function
would find duplicates and thus the memory was never being freed.  I fixed 
this error by calling `free(randoms)` just before returning true after 
finding a match.

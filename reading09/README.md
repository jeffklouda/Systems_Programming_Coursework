Reading 09
==========

### Activity 1

**1.** What is the size of s and what is the size of u?

s is 12 bytes (8 for the char\* and 4 for the int), and u is 8 bytes (the 
size of its largest member, char\*).

**2.** What is the difference between a union and a struct?

A union allocates enough memory for just its largest data member and stores
only member at a time while a struct allocates memory for all its members
and can store and access any of these members at any time.

### Activity 2

**1.** What message does this program output?

This program outputs the message "fate is inexorable!".

**2.** Use the `DUMP_BITS` macro to explore this program and then explain how
it works (that is, how does setting the values above in the `struct Thing t` 
object yield the final message).

This program sets each `Value` by assigning bits as different data types
(char, short, int, long) to access different bits in each 8 byte Value.
Because unions use the same memory for any value it stores, the bytes 
assigned to a bigger data type such as a `long` will be preserved when
writing over certain bits with a smaller data type like an `int`.  This
program takes advantage of this aspect of unions to assign each letter of 
the final message in each of the bytes stored in the Values stored in the
`struct Thing t`.  It then uses a char\*pointer to increment through `t`'s
data and read each byte as an ascii `char` for output.

**3.** What does this program tell you about types, memory, and how data is 
represented in C? What are we really doing when we cast values in C?

This program tells me that all data in C is stored in the same way, in bits,
and that the values we get out of a certain program really depend on what we
call those bits, be it an `int` or a `char` or so on.  When we cast values
in C, we are really telling the program to read those same bytes but as a
different type of data.

### Activity 3

**1.** What exactly is a collision?

A collision in a hash table is when the hashing function returns the same
value and thus the same index for distinct inputs.

**2.** How are collisions handled in a hash table that uses separate 
chaining?

In a hash table using separate chaining, each index in the table contains
a list, and each time an additional data point is mapped to this index, 
it is simply added to that list.

**3.** How are collisions handled in a hash table that uses open addressing 
(e.g. linear probing)?

In hash tables using open addressing, data that maps to an index already 
occupied by another value is stored in the next available index in the array,
the next index that does yet not contain a value.  Then when a value needs to
be accessed, one can go to the index produced by the hash function for that
value and then step through each subsequent index in the table until finding
either that value or an empty bucket.

### Activity 4

**1.** Using separate chaining and using the hash function h(x) = x % 10, 
show the result of inserting the following values into the table:

7, 3, 2, 78, 56, 72, 79, 68, 13, 14

| Bucket    | Value     |
| --------- | --------- |
| 0         |           |
| 1         |           |
| 2         | 2, 72     |
| 3         | 3, 13     |
| 4         | 14        |
| 5         |           |
| 6         | 56        |
| 7         | 7         |
| 8         | 78, 68    |
| 9         | 79        |

**2.** Using open addressing (and linear probing with an interval of 1), and 
using the hash function h(x) = x % 10, show the result of inserting the 
following values into the table:

7, 3, 2, 78, 56, 72, 79, 68, 13, 14

| Bucket    | Value     |
| --------- | --------- |
| 0         | 68        |
| 1         | 14        |
| 2         | 2         |
| 3         | 3         |
| 4         | 72        |
| 5         | 13        |
| 6         | 56        |
| 7         | 7         |
| 8         | 78        |
| 9         | 79        |

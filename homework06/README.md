Homework 06
===========

### Activity 1: String Utilities Library

**1.** Describe how your `string_reverse_words` function works and analyze 
its time complexity and space complexity in terms of Big-O notation.

My `string_reverse_words` function works by first calling `string_reverse`
on the inout string `s`.  This function uses a two pointers to swap each
character at the end of the string with a corresponding character at the 
beginning up to the middle of the string, resulting in at most `n/2` swaps,
so this function's space complexity is O(1) because the memory used to store
the pointers and the temp value used to make the swaps is constant and the 
time complexity is O(n) because of the swaps.  The function then declares 
two pointers `cb` for marking the beginning of words and `ce` for marking 
the end of words.  Space complexity is still O(1) because the number of 
pointers is constant.  The function then increments  through the string 
using a while loop on the condition `*ce`.  In each loop, `ce` is 
incremented until the character after it is either a space or the null 
character (meaning it points to the end of a word), and then `cb` is 
incremented until it does not point to a space (meaning it points to the
beginning of a word).  The function then calls `string_reverse_range` on
`cb` and `ce` to reverse that word (back to its original form since it was 
reversed by the original call to `string_reverse_words`).
`string_reverse_range` works just as `string_reverse` (because
`string_reverse` calls `string_reverse_range`) so each of these calls
will be O(n) time complexity and O(1) space complexity.  The function calls
`string_reverse_range` once for each word, but each character will never be
swapped more than twice (once at the beginning and once as each word is
swapped).  Since there will be at most 2n swaps for n characters, the time
complexity of the entire function is O(n).  Therefore the entire time
complexity for the function is O(n) and the space complexity is O(1).

**2.** Describe how your `string_translate` function works and analyze its 
time complexity and space complexity in terms of Big-O notation.

My `string_translate` function begins by initializing a 128 entry char array
with the value `0` in each entry.  This array is my `lookup_table` which 
stores the data for translating each character from the `from` string to the 
`to` string.  After checking that the length of `from` is the same as that 
of `to`, the function loops through each character in `from` and each 
character in `to` and stores the `to` values in `lookup` with the 
corresponding `from` character as the index. (eg. if one were to translate
'a' to 'g' then `lookup_table['a'] = 'g'`.  The function then increments
through the input string `s` and checks the value corresponding to each
character in the lookup table.  If that value is zero, then the character is
unchanged, otherwise the character is changed to the value in the table.
This function is O(n) time complexity because at most one comparison and
one assignment is made for each character in `s` and one assignment is 
made for each pair of values in `from` and `to`.  It is O(1) space
complexity because it uses only the 128 value lookup table, one integer
incrementer and one additional pointer.

**3.** Describe how your `string_to_integer` function works and analyze its 
time complexity and space complexity in terms of Big-O notation.

My `string_to_integer` function initializes and integer `returnValue = 0` to
store the integer value of the string and then calls `string_lowercase` on
`s` to make calculating values above 9 independent of their case. 
The function then loops through the string starting at the end and translates
each character into its integer value ('9' - '0' = 0. 'b' - 'a' + 10 = 11)
before multiplying that number by the base value raised to the power of that
location (done with a second variable `multBy` initialized at 1 and
multiplied by `base` each loop) and adding it to `returnValue`.  This
function's time complexity is once again O(n) because only one assignment
is made per character in the input.  The space complexity is O(1) because
the number of values is stored is constant and independent of the input.

**4.** What is the difference between a shared library such as libstringutils
.so and a static library such as libstringutils.a?

A shared library is compiled and then used by the program at run-time while
a static library is compiled with all of the code it needs in the library
and then linked into the program that requires it.  Comparing the size of my
shared library `libstringutils.a` and my static library `libstringustils.so`,
the static library is larger, 14 KB vs 12 KB.  This is because 
`libstringutils.so` contains all the code it need to run while 
`libstringutils.a` references that code at run-time.

### Activity 2: Translate

**1.** Describe how the translate.c program works.

The `translate.c` program parses command line arguments in much the same way
as the `grep.c` program from the last reading assignment.  It begins by
incrementing through all the command line arguments that are more than one
character and begin with '-'.  It then uses a case statement to see if these
flags correspond to any of the filtering options.  If one of those options is
found, then the corresponding bit in the `mode` bitmask is set to one such 
as with the statement `case 's': mode |= STRIP;`.  These flagss are defined
globally using `enum` to set each to the proper value.  
To do the translation, the program calls the `translate_stream` function.
The function stores each line from `stdin` in a buffer char array `buffer`
and then performs the translation on the line by calling the 
`string_translate` function from the `stringutils` library.  It then applies
the post processing filters based on the variable `mode` assigned when
parsing the command line arguments.  The program uses if statements to 
check if the bit corresponding to each filter is assigned and if so then 
applies that filter on `buffer`.  Finally, the function prints the buffer to
`stdout` along with a newline character.

**2.** What is the difference between a static executable such as 
`translate-static` and a dynamic executable such as `translate-dynamic`?

Comparing the sizes of `translate-static` and `translate-dynamic` I see that
the static executable is much lareger than the dynamic one, 885KB vs 14.
This is because the static executable has all of the code from the libraries
it references linked into the executable and can be executed independent of 
those files.  For this reason, I am able to execute `translate-static`
after simply compiling it with the `-static` flag.  I cannot, however,
execute `translate-dynamic` when I try to, I receive an error message
stating `libstringutils.so: cannot open shared object file`.  In order to 
get is executable to run I had to add the path to my shared library to 
`LD_LIBRARY_PATH` with `export LD_LIBRARY_PATH=/home/jklouda1.lib:./`.  This
"tells" the linker to look in the current directory for the shared library
file.  Once I did this, I was abe to run both executables.

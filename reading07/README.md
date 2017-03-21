Reading 07
==========

### Activity 1

**1.** Describe what the read\_numbers function does by explaining what is 
happening on the following line:

```
while (i < n && scanf("%d", &numbers[i]) != EOF) {
```

The `read_numbers` reads in numbers from an input stream and stores the first
`n` numbers in the `numbers[]` array.  It then returns the number of values
stored in the array `i`.  The `i < n` in the while statement insures that the
loop runs only while the index of `numbers` is less than `n`. In the main
loop `MAX_NUMBERS` is passed to n, which is defined as `1<<10` or `1024`.
`scanf` reads the next characters from the input stream that matches the 
format string `"%d`, which is the next integer in the stream.  It stores the
integer it finds in `numbers[i]` which is preceded by the `&` to denote it is
a pointer because `scanf()` uses pointers to store data. The `!= EOF` portion
of the code checks that scanf() has not reached the end of the input (end of
file), if it has, then the while loop will not run.

**2.** Insteading of passing i`size_t n` into the `sum_numbers` function, 
could we have used sizeof to get the size of the array as shown below?

```
int sum_numbers(int numbers[]) {
    int total = 0;
    for (size_t i = 0; i < sizeof(numbers); i++) {
        total += numbers[i];
    }

    return total;
}
```

We cannot usei `sizeof` to get the size of the array beacuse `sizeof` is used
to determine the size of a variable or datatype, not the number of values in
an array.  When I tried this code, sizeof(numbers) evalutated to 8.  This
suggests that sizeof returns the size of `int*` when called on `numbers`.

### Activity 2: cat.c

**1.** Compare how this version of cat parses command line arguments versus 
the approach used in cat.py from Reading 05. Beyond the obvious differences 
in syntax, how is the code similar and how is it different?

The two programs parse command line arguments in largely the same way,
initially incrementing through the arguments to catch any that begin with
"-" or are only one character and displaying the usage message.  `cat.c`
increments through the arguments with an index based on the constant `argc`
while `cat.py` does so by calling `pop` on the `args` list.  The two programs
then parse the arguments for each file (or stdin) in the same way,
incrementing through the remaining arguments and calling the appropriate 
functions to display their contents.  `cat.c` increments through the 
arguments by incrementing the index `argind` on the `argv` array as long
as it does not excede the total number of arguments `argc` while `cat.py`
uses a for loop to increment through the arguments remaining in the `args`
list.

**2.** Describe how each file is processed by explaining the following code:

```
while (argind < argc) {
    char *path = argv[argind++];
    if (strcmp(path, "-") == 0) {
        cat_stream(stdin);
    } else {
        cat_file(path);
    }
}
```

This code increments through the programs arguments that should correspond to
either file names or "-" to specify stdin.  The if-else statement determines
whether to run the `cat_stream` function on stdin, printing the contents of
stdin to stdout if the argument is "-" or to run `cat_file` on the argument
string, opening the file and then displaying printing its contents to stdout
with `cat_stream`.  `char *path = argv[argind++] sets `path` to the string
at `argv` of index `argind` before incrementing `argind` by 1 with 
`argind++`.  The `strcmp` comparison checks for strings that are "-" to 
denote input from stdin.

**3.** Explain how the cat_stream function works. What are the purposes of 
fgets and fputs?

`cat_stream` creates an array of chars `buffer` and then places each char
from the input stream to that buffer.  `fgets(buffer, BUFSIZ, stream)` reads
in up to `BUFSIZ` chars from `stream` and stores them in `buffer` along with
a terminating null byte ('/0').  `fputs(buffer, stdout)` then writes every
char from the `buffer` array to `stdout` up to but not including the 
terminating null byte.  

**4.** Explain how the cat_file function works. What is the purpose of the 
following if statement:

```
if (fs == NULL) {
    fprintf(stderr, "%s: %s: %s\n", PROGRAM_NAME, path, strerror(errno));
    return;
}
```

`cat_file` begins by opening the file at `path` and setting it to the FILE
pointer `fs`.  The if statement above then checks whether `fs` points to a
valid file location.  If not (`fs == NULL`) then the function prints an 
error message using `strerror` which prints the error message corresponding 
to its argument number `errno` which returns the number of the last error
set by the program and end the function with `return` to `stderr`.  If the 
file is valid, it then calls `cat_stream` on `fs` to print the contents of 
the file and then closes the file location with `fclose(fs)`.

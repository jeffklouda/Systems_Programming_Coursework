Reading 05
==========

### Part 1

**1.** What is the purpose of `import sys`?

`import sys` imports the `sys` module.=, which gives us access to the 
`sys.argv` object used in the script.

**2.** Explain what `for arg in sys.argv[1:]:` does.

This section of the script executes a `for` loop.  The loop runs for every
element from element 1 in the `sys.argv` list, where `arg` is equal to the
that element for every iteration. This iterates through every argument
passed to the script except the first, which is the name of the script 
itself.

**3.** Why is there a trailing `,` in `print arg,`?

The trailing `,` in `print arg,` prevents the script from printing each 
argument on a new line, instead printing them all one line.

### Part 2

**1.** Explain how the command line arguments are parsed by discussing how 
this loop `while len(args) and args[0].startswith('-') and len(args) > 1`
works.

This loop runs while `len(args)` is true, meaning there are arguments in the
`args` list, `args[0].startswith('-')`, meaning the first argument in the
`args` list starts with `-`, and `len(args[0]) > 1`, meaning the length
of that first argument in the `args` list is greater than 1 character.
The loop begins by removing the first element from `args` and storing it in
`arg` with `arg = args.pop(0)`.  The script then runs the appropriate lines
based on the input argument using the if loop.

**2.** What are the purposes of the following code blocks:
```
if len(args) == 0:
    args.append('-')
```
```
if path == '-':
    stream = sys.stdin
else:
    stream = open(path)
```

These two blocks determine where to take the input for the script.  If
`len(args)` is equal to 0, then no file was entered as an argument, the 
script denotes this by adding a `-` to the list.  The second block then 
executes this by setting the `stream` to `stdin` if no file was entered, and
the path to the file if it was entered.

**3.** What does `line = line.rstrip()` do? Is it necessary?

The `rstrip()` method removes trailing whitespace from each line.  This is
necessary because otherwise the `$` optionally printed at the end of each
line may be printed after some whitespace, changing the output of the script.


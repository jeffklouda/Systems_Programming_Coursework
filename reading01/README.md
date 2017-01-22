Reading 01
==========

### Question 1
```
$ du -h /etc/ 2> /dev/null | sort -h > output.txt
```

**a.** What is the purpose of the `|` ?
    The `|` pipes the standard output of the `du` command into the standard input of the `sort` command.

**b.** What is the purpose of the `2> /dev/null` ?
    The 2> /dev/null redirects the standard error to /dev/null, effectively suppressing error messages from the command.

**c.** What is the purpose of the `> output.txt` ?
    The > output.txt redirects the standard output of the sort command, writing it to output.txt.

**d.** What is the purpose of the `-h` flags?
    The -h flags format the outputs of the du and sort commands in human-readable format, representing file sizes in kb, mb, etc. rather than bytes. 

**e.** Is the following command the same as the one above? Explain.
```
$ du -h /etc/ | sort -h > output.txt 2> /dev/null
```
    This command is not equivalent to the one above because it redirects the standard error from the sort command to /dev/null rather than that of the du command.

### Question 2

**a.** How would you concatenate all the files from 2002 into one file?
```
cat 2002\* > 2002file.txt
```

**b.** How would you concatenate all the files from the month of December into one file?
```
cat \*-12 > decFile.txt
```

**c.** How would you view the contents of all files from the month of January to June?
```
cat \*-{01..06}
```

**d.** How would you view the contents of all files with an even year and odd month?
```
cat 200{2..9..2}-{01..12..2}
```

**e.** How would you view the contents of all the files from 2002 to 2004 in the months of September to December?
```
cat 200{2..4}-{09..12}
```

### Question 3
```
-rw------- 1 pbui users 0 Jan 18 07:19 Beastie
-rwxr-xr-x 1 pbui users 0 Jan 18 07:18 Huxley
-rwxr-x--- 1 pbui users 0 Jan 18 07:18 Tux
```

**a.** Which files are executable by the owner?
    `Huxley` and `Tux` (---x------)

**b.** Which files are readable by the members of the `users` group?
    `Huxley` and `Tux` (----r-----)

**c.** Which files are writable by anyone (ie. the world)?
    None (--------w-)

**d.** What command would you execute so that `Tux` had the same permissions as `Huxley`?
```
chmod o+rx Tux
```

**e.** What command you you execute so that `Tux` had the same permissions as `Beastie`?
```
chmod g-rx Tux
```

### Question 4
```
$ bc
```

**a.** How would you suspend the `bc` process?
    ctrl + z

**b.** How would you resume the `bc` process?`
    `fg` or `fg %[jobspec]` if there is more than one job

**c.** How would you signal the end of input to the `bc` process?
    ctrl + d

**d.** If the `bc` process was still running, how would you terminate the `bc` process?
    ctrl + c

**e.** If the `bc` process was still running, how would you terminate the `bc` process from another terminal?
    `kill -1 bc` or `kill -1 %[jobspec]`

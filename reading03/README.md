Reading 03
==========

**1.** Convert all the input text to upper case:

```
$ echo "All your base are belong to us" | tr a-z A-Z
ALL YOUR BASE ARE BELONG TO US
```

`tr` finds all character in the range a to z and replaces them with the corresponding characters
in the range A to Z, effectively converting all lower case text to upper case.

**2.** Find and replace all instances of `monkeys` to `gorillaz`:

```
$ echo "monkeys love bananas" | sed 's/monkeys/gorillaz/'
gorillaz love bananas
```

`sed`'s `s` command replaces all instance of `monkeys` with `gorillaz`.

**3.** Remove any leading whitespace from a string of text:

```
$ echo "     monkeys love bananas" | sed 's/^ *//'
monkeys love bananas
```

Here, the `s` command replaces 0 or more (\*) blank spaces (' ') at the beginning of the line (^)
with nothing, effectively removing the whitespace at the beginning of the line.

**4.** Parse the `/etc/passwd` file for the shell of the root user:

```
$ sort -t : -k 3 /etc/passwd | head -n 1 | cut -d ':' -f 7
/bin/bash
```

Probably not the most elegant solution, but `sort` sorts the files in `/etc/passwd` by the third 
field (`-k 3`), `head` takes the first file, which will be that of the root user who has a UID of 0 
in the third field, and `cut` removes the seventh field of the line, which is the shell.

**5.** Find and replace all instances of /bin/bash, /bin/csh, and /bin/tcsh to /usr/bin/python in 
/etc/passwd:

```
$ cat /etc/passwd | sed 's_/bin/\(bash\|csh\|tcsh\)_/usr/bin/python_' | grep python
root:x:0:0:root:/root:/usr/bin/python
mysql:x:27:27:MySQL Server:/var/lib/mysql:/usr/bin/python
xguest:x:500:501:Guest:/home/xguest:/usr/bin/python
condor:x:108172:40:Condor Batch System:/afs/nd.edu/user37/condor:/usr/bin/python
lukew:x:522:40:Luke Westby temp access:/var/tmp/lukew:/usr/bin/python
```

Here, `sed` replaces all instances of the regular expression /bin/\(bash|csh|tcsh\), which expands
to `/bin/bash`, `/bin/csh`, or `/bin/tcsh`, with `/usr/bin/python`.

**6.** Find all the records in /etc/passwd that have a number that begins with a 4 and ends with a 
7:

```
$ cat /etc/passwd | grep '4[[:digit:]]*7'
rtkit:x:499:497:RealtimeKit:/proc:/sbin/nologin
qpidd:x:497:495:Owner of Qpidd Daemons:/var/lib/qpidd:/sbin/nologin
uuidd:x:495:487:UUID generator helper daemon:/var/lib/libuuid:/sbin/nologin
mailnull:x:47:47::/var/spool/mqueue:/sbin/nologin
```

`grep '4[[:digit:]]*7'` returns all lines containing a 4 followed by some number zero or greater
of digits 0-9, followed by a 7.

**7.** Given two text files, show all the lines that are present in both files.

```
comm -12 file1 file2
```

`comm` displays the unique lines in each file and the lines in both files. `-12` suppresses the
columns that show the unique lines, leaving only the lines in both files.

**8.** Given two text files, show which lines are different. 

```
diff file1 file2
```

`diff` displays which lines are different between file1 and file2 as well as what those differences
are.

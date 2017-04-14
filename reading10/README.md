Reading 10
==========

### 1. Identify which system calls you would use to perform the following actions by briefly listing example C code:

**1.** Put the error message associated with a failed system call.

`puts("%s\n", strerror(errno));`

**2.** Truncate a file.

`ftruncate(fd. length)`

**3.** Move to the 10th byte of a file.

`lseek(fd, 9, SEEK_SET);`

**4.** Check if a path is a directory.

```
struct stat s;
stat(PATH, &s);
if (S_ISDIR(s.st_mode)) { ...
```

**5.** Create a copy of the current process.

`fork()`

**6.** Replace the code in the current process with another program.

`execve(pathname, argv, envp)`

**7.** Tell a process to terminate.

`kill(process, SIGTERM);`

**8.** Receive the exit status of a child process.

```
int status;
waitpid(child, &status, 0);
int exitStatus = WEXITSTATUS(status);
```

### 2. Write the C equivalent, walk.c, to the Python code below (walk.py):

```
#!/usr/bin/env python2.7

import os

for name in os.listdir('.'):
    if os.path.isfile(name):
            print name, os.path.getsize(name)
```



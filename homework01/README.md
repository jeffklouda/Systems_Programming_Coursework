Homework 01
===========

### Activity 1: Permissions & ACLs

**1.**

a. What are the differences in the ACLs for those three folders?

  The ACLs differ in their permissions for nd\_campus, and system:authuser.
My home directory grants l (lookup) permissions to nd\_ campus and system:authuser (authorized users), my Public directory grants rlk (read, lookup, lock) permissions to these two groups, and my Private directory grants permissions to neither of these groups.

b. What ACLs make the `Private` directory private and the `Public` directory public?

  The ACLs for nd\_campus and system:authuser make the directories private or public as the `Private` ACL contains permissions for only me and system administrators while that for `Public` contains permissions for other groups of users (namely nd\_campus and system:authuser).

**2.**

a. What was the result of the command?  That is, were you able to create the specified file?

  I was unable to create the file.  I received a "Permission denied" message from `touch`.

b. Considering this result, which takes precedence on AFS: the Unix permissions or the ACLs?

   Considering  inability to create the file and the fact that the Unix permissions for /web/ (checked with ls -l on /afs/nd.edu/) are rwxrwxrwx, the ACLs take precedence on AFS.

### Activity 2: File Operations

| Command                                       | Elapsed Time |
|-----------------------------------------------|--------------|
| `cp -r /usr/share/pixmaps/ ~/images`          | 1.901s       |
| `mv ./images ./pixmaps`                       | 0.004s       |
| `mv ./pixmaps /tmp/jklouda1-pixmaps`          | 0.860s       |
| `rm -r /tmp/jklouda1-pixmaps`                 | 0.008s       |

**1.** Both renaming and moving the `pixmaps` folder use the `mv` command but the former operation takes significantly less time than the latter.  Explain why this is.

  Using the `mv` command to move the folder required all files in the folder to be copied over to the new location.  Renaming the folder, on the other hand, only changed the name of the folder, which is a less intensive process.

**2.** Similarly, explain why removing the `/tmp/jklouda1-pixmaps` operation is faster than the move operation.

  The `rm` operation was much faster than the `mv` operation because the `rm` operation is only removing the link to the files and their metadata, not actually altering the files themselves which will eventually be written over.

### Activity 3: Redirection

**1.** How would you use I/O redirection to process the `math.txt` file with bc?

  ```
  bc < math.txt
  ```

**2.** How would you use I/O redirection to process the `math.txt` file with bc and save the output to `results.txt`?

  ```
  bc < math.txt > results.txt
  ```

**3.** How would you use I/O redirection to process the `math.txt` file with `bc`, save the output to `results.txt`, and suppress any errors?

  ```
  bc < math.txt > results.txt 2> /dev/null
  ```

**4.** How would you use `cat` and a pipeline instead of I/O redirection to process the `math.txt` file with bc?  Why is this considered less efficient than using I/O redirection?

  ```
  cat math.txt | bc
  ```

  This is less efficient than using I/O redirection because it requires cat to copy the contents of math.txt to the input of bc.  `bc < math.txt` uses only the bc process into which `math.txt` is input directly.

### Activity 4: Pipelines

**1.** Determine how many accounts in the `/etc/passwd` file have `/sbin/nologin` as their shell.

  ```
  grep /sbin/nologin /etc/passwd | wc -l | cat
  ```
  49. `grep` returns all the lines in /etc/passwd containing /sbin/nologin, `wc -l` prints the number of newline chars in the resulting text, and `cat` prints the result.

**2.** Determine how many unique users are logged into the current system.

  ```
  who | sort -u | uniq -w 8 | wc -l | cat
  ```
  8.  `who` lists the users, `sort -u` sorts them by name and removes duplicate lines, `uniq -w 8` merges lines that share the first 8 chars (username), `wc -l` returns the number of newline chars, and `cat` prints the final number.

**3.** Determine the top 5 largest files or directories in the `/etc` directory while suppressing any errors.

  ```
  ls -Shl /etc 2> /dev/null | head -n 6 2> dev/null | cat
  ```
  termcap, prelink.cache, services, ld.so.cache, and Muttrc.  `ls -Shl` lists the files and directories in `/etc` by size in human readable format in long-listing form, `head` passes the first 6 lines of the resulting list (the first being the total size of /etc), and `cat` prints the results, the five largest files in /etc with their long-listing information.

**4.** Determine how many instances of `bash` are running on the current machine.

  ```
  ps -e | grep bash | wc -l | cat
  ```
  4. `ps -e` lists all the processes on the system, `grep` returns only the lines containing "bash", `wc -l` returns the number of newline chars in the resulting text, and cat prints the final number.

### Activity 5: Processes & Signals

**1.** Using a single window, run the `TROLL` program and figure out a way to terminate it:

a. Describe what commands or operations failed to terminate the process.

Using ctrl + c failed to terminate the process.  After suspending the process, passing the INT and TERM signals also failed to terminate it.

b. Describe what commands or operations finally succeeded in terminating the process.

I terminated the process using ctrl + z to suspend the program and then `killall -9 TROLL` to pass the KILL signal to the process.  I could have also used `ps` to find the `TROLL` pid and then pass the signal to it using the `kill` command. 

**2.** Using two terminal windows, run the `TROLL` program in the first window and figure out a way to terminate it from the second terminal window.

a. Describe a pipeline that can be used to terminate the process from the second window.

  I can use `ps ux | grep TROLL | awk '{print $2}'` to get the process id for `TROLL` and pass that to the kill command with `kill -9 $(ps ux | grep TROLL | awk '{print $2}')`.

b. Describe a single command that can be used to terminate the process from the second terminal window.

  `killall -9 TROLL` successfully terminates the process from the second terminal window.

**3.** Explore passing different signals to the `TROLL` program. Which ones lead to interesting messages that are not taunts or insults?

  Sending SIGALARM causes `TROLL` to quote song lyrics about time,  SIGUSR1 causes it to run `cmatrix`, printing random green chars Matrix style, and SIGUSR2 causes it to run what appears to be an ASCII version of the entire Star Wars movie.

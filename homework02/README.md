Homework 02
===========

### Activity 1: Saving the World (extract.sh)

**1.** How did you check and handle having no arguments?

I checked for no arguments with an if statement at the beginning of my script.  The script tests if 
`${#}` (the number of arguments) is equal to `0`.  If it is, then the script `echo`s the usage message
and the script ends and returns an error code 1 with `exit 1`.

**2.** How did you determine which command to use for each argument?

The script determines which command to use for each argument in a case statement that runs while 
`"${#}" -gt "0"`.  The case statement matches `${1}` to each supported file extension preceded by a 
wildcard `*`.  This means that any argument that ends in a specified file extension will run the
command in that block.  The final case in the sctructure is `*)` which exists to identify and alert the 
user to arguments that are not supported.

**3.** What was the most challenging aspect of writing this scipt?
The most challenging aspect of writing this script was determining which commands to use to extract each
type of archive. (eg. `tar -xzf *.tar.gz`)  I was able to overcome this challenge through research in
the *The Linux Command Line* and on Google.

### Activity 2: Predicting the Future

**1.** How did you display random messages to the user?

To display random messages to the user, I used the `shuf` command on the list of phrases provided.
I piped the output of this command to `head -n 1` to get just the top message from the randomized list
and then piped the output of that to `cowsay` to have the cow say the message to the user.

```
shuf << EOF | head -n 1 | $COWSAYPATH
```

**2.** How did you handle signals?

I trapped the signals by running the `trap signal_exit INT HUP TERM` command in my while loop.  The
first argument is the function I wrote which displays the alternate exit message and ends the sctipt
with error code 1, and the other arguments are the signals that will cause the function to execute.

**3.** How did you read input from the user?

I read input from the user with the `read -p "Question?" QUESTION` command.  This command reads input
from the user and saves it to the QUESTION variable.  QUESTION is tested in the while loop to determine
if the user should be prompted again.  The `read` command will execute whenever QUESTION is empty.  The
`-p "Question? "` flag prints "Question? " to the command line when prompting the user.

**4.** What was the most challenging aspect of writing this script?

The most challenging part of writing this script was randomizing the output message.  I was having
trouble implementing the `shuf` command and getting the output to be displayed by cowsay.  The biggest
problem I encountered was `shuf` being unable to find `EOF` at the end of my messages because I had 
`EOF` indented.  Once I discovered the issue by Googling my error message, the issue was easily fixed
by removing the space before my `EOF`.

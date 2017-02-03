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

### Activity 3: Meeting with the Oracle

1. My first step was to scan `xavier.h4x0r.space` for an HTTP port:

    ```
    $ nc -z xavier.h4x0r.space 9000-9999
    Connection to xavier.h4x0r.space 9097 port [tcp/*] succeeded!
    Connection to xavier.h4x0r.space 9111 port [tcp/*] succeeded!
    Connection to xavier.h4x0r.space 9876 port [tcp/sd] succeeded!
    ```

    As can be seen, there are 3 ports in the 9000-9999 range.

2. Next, I tried to access the HTTP server:

    ```
    nc xavier.h4x0r 9097
    nc xavier.h4x0r 9111
    nc xavier.h4x0r 9876
    ```
    
    Port 9111 was the only port that returned a response.  It prompted me for a name and a message
    before telling me to "go back to the DOORMAN or BOBBIT".

3. Next I tried using `curl` to access the surver

    ```
    curl xavier.h4x0r 9097
    curl xavier.h4x0r 9111
    curl xavier.h4x0r 9876
    ```

    Port 9097 returned html content, 9111 returned the same messages as before but now filled with
    what I think is information provided by the curl command, and 9876 returned the following message:

    ```
     Halt! Who goes there?                  \
     |                                        |
     | If you seek the ORACLE, you must come  |
     | back and _request_ the DOORMAN at      |
     | /{NETID}/{PASSCODE}!                   |
     |                                        |
     | To retrieve your PASSCODE you must     |
     | first _find_ your LOCKBOX which is     |
     | located somewhere in                   |
     | ~pbui/pub/oracle/lockboxes.            |
     |                                        |
     | Once the LOCKBOX has been located, you |
     | must use your hacking skills to        |
     | _bruteforce_ the LOCKBOX program until |
     | it reveals the passcode!               |
     |                                        |
     \ Good luck!                             /
     ```

4. Next, I used ls on ~pbui/pub/oracle/lockboxes to locate the PASSCODE:

    ```
    ls ~pbui/pub/oracle/lockboxes
    jklouda1.lockbox
    02593f82  21682708  366cd202  5c410beb  6c36ba66  89fd3b2a  a981be49  c3a3962a  d735612d  ee376659
    03c791ec  2487bfa4  37066d9b  5c9de217  6e627427  8eb492d8  ad5926d2  c5160fa5  d8240ce1  ee936007
    05ceac3e  25774ca7  37e047d7  5ce49eb7  6fa89e65  8f66e26a  ada4e6a9  c65aa523  da412c5e  efa53cee
    07af0940  26aa3a18  37ee344f  5d443d6f  714273b5  915208cd  adc138e7  c673f845  db591b1a  f0e027d4
    09614a13  270bd30c  38b013b4  5d449fa4  73cef19a  92256177  ae9792e4  c6ce31f5  dca22610  f2060995
    0c360a39  2713d451  3b29284b  5e784d55  75099e30  923343b7  aee0505f  c6d66e07  dcbe76ba  f5a049be
    0e2077a0  292053f2  3b9cc08f  6021ca64  796c5810  932d42db  af0abfc6  c8c0c8f2  deccbd53  f851b94f
    11928dbd  2946742c  3bf15193  61a11f65  7a07896b  9583fc3f  b4023b8d  c9a15469  e124f6cb  f85949cd
    134305d8  29cb1abe  3d96059f  627e5f68  7d8849c3  95a10690  b460161a  ca75fe8d  e15b654d  f9435329
    13f10e32  2b5e6b0b  4009dad1  64eab726  7e54e151  95abb267  b51dccf8  caa65aa9  e57e8bcb  f9607366
    148537d8  2c305470  4144d332  6650fa05  803562b4  972dfa15  b87967c8  cd7e8868  e59ace2e  f986ef28
    16e5ed1b  2d01449b  443be000  673c8683  84626ba9  998dbcac  bbf320ee  cdc03cbc  e5cd1b09  f9c4e15a
    1764ed35  2d8663b0  5237747d  68ada0b1  872ca2c2  9d0fa52e  bc95089b  cfa75d1a  e636c312  fab79d41
    17ac8064  2d8c5740  52604dae  6a5062df  877c28fa  a084e523  bd065da6  d06bfc5f  e75d0a3d
    19451533  2db7d43d  545a1014  6af5c415  87c3351a  a2eb9485  becd9817  d39238d3  e7ef024d
    1d45daa3  3096b5a5  5aabdb3e  6b3c539e  8829c8bc  a2ec7b21  bef69ac1  d3a253fb  ebe15774
    20a720a5  35d91ffd  5ac56972  6bff9d3c  889c7ec1  a7a98f42  c01a573d  d41574af  ee225bd4
    ```

    Not very helpful.

5. Next, I ran find on the directory to look for files with my NETID:

    ```
    find ~pbui/pub/oracle/lockboxes | grep jklouda1
    ```
    
    This returned dozens of files, but one of them was

    ```
    /afs/nd.edu/user15/pbui/pub/oracle/lockboxes/cdc03cbc/30fde1a6/717c2a0a/16c4ac94/jklouda1.lockbox
    ```

6. I tried to run the file, but it required a password, so I wrote a script to break the code:

    ```
    #!/bin/sh

    while [ ${#} -gt -0 ]
    do
        ./jklouda1.lockbox ${1}

        shift
    done
    ```

    This allowed me to bruteforce the lockbox by trying all possible passwords one at a time on the
    file.

    ```
    ~/cse-20289-sp17-assignments/homework02/breakdacode.sh $(strings jklouda1.lockbox)
    ```

    Returned

    ```
    2970101855b2811f57b20e4f122529b0
    ```

7. I didn't know what to do with this code, but everyone else was entering it on slack, so I sent a private message to Bobbit:

    ```
    !verify jklouda1 2970101855b2811f57b20e4f122529b0
    ```

    and received:

    ```
    Hi jklouda1! Please tell the ORACLE the following MESSAGE: d3h5YmhxbjE9MTQ4NjE2NTY0Mw==
    ```

8. Finally I returned to the oracle and entered the message I got from Bobbit:

    ```
    nc xavier.h4x0r.space 9111
    ```

    ```
     Ah yes... jklouda1!                   \
     |                                       |
     | You're smarter than I thought. I can  |
     | see why the instructor likes you.     |
     |                                       |
     | You met BOBBIT about 0 minutes ago... |
     \ What took you so long?                /

     Hmm... Sorry, kid. You got the gift, \
     | but it looks like you're waiting for |
     | something.                           |
     |                                      |
     | Your next life, maybe. Who knows?    |
     \ That's the way these things go.      /

     Congratulations jklouda1! You have reached the end of this journey.
    ```

    I was congratulated on my efforts and sent on my way.

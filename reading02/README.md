Reading 02
==========

**1.** How would you run the script even though it is not executable?

`sh exists.sh {argument}` can be used to run the script.

**2.** How would you make this script executable?

`chmod 755 exists.sh` would change the permissions on the script such that I would be able to execute it.

**3.** Once the script is executable, how would you run it directly?

`./exists.sh {filename}`

**4.** What is the purpose of the line `#!/bin/sh`?

This line specifies that the file should be executed by `/bin/sh`.

**5.** What is the output of the script if you run it with the arguments `*`?

`README.md exists!` because the `*` argument passes all the files in the directory to the script, but only the first argument is tested by the script.

**6.** What is the `$1` that appears in the script?

This variable is the first argument passed to the script.

**7.** What does `test -e "$1"` do?

This portion of the script tests whether or not the file $1 exists, allowing the code in the `if` statement to run if it does.

**8.** What does this script do?

This script tests whether or not a specified file exists, returning "{filename} exists!" if it does and "{filename} does not exist!" if it does not.

Write a new version of `exists.sh` with the folowing modifications:

1. Use [ instead of test for the conditional

2. Test every command line argument (one at a time)

3. Return an error code if one of the tests fails.

4. Display an error message and exit with an error if no arguments are given.

```
if [ "${#}" = "0" ] ; then
    echo "Error: no arguments given"
    exit 1
else
    while [ "${#}" -gt "0" ]
    do
        if [ -e "${1}" ] ; then
            echo "${1} exists!"
        else
            echo "${1} does not exist!"
            exit 1
        fi
        shift
    done
fi
```

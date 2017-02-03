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

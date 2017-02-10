Homework 03
===========

I collaborated with gking5 and mdalonz1 on this assignment.

### Activity 1: Caesar Cipher

**1.** How did you parse the command line arguments?

To parse the command line arguments, I simply checked if the first argument was a "-h" flag with an
if statement to determine if the usage message should be displayed.  Otherwise, I set my KEY (which
I use to shift the letters) variable to the first argument `$1`.

**2.** How did you construct the source set?

The source set is just the the lowercase and uppercase letters, so I used [a-z] and [A-Z] as the
source sets.

**3.** How did you construct the target set?

To perform the Caesar Cipher transformations, I needed to shift each letter to the next one, so I
used [b-za] as my target set for [a-z] and [B-ZA] as my target set for [A-Z].

**4.** How did you use these sets to perform the encryption?

I used two tr commands to perform the encryption.  The first `tr [a-z] [b-za]` to shift the 
lowercase characters and `tr [A-Z] [B-ZA]` to shift the uppercase characters.  `tr` maps the
source sets to the target set, effectively shifting each letter ot the next letter in the alphabet.
I performed these two `tr` commands on the input text the number of times specified in the command
argument to perform the encryption.

### Activity 2: Broification

**1.** How did you parse the command line arguments?

I parsed the command line arguments using a while loop. In the loop, I used the shift command to
move through the command line arguments.  When it finds a `-d` flag in the first argument, the 
script set its delimiter variable `DELIM` to the second argument `$2`, and when the shell finds a 
`-W` flag, it sets the `STRIP` variable to 0.

**2.** How did you remove comments?

To remove comments I used the command `sed -r "s|${DELIM}.*||"`.  This command finds all instances
of the comment delimiter `DELIM` followed by 0 or more of any other character and replaces that
sequence with nothing.  Removing all comments starting with the delimiter.

**3.** How did you remove empty lines?

To remove empty lines, I used the command `sed -r "/^$/d"`.  This command finds all instances of
`^$`, which is the begining of a line next to the end of a line and deletes them.  Since this
only occurs in empty lines, this will remove all empty lines in a file.

**4.** How do the command line options affect your operations above?

The command line option `-W` sets the `STRIP` variable, which is 1 by default, to 0.  When `STRIP`
is equal to 1, the script runs the `sed` command to remove empty lines, otherwise it only runs the
commands to remove comments and delete the whitespace at the end of lines.

### Activity 3: Zip Codes

**1.** How did you parse the command line arguments?

I used the same method for parsing the command line arguments in this script as I did in the 
broify.sh script.  I used a while loop and the shift command to imcrement through the command
line arguments, and whenever I found an argument that needed to be saved (`STATE`,`FORMAT`, and
`CITY`) I set the second command line argument to the appropriate variable and called the `SHIFT`
command again.  I also printed the usage information and called `exit 1` when the `-h` flag was found.

**2.** How did you extract the zip codes?

To extract the zip codes, I first looked at the html document from the zipcodestogo website to see 
how the zipcodes were formatted on the page.  I saw that each zipcode was stored between forward 
slashes following the state's abbreviation (eg. IN/46556/) so I used `grep -Eo "/[A-Z]{2}/[0-9]*/"` to
find the zipcodes and then `grep -Eo "[0-9]+" | sort | uniq` to get zipcodes alone and remove
potential repeats.

**3.** How did you filter by `STATE` and `CITY`?

To filter by state, I used the `STATE` variable at the end of the zipcodestogo url to download the
data for that state.  To filter by city, I used `grep -E "/$CITY/` to get just the lines for that 
city. It was necessary to include the slashes to exclude false matches based on partial city names 
such as in the case of the "Orange" test in `test_zipcode.sh`.

**4.** How did you handle the `text` and `csv` `FORMAT` options?

By default, the command I used output the list as a zipcode per line so is the `FORMAT` variable was
not set to "csv" then I would just run the commands normally.  When `$FORMAT = "csv"`, I run the
same pipeline with the additional command `awk -vORS=, '{ print }' | sed "s/,$/\n/"`.  This `awk` 
command changes the output so that it is separated by commas rather than newlines. and the `sed` 
command removes all commas followed by the end of a line, replacing them with newlines.  This removes
the final `,` at the end of the output.

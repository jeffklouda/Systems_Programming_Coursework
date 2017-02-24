Homework 04
===========

### Activity 1: Blend Profiles

**1.** To parse the command line arguments, I used the while loop given in
the starter code.  This loop cycles through all of the arguments that begin
with '-'. popping the first argument to `arg`.  I used `if` and `elif` 
statements to check for the expected flags `-r`, `-d`, and `-s` and, upon
finding each of these, I either set `REVERSE` to `True` for the `-r` arg or
popped the next argument to the respective `DELAY` and `STEPSIZE` variables.
I used an `else` statement to catch all other inputs and display the usage
message with the `usage()` function.  

**2.** To manage the temporary workspace, I used the `tempfile.mkdtemp()`
function to create a tempoarary directory and set `TEMPPATH` to the path of
that directory.  I also set `ORIGPATH` to the path to the directory where
blend.py is stored.  I then used `os.chdir(TEMPPATH)` to move into the
temporary directory so that all generated files would be stored in 
`TEMPPATH`.  After generating the final .gif I used the `os.system()` method
to call `mv target ORIGPATH`, moving the .gif outside of the temp directory.
I used the `atexit.register()` method to call my `clean_up` function upon 
exiting the program.  `clean_up()` displays a message about deleting the 
directory before running `shutil.rmtree(TEMPPATH)` to remove the temp 
directory and its contents.

**3.** To extract the portrait URLS I set my `regex` variable to:
```
'https://engineering.nd.edu/profiles/{}/.*\.(?:jpeg|png)'.format(netid)
```
which is the format of the images in the profile pages.  I used this with
the `re.findall()` function to search through the URL of the profile page
itself, which I downloaded using `requests.get(url)` after setting `url` to
`'https://engineering.nd.edu/profiles/{}'.format(netid)`.  The `re.findall`
method using the regex and the result of `requests.get` return the URL of 
the image if it is on the page.

**4.** Once I found the URL of the portrait images, I downloaded them using
the `img = requests.get(url)`. I then saved the image by opening a file
at a given path as `output` and running `output.write(img.content)`.

**5.** Once I saved the images as img1 and img2 I was able to generate the
blended composite images using the following `for` loop.
```
for perc in range (00, 110, 10):
    
    command = 'composite -blend {} {} {} {}-{}_{}.gif'.format(perc,
        img1, img2, '{:03d}'.format(perc), netid1, netid2)

    os.system(command)
```
This loop uses the composite -blend command to create the blended images
named in the `000-netid1_netid2.gif` format at every ten percent of 
combination between the images.

**6.** To generate the final image, I used the following code:
```
gif_list = ''
print "Generating {}... ".format(target),
if REVERSE == True:
    for i in range (00, 110, 10):
        gif_list += '{}-{}_{}.gif '.format('{:03d}'.format(i), netid1,
        netid2)
    for i in range (100, -10, -10):
        gif_list += '{}-{}_{}.gif '.format('{:03d}'.format(i), netid1,
        netid2)

else:
    for i in range (00, 110, 10):
        gif_list += '{}-{}_{}.gif '.format('{:03d}'.format(i), netid1,
        netid2)

command = 'convert -loop 0 -delay {} {} {}'.format(DELAY, gif_list,
target)
os.system(command)
```
This code stores the name of every image to be used in creating the gif in
the `gif_list` list by using the for loops to capture the names of all of the
previously generated images.  If `REVERSE` is true, then the images need to
go back down from 100 to zero, so a second for loop adds the images to the
list again, but in the reverse order.  Once the list is complete, it is used
in the `command` variable and the `convert` command is run using `os.system`
to generate the final .gif.

**7.** I checked for failure when downloading the profile page and when 
downloading the images.  For each, I checked whether or not the result of
`requests.get()` was an empty list using `not`.  If the list did not exist,
then I printed an error message and used `sys.exit(1)` to end the program
with an error code.

### Activity 2: Grep Reddit

**1.** I parsed the command line arguments for this activity very similarly
to how I did so for the first activity.  I set `args = sys.argv[1:]` to 
store the command line arguments in `args`.  I then wrote a for loop that
runs while `len(args)` meaning is still data in `args` and 
`args[0].startswith('-')` meaning the next argument is a flag.  I then
captured the first argument from `args` and removed it from the list using
`arg = args.pop(0)` before matching it to one of the expected flags with if
and elif statements.  When the program finds one of these flags it removes
the next argument form the list and sets it to the appropriate variable 
(eg. `FIELD = args.pop(0)`).  If the flag is -h or is not recognized, then
the usage message is displayed.  Finally, I set the `REGEX` search variable
assigning the next argument to `REGEX` if `args` is not empty after running
the while loop.

**2.** I fetched the JSON data for the appropriate page by calling
`requests.get` on the page along with the provided headers data.  I then 
assigned the JSON data of this page to the `data` variable with `data = 
response.json()` where response is the output of the `requests.get` method.
I then iterated through the articles on the page with the for loop `for 
resource in data['data']['children']:`.  This cycles through the `children`
list of dictionaries for each article.

**3.** Once the program iterates through the dictionaries for each article,
it is able to filter the article based on the `FIELD` and `REGEX` using the
`re.search(REGEX, resource['data'].get(FIELD, None))` function.  This
searches the approriate field in the articles dictionary for the regular 
expression and returns `True` if the regex is found.  I used this in an if
statement to determine whether or not to add each article to my 
`article_list`, which contains the data for all the articles to be displayed.

**4.** To generate the shortened URL, I wrote the following function:
```
def shorten_url(url):
    payload = {'format': 'json', 'url': str(url)}
    response = requests.get('http://is.gd/create.php', params=payload)
    if response.status_code != 200:
        print "Unable to shorten URL!"
        sys.exit(1)
    return response.json().get('shorturl', None)
```
By running `requests.get()` with the parameters stored in `payload`, the 
program receives the shortened URL from is.gd in the form of JSON data.  It
then returns just the URL using `.get('shorturl', None)` on the JSON data to
pick out the URL associated with `shorturl`.

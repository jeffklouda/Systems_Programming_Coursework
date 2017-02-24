#!/usr/bin/env python2.7

import atexit
import os
import re
import shutil
import sys
import tempfile

import requests

# Global variables

REVERSE     = False
DELAY       = 20
STEPSIZE    = 5

# Functions

def usage(status=0):
    print '''Usage: {} [ -r -d DELAY -s STEPSIZE ] netid1 netid2 target
    -r          Blend forward and backward
    -d DELAY    GIF delay between frames (default: {})
    -s STEPSIZE Blending percentage increment (default: {})'''.format(
        os.path.basename(sys.argv[0]), DELAY, STEPSIZE
    )
    sys.exit(status)

def search_portrait(netid):
    regex = 'https://engineering.nd.edu/profiles/{}/.*\.(?:jpeg|png)'.format(netid)
    url = 'https://engineering.nd.edu/profiles/{}'.format(netid)
    print "Searching portrait for {}... ".format(netid),
    response = requests.get(url)
    if not response:
        print "Not Found!"
        sys.exit(1)
    
    url = re.findall(regex, response.text)[0]
    
    print url
    return url

def download_file(url, path):
    print "Downloading {}... ".format(url),
    img = requests.get(url)
    if not img:
        print "Failed!"
        sys.exit(1)
    with open(str(path), 'w') as output:
        output.write(img.content)
    
def clean_up():
    print "Cleaning up workspace: {}".format(TEMPPATH)
    shutil.rmtree(TEMPPATH)

# Parse command line options

args = sys.argv[1:]

while len(args) and args[0].startswith('-') and len(args[0]) > 1:
    arg = args.pop(0)
    if arg == '-r':
        REVERSE = True
    elif arg == '-d':
        DELAY = int(args.pop(0))
    elif arg == '-s':
        STEPSIZE = int(args.pop(0))
    elif arg == '-h':
        usage(0)
    else:
        usage(1)

if len(args) != 3:
    usage(1)

netid1 = args[0]
netid2 = args[1]
target = args[2]

# Main execution

# Create workspace
TEMPPATH = tempfile.mkdtemp()
ORIGPATH = os.getcwd()

print "Using workspace: {}".format(TEMPPATH)

os.chdir(TEMPPATH)

# Register cleanup
atexit.register(clean_up)

# Extract portrait URLs
url1 = search_portrait(netid1)
url2 = search_portrait(netid2)

# Download portraits
img1 = netid1 + '.jpeg'
img2 = netid2 + '.jpeg'

download_file(url1, str(img1))
download_file(url2, str(img2))

# Set imagemagick path
os.environ['PATH'] = '~ccl/software/external/imagemagick/bin:' + os.environ['PATH']

# Generate blended composite images
for perc in range (00, 110, 10):
    
    print "Generating {}-{}_{}.gif... ".format('{:03d}'.format(perc), netid1,
    netid2),

    command = 'composite -blend {} {} {} {}-{}_{}.gif'.format(perc, 
    img1, img2, '{:03d}'.format(perc), netid1, netid2) 
    
    os.system(command)
    print "Success!"

# Generate final animation
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

print "Success!"

command = 'mv {} {}'.format(target, ORIGPATH)
os.system(command)

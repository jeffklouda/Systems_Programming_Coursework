#!/usr/bin/env python2.7

import requests
import os
import sys
import re

FIELD = 'title'
LIMIT = 10
SUBREDDIT = 'linux'
REGEX = ''

def download_page(subreddit='linux'):
    headers  = {'user-agent': 'reddit-{}'.format(os.environ['USER'])} 
    page = 'https://www.reddit.com/r/{}/.json'.format(subreddit)
    print "Downloading {}...".format(page),
    response = requests.get(str(page), headers = headers)
    if response.status_code != 200:
        print "Page not found!"
        sys.exit(1)
    print "Success!"
    return response

def usage(status=0):
    print '''Usage: {} [ -f FIELD -s SUBREDDIT ] regex
        -f FIELD        Which field to search (default: {})
        -n LIMIT        Limit number of articles to report (default: {})
        -s SUBREDDIT    Which subreddit to search (default: {})'''.format(
            os.path.basename(sys.argv[0]), FIELD, LIMIT, SUBREDDIT
        )
    sys.exit(status)

def shorten_url(url):
    payload = {'format': 'json', 'url': str(url)}
    response = requests.get('http://is.gd/create.php', params=payload)
    if response.status_code != 200:
        print "Unable to shorten URL!"
        sys.exit(1)
    return response.json().get('shorturl', None)

# Parse the command line options

args = sys.argv[1:]

while len(args) and args[0].startswith('-'):
    arg = args.pop(0)
    if arg == '-h':
        usage(0)
    elif arg == '-f':
        FIELD = args.pop(0)
    elif arg == '-n':
        LIMIT = args.pop(0)
    elif arg == '-s':
        SUBREDDIT = args.pop(0)
    else:
        usage(1)

if len(args):
    REGEX = args.pop(0)

# Download json data

response = download_page(SUBREDDIT)
data = response.json()

article_list = [] # empty list for artice data

# Add articles contating search REGEX to list

for resource in data['data']['children']:
    if re.search(REGEX, resource['data'].get(FIELD, None)):
        article_list.append(resource['data'])
    if len(article_list) >= int(LIMIT):
        break 

# Print data on articles

for index, article in enumerate(article_list):
    index = index + 1
    title = article.get('title', None)
    author = article.get('author', None)
    link = 'https://reddit.com' + article.get('permalink', None)
    short = shorten_url(link)
    print '''
    {}. Title:  {}
        Author: {}
        Link:   {}
        Short:  {}'''.format('{0: >2}'.format(index), title, author, link, 
            short)

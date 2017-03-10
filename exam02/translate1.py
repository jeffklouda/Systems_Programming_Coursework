#!/usr/bin/env python2.7

import re

with open('/etc/passwd', 'r') as input:
    data = input.readlines()

fields = [line.split(':')[4] for line in data]

regex = '[uU]ser'

results = sorted([word.lower() for word in fields if re.search(regex, word)],
    key=lambda x: re.sub('[^A-Za-z]+', '', x).lower())

for result in results:
    print result

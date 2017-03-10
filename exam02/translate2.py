#!/usr/bin/env python2.7

import requests
import re

url = 'http://yld.me/aJt?raw=1'

r = requests.get(url)

regex = '[0-9]{3}-[0-9]{3}-[0-9]{3}[13579]'

results = re.findall(regex, r.text)

for result in results:
    print result

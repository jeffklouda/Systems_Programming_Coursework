#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

import sys
import string
import re

punct = re.sub(r'-', '', string.punctuation)
punct = punct + '’' + '”' + '“' + '—'

for index, line in enumerate(sys.stdin):
    for word in line.strip().split():
        word = word.translate(None, punct)
        print '{}\t{}'.format(word.lower(),index+1)

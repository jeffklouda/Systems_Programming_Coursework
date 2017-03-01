#!/usr/bin/env python2.7

import sys

def evens(stream):
    for n in stream:
        n = n.strip()
        if int(n)%2 == 0:
            yield n

print ' '.join(evens(sys.stdin))

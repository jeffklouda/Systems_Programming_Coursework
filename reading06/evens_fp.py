#!/usr/bin/env python2.7

import sys

print ' '.join(filter(lambda n: int(n)%2 == 0, map(lambda n: n.strip(), sys.stdin)))

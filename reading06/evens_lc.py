#!/usr/bin/env python2.7

import sys

print ' '.join([n.strip() for n in sys.stdin if int(n)%2 == 0 ])

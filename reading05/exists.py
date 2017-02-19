#!/usr/bin/env python2.7

import sys
import os

for arg in sys.argv[1:]:
    if os.path.isfile(arg):
        print arg, 
        print "exists!"
    else:
        print arg,
        print "does not exist!"
        sys.exit(1)        


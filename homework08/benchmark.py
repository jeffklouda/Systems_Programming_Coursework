#!/usr/bin/env python2.7

import subprocess

print "|   NITEMS   |   ALPHA    |    TIME    |   SPACE    |"
print "|------------|------------|------------|------------|"

for NUM in [1, 10, 100, 1000, 10000, 100000, 1000000, 10000000]:
    for ALPHA in [0.5, 0.75, 0.9, 1.0, 2.0, 4.0, 8.0, 16.0]:
        p = subprocess.Popen('shuf -i1-{} -n {} | ./measure ./freq -l {}'.format(NUM, NUM, ALPHA), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        
        out, err = p.communicate()
        err = err.split();
        print "|",
        print " "*(9-len(str(NUM))), NUM,
        print "|",
        print " "*(9-len("%.2f" % ALPHA)), "%.2f" % ALPHA,
        print "|",
        print " "*(9-len("%.2f" % float(err[0]))), "%.2f" % float(err[0]),
        print "|",
        print " "*(9-len("%.2f" % float(err[2]))), "%.2f" % float(err[2]),
        print "|"
        

        
        #print erreconds        0.585938 Mbytes

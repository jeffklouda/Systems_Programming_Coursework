#!/usr/bin/env python2.7
import sys

# store input in set to remove duplicates
lineNums = set()
for line in sys.stdin:
    lineNums.add(line.strip())

numVals = {}

# group input line numbers by word in dictionary
for item in sorted(lineNums):
    k, v = item.split('\t', 1)
    if k in numVals:
        numVals[k] = numVals.get(k).strip() + ' ' + str(v).strip()
    else:
        numVals[k] = str(v).strip()

# sort numbers
for k, v in numVals.items():
    nums = []
    for num in v.split():
        nums.append(num)
    numVals[k] = ' '.join(sorted(nums,key=int))

# print output
for k, v in sorted(numVals.items()):
    print '{}\t{}'.format(k,v)

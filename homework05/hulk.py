#!/usr/bin/env python2.7

import functools
import hashlib
import itertools
import multiprocessing
import os
import string
import sys

# Constants

ALPHABET    = string.ascii_lowercase + string.digits
ARGUMENTS   = sys.argv[1:]
CORES       = 1
HASHES      = 'hashes.txt'
LENGTH      = 1
PREFIX      = ''

# Functions

def usage(exit_code=0):
    print '''Usage: {} [-a alphabet -c CORES -l LENGTH -p PATH -s HASHES]
    -a ALPHABET Alphabet to use in permutations
    -c CORES    CPU Cores to use
    -l LENGTH   Length of permutations
    -p PREFIX   Prefix for all permutations
    -s HASHES   Path of hashes file'''.format(os.path.basename(sys.argv[0]))
    sys.exit(exit_code)

def md5sum(s):
    # Generate MD5 digest for given string.

    m = hashlib.md5(s)
    return m.hexdigest()

def permutations(length, alphabet=ALPHABET):
    # Yield all permutations of alphabet of specified length.
    for letter in alphabet:
        if (length > 1):
            subset = permutations(length - 1, alphabet)
            strings = map (lambda x: letter + x, (list(subset)))
            for string in strings:
                yield string
        
        elif (length == 1):
            yield letter

def smash(hashes, length, alphabet=ALPHABET, prefix=''):
    # Return all password permutations of specified length that are in hashes
    return list(prefix + str(password) for password in permutations(length, alphabet) if md5sum(prefix + str(password)) in hashes)


# Main Execution

if __name__ == '__main__':
    # Parse command line arguments
    args = ARGUMENTS

    while len(args) and args[0].startswith('-') and len(args[0]) > 1:
        arg = args.pop(0)
        if arg == '-a':
            ALPHABET = args.pop(0)    
        elif arg == '-c':
            CORES = int(args.pop(0))
        elif arg == '-l':
            LENGTH = int(args.pop(0))
        elif arg == '-p':
            PREFIX = args.pop(0)
        elif arg == '-s':
            HASHES = args.pop(0)
        elif arg == '-h':
            usage(0)

    # use multiprocessing
    pool = multiprocessing.Pool(CORES)

    # Load hashes set
    hashSet = set() 
    with open(str(HASHES), 'r') as input:
        for item in input:
            hashSet.add(item.strip())    
    
    # Execute smash function to get passwords
    if CORES > 1 and LENGTH > 1:
        if LENGTH > 3:
            LEN = LENGTH - 3
            subset = 3
        else:
            subset = LENGTH - 1
            LEN = 1 
        
        subsmash = functools.partial(smash, hashSet, subset, ALPHABET)
        passwords = itertools.chain.from_iterable(pool.imap(subsmash, list(map(lambda x: PREFIX + x, permutations(LEN,ALPHABET)))))
        
    else:
        passwords = smash(hashSet, LENGTH, ALPHABET, PREFIX)
    
    for password in passwords:
        print password

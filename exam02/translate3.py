#!/usr/bin/env python2.7

import os

ps = os.popen('ps aux')

users = []

for line in ps:
    users.append(line.split(' ')[0])

users = set(users)

x = 0

for user in users:
    x = x+1

print x

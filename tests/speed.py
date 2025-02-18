#!/usr/bin/env python3
import time

TIME_LIMIT = 3
start = time.time()

class Integer(object):
    def __init__(self, value):
        self.value = value

    def getv(self):
        return self.value

x = 0
for i in range(10):
    l = [Integer(range(10)[i % 10]) for i in range(10)]
    x += sum(map(Integer.getv, l))

stop = time.time()
exec_time = stop - start
print(exec_time)

if exec_time > TIME_LIMIT:
    exit(1)

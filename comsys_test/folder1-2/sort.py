#!/usr/bin/python

import ctypes, time

start_time = time.time()
result = ctypes.CDLL('./sort.so')
result.insertion()
print "Elapsed time: ", (time.time() - start_time)

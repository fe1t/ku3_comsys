#!/usr/bin/python

import ctypes, numpy as np, time

start_time = time.time()
with open('../mat100.dat', 'rb') as f:
    matrix = [[int(y) for y in x]for x in map(lambda x: x.split(), f.readlines()[1:])]

mx = np.matrix(matrix)

print "Elasped time: ", time.time() - start_time

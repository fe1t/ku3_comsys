#!/usr/bin/python

import ctypes, time

filename = '../mat1000.dat'

start_time = time.time()
result = ctypes.CDLL('./3.1.so')
result.mul_matrix(filename)
print "Elapsed time: ", (time.time() - start_time)

# print matmult(matrix, matrix)[99]



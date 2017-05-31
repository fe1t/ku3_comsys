#!/usr/bin/python

import ctypes, time

filename = '../mat1000.dat'

def matmult(a,b):
    zip_b = zip(*b)
    [[sum(ele_a*ele_b for ele_a, ele_b in zip(row_a, col_b)) for col_b in zip_b] for row_a in a]
    # return [[sum(ele_a*ele_b for ele_a, ele_b in zip(row_a, col_b)) for col_b in zip_b] for row_a in a]

with open(filename, 'rb') as f:
    matrix = [[int(y) for y in x]for x in map(lambda x: x.split(), f.readlines()[1:])]

start_time = time.time()
# print matmult(matrix, matrix)
matmult(matrix, matrix)

print "Elapsed time: ", time.time() - start_time

This directory contains serial codes written in the C programming language.
It contains main function that calls each mathematical function and mathematical functions that performs three operations such as:

1. vector-vector multiplication, a function that calculates a the dot product of two vectors.
2. Matrix-vector multiplication, a function that also multplies a matrix and a vector.
3. Matrix-Matrix multiplication, a functiot that also multiplies two mxn square matrics.

The matrix being multiplied should be a square matrix m x n where the value of m and n is obtained from the command line.

Each function contains a time function that is used to time its operations.
The code is run from a makefile by running "make run".
The code when run, tests for the time-to-solution of all the operations whiles doubling the values of N: from 5000, 10000, 20000, and 40000.
The value o
The result is writen a data file "8597421_serial.txt".

A ploting script that is written within the makefile is run when the code is run by "make run" and a image plot is generated.


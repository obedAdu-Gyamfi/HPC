#ifndef VECTOR_H
#define VECTOR_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>


extern double start;
extern double end;
extern double *t_used;

#define SPACE 15
#define N 4

double vector_vector(int m, int n, double * vecA, double *vecB);



#endif

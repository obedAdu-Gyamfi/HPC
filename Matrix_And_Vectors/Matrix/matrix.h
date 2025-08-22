#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <string.h>

#define N 4
#define SPACE 15

extern clock_t start;
extern clock_t end;
extern double *t_used;

void matrix_vector(int m, int n, double *matA, double *vecA, double *matB);
void matrix_matrix(int m, int n, double *matA, double *matB, double *matC);


#endif

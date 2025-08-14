#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N

void matrix_vector(int m, int n, double *matA, double *vecA, double *matB);
void matrix_matrix(int m, int n, double *matA, double *matB, double *matC);


#endif

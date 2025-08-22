#include "matrix.h"

/**
 * Author: Obed Adu-Gyamfi
 * Email: aduigyamfiobed.tpp3@gmail.com
 * github: @obedAdu-Gyamfi
 */

/*
 * matrix_vector - A function the performs a  matrix vector multiplication
 *
 * Description: This function accepts a matrix and a vector multiplies the matrix and vector.
 *
 * @m: Size or Dimension of the matrix A
 * @n: Size of Dimension of the Vector B
 * @matA: A pointer to an mxm matrix, matrix A
 * @vecA: A pointer to the vector A
 * @matB: This is a pointer to the resulting mxm matrix after the matrix vector multiplication.
 *
 * Return: Returns Void
 */

void matrix_vector(int m, int n, double *matA, double *vecA, double *matB){
	//clock_t start, end;
	//double t_used;	
	int i, j;
	start = clock();

	for(i = 0; i < m; i++){
		matB[i] = 0;
		for (j = 0; j < n; j++){
			matB[i] += matA[i * n + j] * vecA[j];
		}
	}
	end = clock();
	t_used = (double *)malloc(sizeof(double));
	if (t_used != NULL){
		*t_used = ((double)(end - start))/CLOCKS_PER_SEC;
	}
	//printf("Matrix Vector operation finished in %lf secs\n", *t_used);
	
}
/**
 * matrix_matrix - This function performs a matrix matrix multipliction.
 *
 * Description: The function performs a matrix matrix multiplication of an mxn square matrix.
 *
 * @m: Size or dimension of matrix A
 * @n: Size or dimension of matrix B
 * matA: A pointer to the matrix A
 * matB: A pointer to the matrix B
 * matC: A pointer to the matrix C and stores the matrix product of matrix A and matrix B.
 *
 * Return: void
 */

void matrix_matrix(int m, int n, double *matA, double *matB, double *matC){
        //clock_t start, end;
        //double t_used;
        start = clock();
        int i, j, k;
        double sum;

        for (i = 0; i < m; i++){
                for (j = 0; j < n; j++){
                        sum = 0;
                        for (k = 0; k < n; k++){
                                sum += (matA[i * n  + k] * matB[k * n + j]);
                        }
                        matC[i * n + j] = sum;
                }
        }
        end = clock();
        t_used = (double *)malloc(sizeof(double));
	if (t_used != NULL){
		*t_used = ((double)(end - start))/CLOCKS_PER_SEC;
	}
	//printf("matrix matrix multiplication finished in %lf secs\n", *t_used);
}




 

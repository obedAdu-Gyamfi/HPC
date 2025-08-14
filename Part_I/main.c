#include "vector.h"
#include "matrix.h"

/**
 * main - Entry point
 * Description: Executes and does functional calls
 * Return: Always 0 on success
 */

int main(int argc, char **argv){
	int i, j;
	int m,n, size;
	double *vecA;
	double *vecB;

	double *matB;
	double *matA;
	double vecans;
	double *matC;
	if (argc != 2){
		fprintf(stderr,"Usage <%s> arg\n",argv[0]);
		exit(-1);
	}
	m = atoi(argv[1]);
	n = m;
	size = m * n;
	vecA = malloc(sizeof(double) * n);
	vecB = malloc(sizeof(double) * n);
	matA = malloc(sizeof(double) * size);
	matB = malloc(sizeof(double) * size);
	matC = malloc(sizeof(double) * size);

	if (matA == NULL || matB == NULL){
	       fprintf(stderr, "Fialed to allocate memory for matrix!\n");
	exit(-1);
	}	
	for(i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			matA[i * n + j] = rand() % 1000;
			matB[i * n + j] = rand() % 1000;
		}
	}

	if (vecA != NULL && vecB != NULL){
		for (j = 0; j < n; j++){
			vecA[j] = rand() % 1000;
			vecB[j] = rand() % 1000;

		}
	}

	matrix_matrix(m, n, matA, matB, matC);
	/*
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			printf("%lf \t", matC[i * n + j]);
		}
		putchar('\n');
	}
	*/
	matrix_vector(m, n, matA, vecA, matB);
	/*
	for (j = 0; j < n; j++){
		printf("%lf\n", matB[j]);
	}*/
	
	vecans = vector_vector(m, n, vecA, vecB);
	//printf("\nVector-Vector product: %lf\n", vecans);
	free(vecA);
	free(vecB);
	free(matA);
	free(matB);
	free(matC);

	return (0);
}


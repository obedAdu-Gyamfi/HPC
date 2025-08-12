#include "vector.h"

/**
 * Name: Obed Adu-Gyamfi
 * E-mail: adugyamfiobed.tpp3@gmail.com
 * github: @obedAdu-Gyamfi
 */

/**
 * vector_vector - A vector-vector multiplication function
 *
 * Description: This function is a serial code that multplies two vectors and returns a scaler
 *
 * @m: This parameter is the dimension of the first vector A
 * @n: This parameter also represents the dimension of the second vector B
 * @vecA: This is a pointer to the first vector A
 * @vecB: This is also a pointer to the second vector B.
 *
 * Return: A double.
 */

double vector_vector(int m, int n, double *vecA, double *vecB){
	double results = 0;
	int i;

	/*
	if (m != n){
		perror("Vectors must have equal dimensions\n");
	}
	*/
	for (i = 0; i <= m; i++){
		results += vecA[i] * vecB[i];
	}
	return (results);
}

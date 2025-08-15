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
	//clock_t start, end;
	double results = 0;
	int i;
	//double t_used;
	start = clock();

	for (i = 0; i <= m; i++){
		results += vecA[i] * vecB[i];
	}
	end = clock();
	t_used = (double *)malloc(sizeof(double));
	if (t_used != NULL){
		*t_used = ((double)(end - start))/CLOCKS_PER_SEC;
	}
	//printf("Vector Vector operations finished in %lf secs\n", *t_used);
	return (results);
}

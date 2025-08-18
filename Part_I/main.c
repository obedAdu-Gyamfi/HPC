#include "vector.h"
#include "matrix.h"
/**
 * Author: Obed Adu-Gyamfi
 * Email: adugyamfiobed.tpp3@gmail.com
 * github: @obedAdu-Gyamfi
 */

/**
 * main - Entry point
 * Description: Executes and does functional calls
 * Return: Always 0 on success
 */
clock_t start;
clock_t end;
double *t_used;

int main(int argc, char **argv){
	int i, j, k;
	FILE *fd;
	char *filename = "8597421_serial.txt";
	int m,n, size;
	double *vecA;
	double *vecB;
	double *matV;

	double *matB;
	double *matA;
	double vecans;
	double *matC;
	fd = fopen(filename, "w");
	if (fd == NULL){
		fprintf(stderr,"Unable to open %s", filename);
		return (1);
	}
	fprintf(fd, "%-*s %-*s %-*s %-*s\n", SPACE, "N", SPACE, "V.V/s", SPACE, "M.V/s", SPACE, "M.M/s");

	if (argc != 2){
		fprintf(stderr,"Usage <%s> arg\n",argv[0]);
		exit(-1);
	}
	m = atoi(argv[1]);
	for (k = 0; k < N; k++){
		n = m;
		size = m * n;
		vecA = malloc(sizeof(double) * n);
		vecB = malloc(sizeof(double) * n);
		matV = malloc(sizeof(double) * n);

		matA = malloc(sizeof(double) * size);
		matB = malloc(sizeof(double) * size);
		matC = malloc(sizeof(double) * size);	

		if (matA == NULL || matB == NULL){
	       		fprintf(stderr, "Fialed to allocate memory for matrix!\n");
			exit(-1);
		}	
		for(i = 0; i < m; i++){
			for (j = 0; j < n; j++){
				matA[i * n + j] = rand() /(double)RAND_MAX;
				matB[i * n + j] = rand()/(double)RAND_MAX;
			}
		}

		if (vecA != NULL && vecB != NULL){
			for (j = 0; j < n; j++){
				vecA[j] = rand() /(double)RAND_MAX;
				vecB[j] = rand() /(double)RAND_MAX;

			}	
		}

			
		vecans = vector_vector(m, n, vecA, vecB);
		fprintf(fd, "%-*d %-*f",SPACE, m, SPACE, *t_used);
		free(t_used);

		matrix_vector(m, n, matA, vecA, matV);
                fprintf(fd, "%-*f", SPACE, *t_used);
                free(t_used);

		
		matrix_matrix(m, n, matA, matB, matC);
                fprintf(fd, "%-*f\n", SPACE, *t_used);
                free(t_used);

		free(vecA);
		free(vecB);
		free(matA);
		free(matB);
		free(matC);
		free(matV);
		m *= 2;
	}
	fclose(fd);
	return (0);
}


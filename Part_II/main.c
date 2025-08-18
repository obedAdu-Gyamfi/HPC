#include "vector.h"
//#include "matrix.h"

/**
 * main - Entry point
 * Description: Executes and does functional calls
 * Return: Always 0 on success
 */
double start; 
double end;
double *t_used;

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	MPI_Status status;
	int rank, nprocs;
	int begin, e, count;
	int s, en, c;
	double *recVecA;
	double *recVecB;
	double vecans;
	double global_time = 0;
	double result;

	int i, j, k;
	FILE *fd;
	char *filename = "8597421_scale.txt";
	int m,n, size;
	double *vecA;
	double *vecB;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	
	if (rank == 0){

		if (nprocs == 1){
			fd = fopen(filename, "w");
			fprintf(fd, "%-*s %-*s %-*s\n", SPACE, "N", SPACE, "Core",SPACE, "V.V/s");

		}
		else {
			fd = fopen(filename, "a");
		}
		if (fd == NULL){
			fprintf(stderr,"Unable to open %s", filename);
			return (1);
		}
		//fprintf(fd, "%-*s %-*s %-*s\n", SPACE, "N", SPACE, "Core",SPACE, "V.V/s");

	}
	if (argc != 2){
		fprintf(stderr,"Usage <%s> arg\n",argv[0]);
		exit(-1);
	}
	m = atoi(argv[1]);
	n = m;
	size = m * n;
	
	begin = (rank * n) / nprocs;
	e = ((rank + 1)*n) / nprocs;
	count = e - begin;
	recVecA = (double *)malloc(sizeof(double) * count);
	recVecB = (double *)malloc(sizeof(double) * count);
	if (rank == 0){
		vecA = (double *)malloc(sizeof(double) * n);
		vecB = (double *)malloc(sizeof(double) * n);
		
		if (vecA != NULL && vecB != NULL){
			for (j = 0; j < n; j++){
				vecA[j] = rand() /(double)RAND_MAX;
				vecB[j] = rand() /(double)RAND_MAX;

			}	
		}
		else{
			fprintf(stderr, "Failed to allocate memory for vectors A and B");
			exit(-1);
		}
		for (i = 1; i < nprocs; i++){
			s = (i * n) / nprocs;
			en = ((i + 1) * n) / nprocs;
			c = en - s;
			MPI_Send(vecA + s, c, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			MPI_Send(vecB + s, c, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
		}
		for (j = 0; j < count ; j++){
			recVecA[j] = vecA[begin + j];
			recVecB[j] = vecB[begin + j];
		}
		free(vecA);
		free(vecB);
	}
	else{
			MPI_Recv(recVecA, count, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
			MPI_Recv(recVecB, count, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
	}
	
	MPI_Barrier(MPI_COMM_WORLD);

	vecans = vector_vector(count, count, recVecA, recVecB);
	
	global_time = end - start;

	MPI_Reduce(&vecans, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0){
		fprintf(fd, "%-*d", SPACE, m);
		fprintf(fd, "%-*d %-*f\n",SPACE, nprocs, SPACE, global_time);
	
		
	}
	
	global_time = 0;
	free(t_used);

	free(recVecA);
	free(recVecB);

	if (rank == 0){
		fclose(fd);
	}
	MPI_Finalize();
	return (0);
}


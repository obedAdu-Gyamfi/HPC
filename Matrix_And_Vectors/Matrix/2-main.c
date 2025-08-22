#include "matrix.h"


int main(int argc, char **argv){

	int rank, nprocs;
	int n, m;
	int i, j;
	int size;
	int s, en, chunk;
	int start, end ,row;
	FILE *fd;
	MPI_Init(&argc, &argv);
	MPI_Status status;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	
	if(argc != 2){
		fprintf(stderr, "Usage: <%s> N\n", argv[0]);
	}
	n = atoi(argv[1]);
	m = n;
	
	start = (rank * n) / nprocs;
	end = ((rank + 1) * n) / nprocs;
	row = end - start;
	double *recM = (double *)malloc(sizeof(double) * row * n);

	double *vecC = (double *)malloc(sizeof(double) * m);
	double *vecB = NULL;
	double *vecA = (double *)malloc(sizeof(double) * n);
	if (rank == 0){
		fd = fopen("8597421_scale.txt", "w");
		fprintf(fd, "%-*s %-*s %-*s",  SPACE, "N", SPACE, "M.V/s", SPACE, "M.M/s");
		size = m * n;
		double *matA = (double *)malloc(sizeof(double) * size);
		
		vecB = (double *)malloc(sizeof(double) * m);
		for (i = 0; i < size; i++){
			matA[i] = rand() / (double)RAND_MAX;
		}
		for (i = 0; i < n; i++){
			vecA[i] = rand() / (double)RAND_MAX;
		}
		for (j = 1; j < nprocs ; j++){
			s = (j * n) / nprocs;
			en = ((j + 1)*n) / nprocs;
			chunk = en - s;
			MPI_Send(matA + s * n, chunk * n, MPI_DOUBLE,j, 0, MPI_COMM_WORLD);
		}
		
		for(i = 0; i < row; i++){
			memcpy(recM + i * n, matA + (start + i) * n, n * sizeof(double));
		}
		free(matA);
	}
	else{
		MPI_Recv(recM, row, MPI_DOUBLE,0, 0, MPI_COMM_WORLD, &status);
		
	}
	MPI_Bcast(vecA, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);

	matrix_vector(row, n, recM, vecA, vecC);
	MPI_Gather(vecC, row, MPI_DOUBLE, vecB, row, MPI_DOUBLE, 0, MPI_COMM_WORLD); 
	if (rank == 0){
		for (i = 0; i < n; i++){
			printf("%lf\n", vecB[i]);
		}
		free(vecB);
		free(vecC);
		fclose(fd);
	}
	MPI_Finalize();
	return (0);
}

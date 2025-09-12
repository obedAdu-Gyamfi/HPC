#include "matrix.h"

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	int rank, nprocs;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	clock_t start, end;
	double t_used;
	FILE *file;
	if (argc != 2){
		if (rank == 0) fprintf(stderr, "Usage: %s N\n", argv[0]);
		MPI_Finalize();
		return 1;
	}
	int n = atoi(argv[1]);
	int m = n;
	int i, j;
	double *matA = NULL, *vec = NULL, *rbuf = NULL, *matB = NULL, *ans = NULL;

	// Per-rank rows (counts) and row displacements (both in ROWS)
	int *rows      = (int *)malloc(sizeof(int) * nprocs);
	int *row_displ = (int *)malloc(sizeof(int) * nprocs);

	vec = (double *)malloc(sizeof(double) * n);// all ranks need vec

	if (rank == 0){
		// Compute rows/displacements in ROWS
		if (nprocs == 1){
			file = fopen("data.txt", "w");
			fprintf(file, "%-*s %-*s %-*s\n",WIDTH, "N",WIDTH, "Core(s)", WIDTH,"M.V/s");
		}
		else{
		file = fopen("data.txt", "a");
		}
		if (!file){
			fprintf(stderr, "Unable to open file for write operation!\n");
			exit(-1);
		}
		for (j = 0; j < nprocs; j++){
			int start = (j * n) / nprocs;
			int end   = ((j + 1) * n) / nprocs;
			rows[j]      = end - start;   // rows for rank j
			row_displ[j] = start;         // starting row index
        	}
		// Allocate and fill matrix and vector
		matA = (double *)malloc(sizeof(double) * n * m);
		for (i = 0; i < n * m; i++) matA[i] = rand() / (double)RAND_MAX;
		for (i = 0; i < n; i++) vec[i] = rand() / (double)RAND_MAX;
		ans = (double *)malloc(sizeof(double) * n);
    }

    // Broadcast vector to everyone
    MPI_Bcast(vec, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Tell each rank how many rows it will receive
    int my_rows = 0;
    MPI_Scatter(rows, 1, MPI_INT, &my_rows, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Allocate local buffers
    rbuf = (double *)malloc(sizeof(double) * my_rows * n);  // my_rows x n
    matB = (double *)malloc(sizeof(double) * my_rows);      // my_rows results

    // Build element counts/displs for Scatterv (in ELEMENTS)
    int *sendcounts_elems = NULL;
    int *displs_elems     = NULL;
    if (rank == 0) {
        sendcounts_elems = (int *)malloc(sizeof(int) * nprocs);
        displs_elems     = (int *)malloc(sizeof(int) * nprocs);
        for (j = 0; j < nprocs; j++) {
            sendcounts_elems[j] = rows[j] * n;       // elements (rows * n)
            displs_elems[j]     = row_displ[j] * n;  // elements (row_start * n)
        }
    }

    // Scatter the matrix rows
    MPI_Scatterv(matA, sendcounts_elems, displs_elems, MPI_DOUBLE,
                 rbuf, my_rows * n, MPI_DOUBLE,
                 0, MPI_COMM_WORLD);

    // Local mat-vec multiply on my_rows
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    matrix_vector(my_rows, n, rbuf, vec, matB);
    end = MPI_Wtime();
    t_used = end - start;
    // Gather the result vector (counts & displs in ROWS)
    MPI_Gatherv(matB, my_rows, MPI_DOUBLE,
                ans, rows, row_displ, MPI_DOUBLE,
                0, MPI_COMM_WORLD);

    // Cleanup
    if (rank == 0) {
	 fprintf(file, "%-*d %-*d %-*lf\n",WIDTH, n, WIDTH, nprocs,WIDTH, t_used);
	fclose(file);
        free(matA);
        free(ans);
        free(sendcounts_elems);
        free(displs_elems);
    }
    free(vec);
    free(rbuf);
    free(matB);
    free(rows);
    free(row_displ);

    MPI_Finalize();
    return 0;
}


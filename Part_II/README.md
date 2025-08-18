This directory contains HPC parallel programming codes written in the C programming language.
The program is a scalable distributed memory MPI version of the vector vector multiplication programing from Part_I of the HPC directory.
The program utilize the resources of the machine such as an increasing processor size to compute the vector product of two vector.

1. vector-vector multiplication, a function that calculates a the dot product of two vectors.

A scalability test on an N value of 2.51e8 is performed on varying the number of cores being used.

The CPU time-to-solution of  each processor  core is written in a text file and performance anlysis is performed on the varying number of processor cores against time-to-solution.
Scalability plots that include strong scaling charts shows the perfomance from a serial run, and parallel run from 2 cores to 8 cores are performed.

A speed-Up plot is also generated to visualize the performance of the increasing number of cpu
 cores relative to a serial run of 1 processor.
 
The program can be scaled to include mulptiple nodes.
The inclusion of nodes to the cluster requires the user to provide a host.txt that has the ip address or hostname of the additional nodes specified and the number of slots available.

The makefile can then be modified by adding the -hosfile host.txt to the mpirun command and the number of iterations increased to prefered number of available cores in the cluster.
the variable name host.txt should also be handled in the modified in the makefile to avoid variable errors.

The new nodes being added to should be able to communicate across an ssh connection with a public key to avoid authentication or authorization issues.


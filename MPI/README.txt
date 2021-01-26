Inside this folder you can find 6 files, mpi_deficient_numbers.c (code), mpi_deficient_numbers (compile file), deficient_numbers_mpi.sbatch (configure file slurm), output_deficient_numbers_mpi.out (results), and time_comparision.txt (comparasion for time progrman execution).


this code has been tested in guane for N = 1000000 iter
Nodes = 2
tasks per node = 8

Using openmpi version 3.1.4


Compilation
mpicc mpi_deficient_numbers.c -o mpi_deficient_numbers -lm -std=gnu99

Execution

sbatch mpi_deficients_numbers.sbatch 

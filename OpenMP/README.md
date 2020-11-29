Inside this folder you can find 5 files, omp_deficient_numbers.c (code), omp_deficient_numbers (compile file), deficient_numbers.sbatch (configure file slurm) and output_deficient_numbers_omp.txt (results), output_deficient_numbers_omp.txt (mistakes).


this code has been executed in local and guane for 16 cores for task

Using gcc version 8.3.0

Local: 8 cores

Compilation
gcc -fopenmp omp_deficient_numbers.c -o omp_fft -lm

Execution
./omp_deficient_numbers


GUANE: 16 cores
Load module gcc

module load devtools/gcc/8.3.0

Compilation
gcc -fopenmp omp_deficient_numbers.c -o omp_fft -lm

Execution

sbatch deficient_numbers.sbatch


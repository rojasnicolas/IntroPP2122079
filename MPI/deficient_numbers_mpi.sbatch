#!/bin/bash
#SBATCH --job-name=openMPI
#SBATCH --output=ouput_mpi_deficient.out
#SBATCH --error=error_mpi_deficient.err
#SBATCH -N 2
#SBATCH -n 8
#SBATCH --partition=normal


# Load the default OpenMPI module.
module load devtools/mpi/openmpi/3.1.4


# Set OMP_NUM_THREADS to the number of CPUs per task we asked for.
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Run the process with mpirun. Note that the -n option is not required
# in this case; mpirun will automatically determine how many processes
# to run from the Slurm settings.
mpirun ./mpi_deficient
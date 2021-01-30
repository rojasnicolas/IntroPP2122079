#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MASTER 0 /* task ID of master task */
#define TAG_CTR 1
#define TAG_N 2

/*
  Purpose:
  deficient_numbers calculates and writes the deficient numbers between 1 and a given number, using some parameters by Intro PP students.
  Licensing:
  This code is distributed under the GNU LGPL license.
  Author:
  electronic content
  https://www.w3resource.com/c-programming-exercises/numbers/c-numbers-exercise-5.php 
  
  OpenMPI Modification:
  26 Jan 2020 by Nicolás Rojas, Universidad Industrial de Santander DAMAR.ROJAS@correo.uis.edu.co                   
  This OpenMPI Modification makes a parallelization of the original Code design.  
  
*/

int getSum(int n)
{
    int sum = 0;
    for (int i = 1; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            if (n / i == i)
                sum = sum + i;
            else
            {
                sum = sum + i;
                sum = sum + (n / i);
            }
        }
    }
    sum = sum - n;
    return sum;
}

bool checkDeficient(int n)
{
    return (getSum(n) < n);
}

int main(int argc, char **argv)
{
    int n, ctr = 0;
    //variables for MPI use
    int ntasks; /* task ID */
    int rank;   /* number of tasks */
    int dest, source;
    double wtime;
    double starttime, endtime;

    int inicio = 1;
    int total = 1000000;
    int numbers[total];
    int r;

    //Get the Status
    MPI_Status Stat;
    MPI_Init(&argc, &argv);

    //get the total number of MPI process
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    //get the total number of calling MPI process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //get an elapsed wall clock time in seconds
    starttime = MPI_Wtime();

    //only master does this
    if (rank == MASTER) //master process
    {
        printf("\n\n The Deficient numbers between 1 to 1000000 are: \n");
        printf(" ------------------------------------------------\n");
        // MPI_Recv(&numbers, 1, MPI_UNSIGNED, 1, TAG_N, MPI_COMM_WORLD, &Stat);
    }

    // MPI_Scatter(numbers, 1, MPI_INT, sub_nums, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank > 0)
    {

        for (int r = 1; r <= rank; r++)
        {
            if (rank == r)
            {
                inicio = (total / rank) * (r - 1);
                for (int j = inicio; j < (total / rank) * r; j++)
                {
                    n = j;
                    if (n > 0)
                    {
                        if (checkDeficient(n) == true)
                        {
                            printf("%d ", n);
                            // numbers[j] = n;
                            ctr++;
                        }
                    }
                }
                // MPI_Send(&numbers, 1, MPI_UNSIGNED, 0, TAG_N, MPI_COMM_WORLD);
                MPI_Send(&ctr, 1, MPI_UNSIGNED, 0, TAG_CTR, MPI_COMM_WORLD);
            }
        }
    }

    // MPI_Gather(&numbers, 1, MPI_UNSIGNED, NULL, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    // MPI_Barrier();
    if (rank == MASTER)
    {
        MPI_Recv(&ctr, 1, MPI_UNSIGNED, 1, TAG_CTR, MPI_COMM_WORLD, &Stat);
        printf("\n The Total number of Deficient numbers are at the moment is: %d \n", ctr);
    }
    
    //finalized time execution mpi
    endtime = MPI_Wtime();
    MPI_Finalize();
    if (rank == MASTER) //just master made this task
    {
        printf("\n");
        printf("Deficient_MPI:\n");
        printf("  Normal end of execution.\n");
        printf("\n");
        printf("That took %f seconds\n", endtime - starttime);
    }
    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

/*

  Purpose:

  deficient_numbers calculates and writes the deficient numbers between 1 and a given number, using some parameters by Intro PP students.

  Licensing:

  This code is distributed under the GNU LGPL license.

  Author:
  electronic content
  https://www.w3resource.com/c-programming-exercises/numbers/c-numbers-exercise-5.php 
  
  OpenMP Modification:
  26 Nov 2020 by Nicolás Rojas, Universidad Industrial de Santander DAMAR.ROJAS@correo.uis.edu.co                   
  This OpenMP Modification makes a parallelization of the original Code design.  
  
*/


int getSum(int n)
{
    int sum = 0;
    int i;
    // #pragma omp parallel for default(none) private(i, n, sum)
    for (i = 1; i <= sqrt(n); i++)
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

int main()
{
//the variable wtime stores the time it takes to execute the program
    double wtime;
    double mflops;
    int n, ctr = 0;

    printf("\n\n The Deficient numbers between 1 to 1000000 are: \n");
    printf(" ------------------------------------------------\n");
    wtime = omp_get_wtime();

//the for is parallelized
#pragma omp parallel for 
    for (int j = 1; j <= 10000000; j++)
    {
        n = j;
        if (checkDeficient(n) == true)
        {
            printf("%d ", n);
            ctr++;
        }
    }
    wtime = omp_get_wtime() - wtime;

    printf("\n The Total number of Deficient numbers are: %d \n", ctr);
    printf("Tiempo execution  %f\n seconds", wtime);
}

#include <iostream>
#include <cmath>

#include "PapiWrapper.h"
#include <papi.h>


#ifndef OUTPUT_ALL
#define OUTPUT_ALL 1
#endif

static void populateA(double **a, const int m, const int n, const int p)
{
   const int minDim = std::min(m,n);
   for (int z = 0; z < minDim; z++)
      a[z][z] = 1;
}

static void populateB(double **b, const int m, const int n, const int p)
{
   const int minDim = std::min(n,p);
   for (int z = 0; z < minDim; z++)
      b[z][z] = 1;
}

static void printA(double **a, const int m, const int n, const int p)
{
   std::cout << "A: = " <<std::endl;
   for (int i=0; i < m; i++)
   {
	  for (int k=0; k < n; k++)
	  {
	     std::cout << a[i][k]<< " " ;
      }
	  std::cout << std::endl;
   }
   std::cout << std::endl;
}

static void printB(double **b, const int m, const int n, const int p)
{
   std::cout << "B: = " <<std::endl;
   for (int i=0; i < n; i++)
   {
	  for (int k=0; k < p; k++)
	  {
	     std::cout << b[i][k]<< " " ;
      }
	  std::cout << std::endl;
   }
   std::cout << std::endl;
}

static void printC(double **c, const int m, const int n, const int p)
{
   std::cout << "C: = " <<std::endl;
   for (int i=0; i < m; i++)
   {
	  for (int k=0; k < p; k++)
	  {
	     std::cout << c[i][k]<< " " ;
      }
	  std::cout << std::endl;
   }
   std::cout << std::endl;
}

static void editC(double **c, const int m, const int n, const int p)
{
   double sum = 0.0;
   for (int i=0; i < m; i++)
   {
	  for (int k=0; k < p; k++)
	  {
	     sum += c[i][k];
      }
   }
   std::cout << "Sum: " << sum << std::endl;
}

int main(int argc, char *argv[])
{
   std::cout << "This is a blocking Matrix Matrix Multiply (MMM) example " << std::endl
             << "It takes matrix a and matrix b and creates matrix c. " << std::endl
			 << std::endl;
   const int outputValue = OUTPUT_ALL;

   std::cout << "The output is: " << (outputValue? "on" : "off") << std::endl;

#ifndef BLOCK_M
#define BLOCK_M 30
#endif

#ifndef BLOCK_P
#define BLOCK_P BLOCK_M
#endif

#ifndef BLOCK_N
#define BLOCK_N BLOCK_M
#endif

#ifndef BLOCK_NB
#define BLOCK_NB 10
#endif
   int M  = BLOCK_M;
   int N  = BLOCK_N;
   int P  = BLOCK_P;
   int NB = BLOCK_NB;
   if (argc > 1)
      M = atoi(argv[1]);
   if (argc > 2)
      N = atoi(argv[2]);
   if (argc > 3)
      P = atoi(argv[3]);
   if (argc > 4)
      NB = atoi(argv[4]);

   double** a = new double*[M];
   double** c = new double*[M];
   for (int i=0; i<M; ++i)
   {
      a[i] = new double[N]();
      c[i] = new double[P]();
   }
   double** b = new double*[N];
   for (int i=0; i < N; ++i)
   {
      b[i] = new double[P]();
   }

   populateA(a, M, N, P);
   populateB(b, M, N, P);

   papiSetup();
   papiStart();

   for (int i=0; i < N; i+=NB)
      for (int j=0; j < M; j+=NB)
	     for (int k=0; k < P; k+=NB)
		   for (int i0=i; i0 < (i+NB); i0++)
		      for (int j0=j; j0 < (j+NB); j0++)
			     for (int k0=k; k0 < (k+NB); k0++)
				    c[i0][j0] += a[i0][k0]*b[k0][j0];

   papiFinish();

   #if OUTPUT_ALL
   printA(a, M, N, P);
   printB(b, M, N, P);
   printC(c, M, N, P);
   #endif

   papiPrintResults();

   editC(c, M, N, P);
   return 0;
}

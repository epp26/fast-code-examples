#include <iostream>
#include <cmath>

#include "PapiWrapper.h"
#include <papi.h>

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

#ifndef OUTPUT_ALL
#define OUTPUT_ALL 1
#endif

static void populateA(double a[BLOCK_M][BLOCK_N])
{
   const int m = BLOCK_M;
   const int n = BLOCK_N;
   const int p = BLOCK_P;
   const int minDim = std::min(m,n);
   for (int z = 0; z < minDim; z++)
      a[z][z] = 1;
}

static void populateB(double b[BLOCK_N][BLOCK_P])
{
   const int m = BLOCK_M;
   const int n = BLOCK_N;
   const int p = BLOCK_P;
   const int minDim = std::min(n,p);
   for (int z = 0; z < minDim; z++)
      b[z][z] = 1;
}

static void printA(double a[BLOCK_M][BLOCK_N])
{
   const int m = BLOCK_M;
   const int n = BLOCK_N;
   const int p = BLOCK_P;

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

static void printB(double b[BLOCK_N][BLOCK_P])
{
   const int m = BLOCK_M;
   const int n = BLOCK_N;
   const int p = BLOCK_P;

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

static void printC(double c[BLOCK_M][BLOCK_P])
{
   const int m = BLOCK_M;
   const int n = BLOCK_N;
   const int p = BLOCK_P;

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

static void editC(double c[BLOCK_M][BLOCK_P])
{
   const int m = BLOCK_M;
   const int n = BLOCK_N;
   const int p = BLOCK_P;

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


int main()
{
   std::cout << "This is a blocking Matrix Matrix Multiply (MMM) example " << std::endl
             << "It takes matrix a and matrix b and creates matrix c. " << std::endl
			 << std::endl;
   const int outputValue = OUTPUT_ALL;

   std::cout << "The output is: " << (outputValue? "on" : "off") << std::endl;

   double a[BLOCK_M][BLOCK_N] = {0.0};
   double b[BLOCK_N][BLOCK_P] = {0.0};
   double c[BLOCK_M][BLOCK_P] = {0.0};

   const int M  = BLOCK_M;
   const int N  = BLOCK_N;
   const int P  = BLOCK_P;
   const int NB = BLOCK_NB;

   populateA(a);
   populateB(b);

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
   printA(a);
   printB(b);
   printC(c);
   #endif

   papiPrintResults();

   editC(c);
   return 0;
}

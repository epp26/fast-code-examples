#include <iostream>
#include <cmath>

#include "PapiWrapper.h"
#include <papi.h>
#include <cstdlib>

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
   std::cout << "This is a simple Matrix Matrix Multiply (MMM) example " << std::endl
             << "It takes matrix a and matrix b and creates matrix c. " << std::endl
			 << std::endl;
   const int outputValue = OUTPUT_ALL;

   std::cout << "The output is: " << (outputValue? "on" : "off") << std::endl;

// double a[SIMPLE_M][SIMPLE_N] = {0.0};
// double b[SIMPLE_N][SIMPLE_P] = {0.0};
// double c[SIMPLE_M][SIMPLE_P] = {0.0};

#ifndef SIMPLE_M
#define SIMPLE_M 30
#endif

#ifndef SIMPLE_P
#define SIMPLE_P SIMPLE_M
#endif

#ifndef SIMPLE_N
#define SIMPLE_N SIMPLE_M
#endif
   int m = SIMPLE_M;
   int n = SIMPLE_N;
   int p = SIMPLE_P;
   if (argc > 1)
      m = atoi(argv[1]);
   if (argc > 2)
      n = atoi(argv[2]);
   if (argc > 3)
      p = atoi(argv[3]);

//   std::cout << "M: " << m << " N: " << n << " P: "<< p <<" argc: " << argc << std::endl;

   double** a = new double*[m];
   double** c = new double*[m];
   for (int i=0; i<m; ++i)
   {
      a[i] = new double[n]();
      c[i] = new double[p]();
   }
   double** b = new double*[n];
   for (int i=0; i < n; ++i)
   {
      b[i] = new double[p]();
   }

   populateA(a, m, n, p);
   populateB(b, m, n, p);

   papiSetup();
   papiStart();

   for (int i=0; i < m; i++)
      for (int j=0; j < p; j++)
	     for (int k=0; k < n; k++)
		    c[i][j] += a[i][k]*b[k][j];

   papiFinish();

   #if OUTPUT_ALL
   printA(a, m, n, p);
   printB(b, m, n, p);
   printC(c, m, n, p);
   #endif

   papiPrintResults();

   editC(c, m, n, p);
   return 0;
}

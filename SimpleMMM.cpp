#include <iostream>
#include <cmath>

#include "PapiWrapper.h"
#include <papi.h>

#define SIMPLE_M 30
#define SIMPLE_P 30
#define SIMPLE_N 30

static void populateA(double a[SIMPLE_M][SIMPLE_N])
{
   const int m = SIMPLE_M;
   const int n = SIMPLE_N;
   const int p = SIMPLE_P;
   const int minDim = std::min(m,n);
   for (int z = 0; z < minDim; z++)
      a[z][z] = 1;
}

static void populateB(double b[SIMPLE_N][SIMPLE_P])
{
   const int m = SIMPLE_M;
   const int n = SIMPLE_N;
   const int p = SIMPLE_P;
   const int minDim = std::min(n,p);
   for (int z = 0; z < minDim; z++)
      b[z][z] = 1;
}

static void printA(double a[SIMPLE_M][SIMPLE_N])
{
   const int m = SIMPLE_M;
   const int n = SIMPLE_N;
   const int p = SIMPLE_P;

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

static void printB(double b[SIMPLE_N][SIMPLE_P])
{
   const int m = SIMPLE_M;
   const int n = SIMPLE_N;
   const int p = SIMPLE_P;

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

static void printC(double c[SIMPLE_M][SIMPLE_P])
{
   const int m = SIMPLE_M;
   const int n = SIMPLE_N;
   const int p = SIMPLE_P;

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

int main()
{
   std::cout << "This is a simple Matrix Matrix Multiply (MMM) example " << std::endl
             << "It takes matrix a and matrix b and creates matrix c. " << std::endl
			 << std::endl;

   double a[SIMPLE_M][SIMPLE_N] = {0.0};
   double b[SIMPLE_N][SIMPLE_P] = {0.0};
   double c[SIMPLE_M][SIMPLE_P] = {0.0};

   const int m = SIMPLE_M;
   const int n = SIMPLE_N;
   const int p = SIMPLE_P;


   populateA(a);
   printA(a);
   populateB(b);
   printB(b);

   papiSetup();
   papiStart();

   for (int i=0; i < m; i++)
      for (int j=0; j < p; j++)
	     for (int k=0; k < n; k++)
		    c[i][j] += a[i][k]*b[k][j];

   papiFinish();
   printC(c);

   papiPrintResults();

   return 0;
}

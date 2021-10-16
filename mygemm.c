#include "mygemm.h"

/**
 * 
 * Implement all functions here in this file.
 * Do NOT change input parameters and return type.
 * 
 **/

//Register Reuse part 1
void dgemm0(const double* A, const double* B, double* C, const int n)
{
  /*dgemm0: simple ijk version triple loop algorithm*/
  int i, j, k = 0;
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      for (k=0; k<n; k++) {
        C[i*n+j] += A[i*n+k] * B[k*n+j]; 
      }
    }
  }
}

void dgemm1(const double *A, const double *B, double *C, const int n) 
{
  int i, j, k = 0;
  for (i=0; i<n; i++)
    for (j=0; j<n; j++) {
      register double r = C[i*n+j] ;
      for (k=0; k<n; k++) {
        r += A[i*n+k] * C[k*n+j];
      }
      C[i*n+j] = r;
    }
}
//Register Reuse part 1 End

//Register Reuse part 2
void dgemm2(const double *A, const double *B, double *C, const int n) 
{
  int i, j, k = 0;
  for (i=0; i<n; i+=2) {
    for (j=0; j<n; j+=2) {
      for (k=0; k<n; k+=2) {
        C[i*n+j] = A[i*n+k] * B[k*n+j] + A[i*n+k+1] * B[(k+1)*n+j] + C[i*n+j];
        C[(i+1)*n+j] = A[(i+1)*n+k] * B[k*n+j] + A[(i+1)*n+k+1] * B[(k+1)*n+j] + C[(i+1)*n+j];
        C[i*n+(j+1)] = A[i*n+k] * B[k*n+(j+1)] + A[i*n+k+1] * B[(k+1)*n+(j+1)] + C[i*n+(j+1)];
        C[(i+1)*n+(j+1)] = A[(i+1)*n+k] * B[k*n+(j+1)] + A[(i+1)*n+k+1] * B[(k+1)*n+(j+1)] + C[(i+1)*n+(j+1)];
      }
    }
  }
}
//Register Reuse part 2 End

//Register Reuse part 3
void dgemm3(const double *A, const double *B, double *C, const int n) 
{


}
//Register Reuse part 3 End

//Cache Reuse part 3
void ijk(const double *A, const double *B, double *C, const int n) 
{

}

void bijk(const double *A, const double *B, double *C, const int n, const int b) 
{

}

void jik(const double *A, const double *B, double *C, const int n) 
{

}

void bjik(const double *A, const double *B, double *C, const int n, const int b) 
{

}

void kij(const double *A, const double *B, double *C, const int n) 
{

}

void bkij(const double *A, const double *B, double *C, const int n, const int b) 
{

}


void ikj(const double *A, const double *B, double *C, const int n) 
{

}

void bikj(const double *A, const double *B, double *C, const int n, const int b) 
{

}

void jki(const double *A, const double *B, double *C, const int n) 
{

}

void bjki(const double *A, const double *B, double *C, const int n, const int b) 
{

}

void kji(const double *A, const double *B, double *C, const int n) 
{

}

void bkji(const double *A, const double *B, double *C, const int n, const int b) 
{

}
//Cache Reuse part 3 End 

//Cache Reuse part 4
void optimal(const double* A, const double* B, double *C, const int n, const int b)
{
    
}

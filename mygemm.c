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
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      for (k=0; k<n; k++) {
        c[i*n+j] += a[i*n+k] * b[k*n+j]; 
      }
    }
  }
}

void dgemm1(const double *A, const double *B, double *C, const int n) 
{
  for (i=0; i<n; i++)
    for (j=0; j<n; j++) {
      register double r = c[i*n+j] ;
      for (k=0; k<n; k++)
        r += a[i*n+k] * b[k*n+j];
      c[i*n+j] = r;
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
        c[i*n+j] = a[i*n+k] * b[k*n+j] + a[i*n+k+1] * b[(k+1)*n+j] + c[i*n+j];
        c[(i+1)*n+j] = a[(i+1)*n+k] * b[k*n+j] + a[(i+1)*n+k+1] * b[(k+1)*n+j] + c[(i+1)*n+j];
        c[i*n+(j+1)] = a[i*n+k] * b[k*n+(j+1)] + a[i*n+k+1] * b[(k+1)*n+(j+1)] + c[(i*n+(j+1)];
        c[(i+1)*n+(j+1)] = a[(i+1)*n+k)] * b[k*n+(j+1)] + a[(i+1)*n+k+1] * b[(k+1)*n+(j+1)] + c[(i+1)*n+(j+1)];
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

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
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      register double r = C[i*n+j];
      for (k=0; k<n; k++) {
        r += A[i*n+k] * B[k*n+j];
      }
      C[i*n+j] = r;
    }
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
  int i, j, k = 0;
  for(i = 0; i < n; i += 2)
       for(j = 0; j < n; j += 2)  {
            register int t = i*n+j; register int tt = t+n; 
            register double c00 = C[t]; register double c01 = C[t+1];  register double c10 = C[tt]; register double c11 = C[tt+1];

            for(k = 0; k < n; k += 2) {

                /* 2 by 2 mini matrix multiplication using registers*/

                register int ta = i*n+k; register int tta = ta+n; register int tb = k*n+j; register int ttb = tb+n;
                register double a00 = A[ta]; register double a01 = A[ta+1]; register double a10 = A[tta]; register double a11 = A[tta+1];
                register double b00 = B[tb]; register double b01 = B[tb+1]; register double b10 = B[ttb]; register double b11 = B[ttb+1];

                c00 += a00*b00 + a01*b10;
                c01 += a00*b01 + a01*b11;
                c10 += a10*b00 + a11*b10;
                c11 += a10*b01 + a11*b11;
             }

             C[t] = c00;
             C[t+1] = c01;
             C[tt] = c10;
             C[tt+1] = c11;
        }

}
//Register Reuse part 3 End

//Cache Reuse part 3
void ijk(const double *A, const double *B, double *C, const int n) 
{
  int i, j , k = 0;
  for (i=0; i<n; i++)  {
    for (j=0; j<n; j++) {
      register double sum = C[i*n+j];
      for (k=0; k<n; k++) 
        sum += A[i*n+k] * B[k*n+j];
      C[i*n+j] = sum;
    }
  } 
}

void bijk(const double *A, const double *B, double *C, const int n, const int b) 
{
  int i, j, k = 0;
  int i1, j1, k1 = 0;
  for (i = 0; i < n; i+=b)
    for (j = 0; j < n; j+=b)
      for (k = 0; k < n; k+=b)
      /* B x B mini matrix multiplications */
        for (i1 = i; i1 < i+b; i1++)
          for (j1 = j; j1 < j+b; j1++) {
            register double r=C[i1*n+j1];
            for (k1 = k; k1 < k+b; k1++)
              r += A[i1*n + k1]*B[k1*n + j1];
            C[i1*n+j1]=r;
          }
}

void jik(const double *A, const double *B, double *C, const int n) 
{
  int i, j, k = 0;
  for (j=0; j<n; j++) {
    for (i=0; i<n; i++) {
      register double sum = C[i*n+j];
      for (k=0; k<n; k++)
        sum += A[i*n+k] * B[k*n+j];
      C[i*n+j] = sum;
    }
  }
}

void bjik(const double *A, const double *B, double *C, const int n, const int b) 
{
  int i, j, k = 0;
  int i1, j1, k1 = 0;
  for (j = 0; j < n; j+=b)
    for (i = 0; i < n; i+=b)
      for (k = 0; k < n; k+=b)
      /* B x B mini matrix multiplications */
        for (j1 = j; j1 < j+b; j1++)
          for (i1 = i; i1 < i+b; i1++) {
            register double r=C[i1*n+j1];
            for (k1 = k; k1 < k+b; k1++)
              r += A[i1*n + k1]*B[k1*n + j1];
            C[i1*n+j1]=r;
          }
}

void kij(const double *A, const double *B, double *C, const int n) 
{
  int i, j, k = 0;
  for (k=0; k<n; k++) {
    for (i=0; i<n; i++) {
      register double r = A[i*n+k];
      for (j=0; j<n; j++)
        C[i*n+j] += r * B[k*n+j];   
    }
  }
}

void bkij(const double *A, const double *B, double *C, const int n, const int b) 
{
  int i, j, k = 0;
  int i1, j1, k1 = 0;
  for (k = 0; k < n; k+=b)
    for (i = 0; i < n; i+=b)
      for (j = 0; j < n; j+=b)
      /* B x B mini matrix multiplications */
        for (k1 = k; k1 < k+b; k1++)
          for (i1 = i; i1 < i+b; i1++) {
            register double r=A[i1*n+k1];
            for (j1 = j; j1 < j+b; j1++)
              C[i1*n+j1] += r * B[k1*n+j1];
          }
}


void ikj(const double *A, const double *B, double *C, const int n) 
{
  int i, j, k = 0;
  for (i=0; i<n; i++) {
    for (k=0; k<n; k++) {
      register double r = A[i*n+k];
      for (j=0; j<n; j++)
        C[i*n+j] += r * B[k*n+j];
    }
  }
}

void bikj(const double *A, const double *B, double *C, const int n, const int b) 
{
  int i, j, k = 0;
  int i1, j1, k1 = 0;
  for (i = 0; i < n; i+=b)
    for (k = 0; k < n; k+=b)
      for (j = 0; j < n; j+=b)
      /* B x B mini matrix multiplications */
        for (i1 = i; i1 < i+b; i1++)
          for (k1 = k; k1 < k+b; k1++) {
            register double r=A[i1*n+k1];
            for (j1 = j; j1 < j+b; j1++)
              C[i1*n+j1] += r * B[k1*n+j1];
          }
}

void jki(const double *A, const double *B, double *C, const int n) 
{
  int i, j, k = 0;
  for (j=0; j<n; j++) {
    for (k=0; k<n; k++) {
      register double r = B[k*n+j];
      for (i=0; i<n; i++)
        C[i*n+j] += A[i*n+k] * r;
    }
  }
}

void bjki(const double *A, const double *B, double *C, const int n, const int b) 
{
  int i, j, k = 0;
  int i1, j1, k1 = 0;
  for (j = 0; j < n; j+=b)
    for (k = 0; k < n; k+=b)
      for (i = 0; i < n; i+=b)
      /* B x B mini matrix multiplications */
        for (j1 = j; j1 < j+b; j1++)
          for (k1 = k; k1 < k+b; k1++) {
            register double r=B[k1*n+j1];
            for (i1 = i; i1 < i+b; i1++)
              C[i1*n+j1] += r * A[i1*n+k1];
          }
}

void kji(const double *A, const double *B, double *C, const int n) 
{
  int i, j, k = 0;
  for (k=0; k<n; k++) {
  for (j=0; j<n; j++) {
    register double r = B[k*n+j];
    for (i=0; i<n; i++)
      C[i*n+j] += A[i*n+k] * r;
    }
  }
}

void bkji(const double *A, const double *B, double *C, const int n, const int b) 
{
  int i, j, k = 0;
  int i1, j1, k1 = 0;
  for (k = 0; k < n; k+=b)
    for (j = 0; j < n; j+=b)
      for (i = 0; i < n; i+=b)
      /* B x B mini matrix multiplications */
        for (k1 = k; k1 < k+b; k1++)
          for (j1 = j; j1 < j+b; j1++) {
            register double r=B[k1*n+j1];
            for (i1 = i; i1 < i+b; i1++)
              C[i1*n+j1] += r * A[i1*n+k1];
          }
}
//Cache Reuse part 3 End 

//Cache Reuse part 4
void optimal(const double* A, const double* B, double *C, const int n, const int b)
{
  int i, j, k = 0;
  int i1, j1, k1 = 0;
  for (i = 0; i < n; i+=b)
    for (j = 0; j < n; j+=b)
      for (k = 0; k < n; k+=b)
      /* B x B mini matrix multiplications */
        for(i1 = 0; i1 < i+b; i1 += 2)
          for(j1 = 0; j1 < j+b; j1 += 2)  {
            register int t = i1*n+j1; register int tt = t+n; 
            register double c00 = C[t]; register double c01 = C[t+1];  register double c10 = C[tt]; register double c11 = C[tt+1];

            for(k1 = 0; k1 < k+b; k1 += 2) {
                /* 2 by 2 mini matrix multiplication using registers*/

                register int ta = i1*n+k1; register int tta = ta+n; register int tb = k1*n+j1; register int ttb = tb+n;
                register double a00 = A[ta]; register double a01 = A[ta+1]; register double a10 = A[tta]; register double a11 = A[tta+1];
                register double b00 = B[tb]; register double b01 = B[tb+1]; register double b10 = B[ttb]; register double b11 = B[ttb+1];

                c00 += a00*b00 + a01*b10;
                c01 += a00*b01 + a01*b11;
                c10 += a10*b00 + a11*b10;
                c11 += a10*b01 + a11*b11;
             }

             C[t] = c00;
             C[t+1] = c01;
             C[tt] = c10;
             C[tt+1] = c11;
        }
}

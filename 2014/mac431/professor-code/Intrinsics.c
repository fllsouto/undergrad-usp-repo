/***************************************************************************************

This code is provided to the students of the "Calcul Reparti et Grid Computing"
course at ENSEEIHT, Toulouse, as an example of some basic optimization techniques
of numerical code for x86 processors with SSE vector units.

The code can be compiled like this:

gcc -O3 -msse -mmmx -o matvec matvec.c


Alfredo Buttari 2011
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#include <xmmintrin.h>


/* 
B is the block size. The matrix-vector product is implemented by partitioning
the original matrix into blocks of size BxB. The optimizations are thus applie 
to the small blocks product kernel,
*/
#define B     32

/* The size of the original matrix is the (NBxB)x(NBxB) */
#define NB    500

int N;
float *ycpy;
double flops;

/* small routine for taking times */
double swtime()
{
  struct timeval tp;
  struct timezone tzp;
  int i;

  i = gettimeofday(&tp,&tzp);
  return  ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );

}

/* interfaces */
void domult(float *A, float *x, float *y, void (*blk)(float*, float*, float*));
void blockmul(float *A, float *x, float *y);
void blockmul_vec(float *A, float *x, float *y);
void compare(float *x, float *y);
void blockmul_vec_ur(float *A, float *x, float *y);
void blockmul_vec_ur_pf(float *A, float *x, float *y);
void blockmul_vec_ur_pf2(float *A, float *x, float *y);

int main(){
  float *A, *x, *y;
  int i, j, one=1;
  char n='n';
  float alpha=1.0, beta=0.0;
  double t1, t2;

  N = B*NB;
  flops = ((double)2)*((double)N)*((double)N)/1e9;


  /* Allocate and initialize the data */
  A    = (float *) malloc(N*N * sizeof(float));
  x    = (float *) malloc(N   * sizeof(float));
  y    = (float *) malloc(N   * sizeof(float));
  ycpy = (float *) malloc(N   * sizeof(float));
  
  for (j=0; j<N; j++){
    y[j]    = 0;
    ycpy[j] = 0;
    x[j]    = ((float)rand())/((float)RAND_MAX);
    for (i=0; i<N; i++){
      A[j*N + i] = ((float)rand())/((float)RAND_MAX);
    }
  }



  /* Naive implementation */
  printf("Basic                     --  ");
  domult(A, x, ycpy, blockmul);

  /* re-initialize y */
  for (i=0; i<N; i++)
    y[i] = 0;

  /* Vectorized version */
  printf("Vector                    --  ");
  domult(A, x, y, blockmul_vec);

  /* Check for correctness */
  compare(ycpy, y);

  /* re-initialize y */
  for (i=0; i<N; i++)
    y[i] = 0;

  /* Vectorized version with loop-unrolling */
  printf("Vector, unroll            --  ");
  domult(A, x, y, blockmul_vec_ur);

  /* Check for correctness */
  compare(ycpy, y);

  /* re-initialize y */
  for (i=0; i<N; i++)
    y[i] = 0;

  /* Vectorized version with loop-unrolling and prefetch */
  printf("Vector, unroll, prefetch  --  ");
  domult(A, x, y, blockmul_vec_ur_pf);

  /* Check for correctness */
  compare(ycpy, y);

  /* re-initialize y */
  for (i=0; i<N; i++)
    y[i] = 0;

  /* Another vectorized version with loop-unrolling and prefetch */
  printf("Vector, unroll, prefetch2 --  ");
  domult(A, x, y, blockmul_vec_ur_pf2);

  /* Check for correctness */
  compare(ycpy, y);


  return 0;


}





void domult(float *A, float *x, float *y, void (*blk)(float*, float*, float*)){
  /* 
     This is the driver routine that performs the product of an entire 
     matrix relying on the blk kernel for doing the block-products
  */
  int i, j;
  double t1, t2;

  t1 = swtime();
  for(j=0; j<N; j+=B){
    for(i=0; i<N; i+=B){
      blk(&A[j*N+i], &x[j], &y[i]);
    }
  }
  t2 = swtime()-t1;

  printf("Time: %6.4f     Gflops: %6.3f\n",t2,flops/t2);

  return;

}


void compare(float *x, float *y){
  /* 
     Checks for correctness by comparing the elements of the 
     two inout arrays
  */
  
  int i;
  double nrm, max;

  max = 0.0;
  nrm = 0.0;

  for(i=0; i<N; i++){
    if(fabs(x[i] - y[i]) > max)
      max = (x[i] - y[i]);

    if(fabs(x[i]) > nrm)
      nrm = fabs(x[i]);
  }

  if(max/nrm > 1e5)
    printf("Error is : %e\n",max/nrm);
  
  return;

}

void blockmul(float *A, float *x, float *y){
  /* This is the most basic implementation: two nested loops */

  int i, j;

  for(j=0; j<B; j++){
    for(i=0; i<B; i++){
      y[i]+= A[j*N+i]*x[j];
    }
  }

  return;

}



void blockmul_vec(float *A, float *x, float *y){
  /* Vectorized version */
  int i, j;
  __m128 Av, xv, mul, yv;


  for(j=0; j<B; j++){
    /* Load one x coefficient into all the 4 vector elements */
    xv = _mm_load1_ps(&x[j]);
    /* Multiply by all the vectors in one column of the block */
    for(i=0; i<B; i+=4){
      /* Load one vector in column j of A */
      Av  = _mm_loadu_ps(&A[j*N+i]);
      /* load the corresponding y vector */
      yv  = _mm_loadu_ps(&y[i]);
      /* multiply */
      mul = _mm_mul_ps(Av, xv);
      /* add */
      yv  = _mm_add_ps(mul, yv);
      /* store the result */
      _mm_storeu_ps(&y[i], yv);
    }
  }

  return;

}






void blockmul_vec_ur(float *A, float *x, float *y){
  /* Vecotirzed version with loop-unrolling */
  int i, j;
  __m128 xv;
  __m128 Av0, mul0, yv0;
  __m128 Av1, mul1, yv1;
  __m128 Av2, mul2, yv2;
  __m128 Av3, mul3, yv3;
  __m128 Av4, mul4, yv4;
  __m128 Av5, mul5, yv5;
  __m128 Av6, mul6, yv6;
  __m128 Av7, mul7, yv7;


  /* Pre-load the entire y vector into registers */
  yv0  = _mm_loadu_ps(&y[0 ]);
  yv1  = _mm_loadu_ps(&y[4 ]);
  yv2  = _mm_loadu_ps(&y[8 ]);
  yv3  = _mm_loadu_ps(&y[12]);
  yv4  = _mm_loadu_ps(&y[16]);
  yv5  = _mm_loadu_ps(&y[20]);
  yv6  = _mm_loadu_ps(&y[24]);
  yv7  = _mm_loadu_ps(&y[28]);

  for(j=0; j<B; j++){
    /* Load one x coefficient into all the 4 vector elements */
    xv = _mm_load1_ps(&x[j]);

    /* Load an entire column j of A into vector registers*/
    Av0  = _mm_loadu_ps(&A[j*N + 0 ]);
    Av1  = _mm_loadu_ps(&A[j*N + 4 ]);
    Av2  = _mm_loadu_ps(&A[j*N + 8 ]);
    Av3  = _mm_loadu_ps(&A[j*N + 12]);
    Av4  = _mm_loadu_ps(&A[j*N + 16]);
    Av5  = _mm_loadu_ps(&A[j*N + 20]);
    Av6  = _mm_loadu_ps(&A[j*N + 24]);
    Av7  = _mm_loadu_ps(&A[j*N + 28]);


    /* multiply */
    mul0 = _mm_mul_ps(Av0, xv);
    mul1 = _mm_mul_ps(Av1, xv);
    mul2 = _mm_mul_ps(Av2, xv);
    mul3 = _mm_mul_ps(Av3, xv);
    mul4 = _mm_mul_ps(Av4, xv);
    mul5 = _mm_mul_ps(Av5, xv);
    mul6 = _mm_mul_ps(Av6, xv);
    mul7 = _mm_mul_ps(Av7, xv);

    /* add */
    yv0  = _mm_add_ps(mul0, yv0);
    yv1  = _mm_add_ps(mul1, yv1);
    yv2  = _mm_add_ps(mul2, yv2);
    yv3  = _mm_add_ps(mul3, yv3);
    yv4  = _mm_add_ps(mul4, yv4);
    yv5  = _mm_add_ps(mul5, yv5);
    yv6  = _mm_add_ps(mul6, yv6);
    yv7  = _mm_add_ps(mul7, yv7);

  }

  /* store y back to memory */
  _mm_storeu_ps(&y[0 ], yv0);
  _mm_storeu_ps(&y[4 ], yv1);
  _mm_storeu_ps(&y[8 ], yv2);
  _mm_storeu_ps(&y[12], yv3);
  _mm_storeu_ps(&y[16], yv4);
  _mm_storeu_ps(&y[20], yv5);
  _mm_storeu_ps(&y[24], yv6);
  _mm_storeu_ps(&y[28], yv7);

  return;

}




void blockmul_vec_ur_pf(float *A, float *x, float *y){
  /* Vectorized version with loop-unrolling and prefetch */

  int i, j;
  __m128 xv;
  __m128 Av0, mul0, yv0;
  __m128 Av1, mul1, yv1;
  __m128 Av2, mul2, yv2;
  __m128 Av3, mul3, yv3;
  __m128 Av4, mul4, yv4;
  __m128 Av5, mul5, yv5;
  __m128 Av6, mul6, yv6;
  __m128 Av7, mul7, yv7;


  /* Pre-load the entire y vector into registers */
  yv0  = _mm_loadu_ps(&y[0 ]);
  yv1  = _mm_loadu_ps(&y[4 ]);
  yv2  = _mm_loadu_ps(&y[8 ]);
  yv3  = _mm_loadu_ps(&y[12]);
  yv4  = _mm_loadu_ps(&y[16]);
  yv5  = _mm_loadu_ps(&y[20]);
  yv6  = _mm_loadu_ps(&y[24]);
  yv7  = _mm_loadu_ps(&y[28]);

  /* pre-fetch the first column of A into cache */
  _mm_prefetch((void *)&A[0 ], _MM_HINT_T0);
  _mm_prefetch((void *)&A[4 ], _MM_HINT_T0);
  _mm_prefetch((void *)&A[8 ], _MM_HINT_T0);
  _mm_prefetch((void *)&A[12], _MM_HINT_T0);
  _mm_prefetch((void *)&A[16], _MM_HINT_T0);
  _mm_prefetch((void *)&A[20], _MM_HINT_T0);
  _mm_prefetch((void *)&A[24], _MM_HINT_T0);
  _mm_prefetch((void *)&A[28], _MM_HINT_T0);

  for(j=0; j<B; j++){
    /* pre-fetch (j+1)-th column of A into cache */
    _mm_prefetch((void *)&A[(j+1)*N + 0 ], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 4 ], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 8 ], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 12], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 16], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 20], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 24], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 28], _MM_HINT_T0);

    /* Load one x coefficient into all the 4 vector elements */
    xv = _mm_load1_ps(&x[j]);

    /* Load an entire column j of A into vector registers*/
    Av0  = _mm_loadu_ps(&A[j*N + 0 ]);
    Av1  = _mm_loadu_ps(&A[j*N + 4 ]);
    Av2  = _mm_loadu_ps(&A[j*N + 8 ]);
    Av3  = _mm_loadu_ps(&A[j*N + 12]);
    Av4  = _mm_loadu_ps(&A[j*N + 16]);
    Av5  = _mm_loadu_ps(&A[j*N + 20]);
    Av6  = _mm_loadu_ps(&A[j*N + 24]);
    Av7  = _mm_loadu_ps(&A[j*N + 28]);

    /* multiply */
    mul0 = _mm_mul_ps(Av0, xv);
    mul1 = _mm_mul_ps(Av1, xv);
    mul2 = _mm_mul_ps(Av2, xv);
    mul3 = _mm_mul_ps(Av3, xv);
    mul4 = _mm_mul_ps(Av4, xv);
    mul5 = _mm_mul_ps(Av5, xv);
    mul6 = _mm_mul_ps(Av6, xv);
    mul7 = _mm_mul_ps(Av7, xv);

    /* add */
    yv0  = _mm_add_ps(mul0, yv0);
    yv1  = _mm_add_ps(mul1, yv1);
    yv2  = _mm_add_ps(mul2, yv2);
    yv3  = _mm_add_ps(mul3, yv3);
    yv4  = _mm_add_ps(mul4, yv4);
    yv5  = _mm_add_ps(mul5, yv5);
    yv6  = _mm_add_ps(mul6, yv6);
    yv7  = _mm_add_ps(mul7, yv7);

  }

  /* store y back to memory */
  _mm_storeu_ps(&y[0 ], yv0);
  _mm_storeu_ps(&y[4 ], yv1);
  _mm_storeu_ps(&y[8 ], yv2);
  _mm_storeu_ps(&y[12], yv3);
  _mm_storeu_ps(&y[16], yv4);
  _mm_storeu_ps(&y[20], yv5);
  _mm_storeu_ps(&y[24], yv6);
  _mm_storeu_ps(&y[28], yv7);

  return;

}









void blockmul_vec_ur_pf2(float *A, float *x, float *y){
  /* Another vectorized version with loop-unrolling and prefetch */

  int i, j;
  __m128 xv0, xv1;
  __m128 Av0, mul0, yv0;
  __m128 Av1, mul1, yv1;
  __m128 Av2, mul2, yv2;
  __m128 Av3, mul3, yv3;
  __m128 Av4, mul4, yv4;
  __m128 Av5, mul5, yv5;
  __m128 Av6, mul6, yv6;
  __m128 Av7, mul7, yv7;
  __m128 Av8 ,  mul8;
  __m128 Av9 ,  mul9;
  __m128 Av10, mul10;
  __m128 Av11, mul11;
  __m128 Av12, mul12;
  __m128 Av13, mul13;
  __m128 Av14, mul14;
  __m128 Av15, mul15;


  /* Pre-load the entire y vector into registers */
  yv0  = _mm_loadu_ps(&y[0 ]);
  yv1  = _mm_loadu_ps(&y[4 ]);
  yv2  = _mm_loadu_ps(&y[8 ]);
  yv3  = _mm_loadu_ps(&y[12]);
  yv4  = _mm_loadu_ps(&y[16]);
  yv5  = _mm_loadu_ps(&y[20]);
  yv6  = _mm_loadu_ps(&y[24]);
  yv7  = _mm_loadu_ps(&y[28]);

  /* pre-fetch the first column of A into cache */
  _mm_prefetch((void *)&A[0 ], _MM_HINT_T0);
  _mm_prefetch((void *)&A[4 ], _MM_HINT_T0);
  _mm_prefetch((void *)&A[8 ], _MM_HINT_T0);
  _mm_prefetch((void *)&A[12], _MM_HINT_T0);
  _mm_prefetch((void *)&A[16], _MM_HINT_T0);
  _mm_prefetch((void *)&A[20], _MM_HINT_T0);
  _mm_prefetch((void *)&A[24], _MM_HINT_T0);
  _mm_prefetch((void *)&A[28], _MM_HINT_T0);

  /* Basically this corresponds to a level-2 unrolling of the previous version */
  for(j=0; j<B; j+=2){
    /* pre-fetch (j+1)-th column of A into cache */
    _mm_prefetch((void *)&A[(j+1)*N + 0 ], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 4 ], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 8 ], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 12], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 16], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 20], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 24], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+1)*N + 28], _MM_HINT_T0);

    /* Load one x coefficient into all the 4 vector elements */
    xv0 = _mm_load1_ps(&x[j]);

    /* Load an entire column j of A into vector registers*/
    Av0  = _mm_loadu_ps(&A[j*N + 0 ]);
    Av1  = _mm_loadu_ps(&A[j*N + 4 ]);
    Av2  = _mm_loadu_ps(&A[j*N + 8 ]);
    Av3  = _mm_loadu_ps(&A[j*N + 12]);
    Av4  = _mm_loadu_ps(&A[j*N + 16]);
    Av5  = _mm_loadu_ps(&A[j*N + 20]);
    Av6  = _mm_loadu_ps(&A[j*N + 24]);
    Av7  = _mm_loadu_ps(&A[j*N + 28]);

    /* multiply */
    mul0 = _mm_mul_ps(Av0, xv0);
    mul1 = _mm_mul_ps(Av1, xv0);
    mul2 = _mm_mul_ps(Av2, xv0);
    mul3 = _mm_mul_ps(Av3, xv0);
    mul4 = _mm_mul_ps(Av4, xv0);
    mul5 = _mm_mul_ps(Av5, xv0);
    mul6 = _mm_mul_ps(Av6, xv0);
    mul7 = _mm_mul_ps(Av7, xv0);

    /* add */
    yv0  = _mm_add_ps(mul0, yv0);
    yv1  = _mm_add_ps(mul1, yv1);
    yv2  = _mm_add_ps(mul2, yv2);
    yv3  = _mm_add_ps(mul3, yv3);
    yv4  = _mm_add_ps(mul4, yv4);
    yv5  = _mm_add_ps(mul5, yv5);
    yv6  = _mm_add_ps(mul6, yv6);
    yv7  = _mm_add_ps(mul7, yv7);

    /* pre-fetch (j+2)-th column of A into cache */
    _mm_prefetch((void *)&A[(j+2)*N + 0 ], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+2)*N + 4 ], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+2)*N + 8 ], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+2)*N + 12], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+2)*N + 16], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+2)*N + 20], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+2)*N + 24], _MM_HINT_T0);
    _mm_prefetch((void *)&A[(j+2)*N + 28], _MM_HINT_T0);


    /* Load one x coefficient into all the 4 vector elements */
    xv1 = _mm_load1_ps(&x[j]);

    /* Load an entire column j of A into vector registers*/
    Av8   = _mm_loadu_ps(&A[(j+1)*N + 0 ]);
    Av9   = _mm_loadu_ps(&A[(j+1)*N + 4 ]);
    Av10  = _mm_loadu_ps(&A[(j+1)*N + 8 ]);
    Av11  = _mm_loadu_ps(&A[(j+1)*N + 12]);
    Av12  = _mm_loadu_ps(&A[(j+1)*N + 16]);
    Av13  = _mm_loadu_ps(&A[(j+1)*N + 20]);
    Av14  = _mm_loadu_ps(&A[(j+1)*N + 24]);
    Av15  = _mm_loadu_ps(&A[(j+1)*N + 28]);

    /* multiply */
    mul8  = _mm_mul_ps(Av8 , xv1);
    mul9  = _mm_mul_ps(Av9 , xv1);
    mul10 = _mm_mul_ps(Av10, xv1);
    mul11 = _mm_mul_ps(Av11, xv1);
    mul12 = _mm_mul_ps(Av12, xv1);
    mul13 = _mm_mul_ps(Av13, xv1);
    mul14 = _mm_mul_ps(Av14, xv1);
    mul15 = _mm_mul_ps(Av15, xv1);

    /* add */
    yv0  = _mm_add_ps(mul8 , yv0);
    yv1  = _mm_add_ps(mul9 , yv1);
    yv2  = _mm_add_ps(mul10, yv2);
    yv3  = _mm_add_ps(mul11, yv3);
    yv4  = _mm_add_ps(mul12, yv4);
    yv5  = _mm_add_ps(mul13, yv5);
    yv6  = _mm_add_ps(mul14, yv6);
    yv7  = _mm_add_ps(mul15, yv7);

  }

  /* store y back to memory */
  _mm_storeu_ps(&y[0 ], yv0);
  _mm_storeu_ps(&y[4 ], yv1);
  _mm_storeu_ps(&y[8 ], yv2);
  _mm_storeu_ps(&y[12], yv3);
  _mm_storeu_ps(&y[16], yv4);
  _mm_storeu_ps(&y[20], yv5);
  _mm_storeu_ps(&y[24], yv6);
  _mm_storeu_ps(&y[28], yv7);

  return;

}





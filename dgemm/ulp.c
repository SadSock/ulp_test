#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int main(){

  const int n = 1000;
  const int m = 1000;


  double *mpfr    = (double *)malloc(n * m * sizeof(double));
  FILE *fp_mpfr = fopen("mpfr.bin", "rb");
  fread(mpfr, sizeof(double), n * m, fp_mpfr);
  fclose(fp_mpfr);


  printf("test x86\n");
  double *x86 = (double *)malloc(n * m * sizeof(double));
  FILE *fp_x86 = fopen("x86.bin", "rb");
  FILE *fp_x86_ulp = fopen("x86_ulp.txt","w");
  fread(x86, sizeof(double), n * m, fp_x86);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      double a = mpfr[i * m + j];
      double b = x86[i * m + j];
      double esp = fabs(nexttoward(a, INFINITY) - a);
      double ulp = fabs(a - b) / esp;
      fprintf(fp_x86_ulp, "%.2f\n", ulp);
    }
  }
  fclose(fp_x86_ulp);
  fclose(fp_x86);

  printf("test nvidia_gpu\n");
  double *nvidia_gpu  = (double *)malloc(n * m * sizeof(double));
  FILE *fp_nvidia_gpu = fopen("nvidia_gpu.bin", "rb");
  FILE *fp_nvidia_gpu_ulp = fopen("nvidia_gpu_ulp.txt","w");
  fread(nvidia_gpu, sizeof(double), n * m, fp_nvidia_gpu);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      double a = mpfr[i * m + j];
      double b = nvidia_gpu[i * m + j];
      double esp = fabs(nexttoward(a, INFINITY) - a);
      double ulp = fabs(a - b) / esp;
      fprintf(fp_nvidia_gpu_ulp, "%.2f\n", ulp);
    }
  }
  fclose(fp_nvidia_gpu_ulp);
  fclose(fp_nvidia_gpu);


  printf("test amd_gpu\n");
  double *amd_gpu  = (double *)malloc(n * m * sizeof(double));
  FILE *fp_amd_gpu = fopen("amd_gpu.bin", "rb");
  FILE *fp_amd_gpu_ulp = fopen("amd_gpu_ulp.txt","w");
  fread(amd_gpu, sizeof(double), n * m, fp_amd_gpu);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      double a = mpfr[i * m + j];
      double b = amd_gpu[i * m + j];
      double esp = fabs(nexttoward(a, INFINITY) - a);
      double ulp = fabs(a - b) / esp;
      fprintf(fp_amd_gpu_ulp, "%.2f\n", ulp);
    }
  }
  fclose(fp_amd_gpu_ulp);
  fclose(fp_amd_gpu);

  return 0;
}
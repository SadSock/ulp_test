#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>
#include <time.h>

int main() {
  int n = 1000, m = 1000, k = 1000; // 定义矩阵的维度

  clock_t start, end;
  double cpu_time_used;

  // 动态分配内存并读取矩阵数据
  double *a, *b, *c;
  a = (double *)malloc(n * k * sizeof(double));
  b = (double *)malloc(k * m * sizeof(double));
  c = (double *)malloc(n * m * sizeof(double));
  FILE *fp;
  fp = fopen("data.bin", "rb");

  size_t result;
  result = fread(a, sizeof(double), n * k, fp);
  if (result != n * k) {
    printf("Failed to read file\n");
    return 1;
  }
  result = fread(b, sizeof(double), k * m, fp);
  if (result != k * m) {
    printf("Failed to read file\n");
    return 1;
  }

  fclose(fp);

  start = clock();
  // 计算矩阵乘法
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, m, k, 1.0, a, k, b,
              m, 0.0, c, m);
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU Time Used: %f seconds\n", cpu_time_used);

  // 将结果保存到文件中
  fp = fopen("x86.bin", "wb");
  fwrite(c, sizeof(double), n * m, fp);
  fclose(fp);

  // 释放内存
  free(a);
  free(b);
  free(c);
  return 0;
}

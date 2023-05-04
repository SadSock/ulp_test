#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>
#include <unistd.h>

#define PRECISION 64000 // 设置精度为25600位

int main() {
    int n = 1000, m = 1000, k = 1000; // 矩阵的大小
    FILE *fdata = fopen("data.bin", "rb"); // 打开数据文件
    FILE *fmpfr = fopen("mpfr.bin", "wb"); // 打开结果文件
    double *a = (double*) malloc(n * k * sizeof(double)); // 存储矩阵a
    double *b = (double*) malloc(k * m * sizeof(double)); // 存储矩阵b
    double *c = (double*) malloc(n * m * sizeof(double)); // 存储矩阵b
    
    // 初始化矩阵a和矩阵b
    fread(a, sizeof(double), n * k, fdata);
    fread(b, sizeof(double), k * m, fdata);

    // 初始化mpfr变量
    mpfr_set_default_prec(PRECISION); // 设置精度

    // 计算矩阵乘法
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
          mpfr_t ret_mpfr;
          mpfr_init(ret_mpfr);
          mpfr_set_d(ret_mpfr, 0, MPFR_RNDN); // 将c[i][j]初始化为0
          for (int t = 0; t < k; t++) {
            mpfr_t tmp;
            mpfr_init(tmp);
            mpfr_set_d(tmp, a[i * k + t], MPFR_RNDN);
            mpfr_mul_d(tmp, tmp, b[t * m + j], MPFR_RNDN);
            mpfr_add(ret_mpfr, ret_mpfr, tmp, MPFR_RNDN);
            mpfr_clear(tmp);
            }
            printf("Progress: %d/1000000 %.02f%%\r", i * m + j,
                   (double)(i * m + j) / 1000 / 1000 * 100);
            fflush(stdout);
            c[i * m + j] = mpfr_get_d(ret_mpfr, MPFR_RNDN);
            mpfr_clear(ret_mpfr);
        }
    }

    // 将结果写入文件
    fwrite(c, sizeof(double), n * m, fmpfr);
    
    // 释放资源
    free(a);
    free(b);
    free(c);
    fclose(fdata);
    fclose(fmpfr);

    return 0;
}

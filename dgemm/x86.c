#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>

int main() {
    int n = 1000, m = 1000, k = 1000;  // 定义矩阵的维度

    // 动态分配内存并读取矩阵数据
    double *a, *b, *c;
    a = (double *)malloc(n * k * sizeof(double));
    b = (double *)malloc(k * m * sizeof(double));
    c = (double *)malloc(n * m * sizeof(double));
    FILE *fp;
    fp = fopen("data.bin", "rb");
    fread(a, sizeof(double), n * k, fp);
    fread(b, sizeof(double), k * m, fp);
    fclose(fp);

    // 计算矩阵乘法
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, m, k, 1.0, a, k, b, m, 0.0, c, m);

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

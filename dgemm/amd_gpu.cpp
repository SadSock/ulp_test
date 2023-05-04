#include <stdio.h>
#include <stdlib.h>
#include <rocblas/rocblas.h>

int main() {
    const int n = 1000;
    const int k = 1000;
    const int m = 1000;

    double *A = (double*)malloc(n * k * sizeof(double));
    double *B = (double*)malloc(k * m * sizeof(double));
    double *C = (double*)malloc(n * m * sizeof(double));



    // 从文件中读取矩阵 A 和 B 的数据
    FILE* fp = fopen("data.bin", "rb");
    fread(A, sizeof(double), n * k, fp);
    fread(B, sizeof(double), k * m, fp);
    fclose(fp);

    // 在 C 中填充零值
    for (int i = 0; i < n * m; ++i) {
        C[i] = 0.0;
    }


    rocblas_handle handle;
    rocblas_create_handle(&handle);

    double *d_A, *d_B, *d_C;
    hipMalloc(&d_A, n * k * sizeof(double));
    hipMalloc(&d_B, k * m * sizeof(double));
    hipMalloc(&d_C, n * m * sizeof(double));

    hipMemcpy(d_A, A, n * k * sizeof(double), hipMemcpyHostToDevice);
    hipMemcpy(d_B, B, k * m * sizeof(double), hipMemcpyHostToDevice);

    const double alpha = 1.0;
    const double beta = 0.0;

    rocblas_dgemm(handle, rocblas_operation_none, rocblas_operation_none, n, m, k, &alpha, d_B, k, d_A, m, &beta, d_C, m);

    hipMemcpy(C, d_C, n * m * sizeof(double), hipMemcpyDeviceToHost);

    fp = fopen("amd_gpu.bin", "wb");
    fwrite(C, sizeof(double), n * m, fp);
    fclose(fp);

    hipFree(d_A);
    hipFree(d_B);
    hipFree(d_C);

    rocblas_destroy_handle(handle);

    free(A);
    free(B);
    free(C);

    return 0;
}
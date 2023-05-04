#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <cublas_v2.h>


int main(void)
{
    const int n = 1000;
    const int k = 1000;
    const int m = 1000;

    double *A, *B, *C;
    double alpha = 1.0, beta = 0.0;

    A = (double*) malloc(n * k * sizeof(double));
    B = (double*) malloc(k * m * sizeof(double));
    C = (double*) malloc(n * m * sizeof(double));

    // 从文件中读取矩阵 A 和 B 的数据
    FILE* fp = fopen("data.bin", "rb");
    fread(A, sizeof(double), n * k, fp);
    fread(B, sizeof(double), k * m, fp);
    fclose(fp);

    // 在 C 中填充零值
    for (int i = 0; i < n * m; ++i) {
        C[i] = 0.0;
    }

    double* d_A, *d_B, *d_C;
    cudaMalloc(&d_A, n * k * sizeof(double));
    cudaMalloc(&d_B, k * m * sizeof(double));
    cudaMalloc(&d_C, n * m * sizeof(double));

    cublasHandle_t handle;
    cublasCreate(&handle);

    cudaMemcpy(d_A, A, n * k * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, k * m * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_C, C, n * m * sizeof(double), cudaMemcpyHostToDevice);

    cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m, n, k, &alpha, d_B, m, d_A, k, &beta, d_C, m);

    cudaMemcpy(C, d_C, n * m * sizeof(double), cudaMemcpyDeviceToHost);

    cublasDestroy(handle);


    fp = fopen("nvidia_gpu.bin", "wb");
    fwrite(C, sizeof(double), n * m, fp);
    fclose(fp);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(A);
    free(B);
    free(C);

    return 0;
}

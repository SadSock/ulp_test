#include <cstdint>
#include <stdio.h>
#include <stdint.h>

// 定义向量长度
#define N 4

// CUDA 核函数，用于计算两个向量的点积
__global__ void dot_product(double *a, double *b, double *result) {
    result[0] = 0.0f;
    for(int i = 0; i < 4; i++){
        result[0] += a[i] * b[i];
    }    
}

int main() {
    double a[N] = {0.0f};
    double b[N] = {0.0f};
    double result[N] = {0.0f};

    FILE *fp;
    uint64_t num;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        if (fscanf(fp, "%la", &a[i]) != 1) {
            printf("Error reading file\n");
            return 1;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (fscanf(fp, "%la", &b[i]) != 1) {
            printf("Error reading file\n");
            return 1;
        }
    }

    // 使用当前时间作为随机数生成器的种子
    srand(time(NULL));
    fclose(fp);
    // 分配 GPU 内存
    double *dev_a, *dev_b, *dev_result;
    cudaMalloc((void**)&dev_a, N * sizeof(double));
    cudaMalloc((void**)&dev_b, N * sizeof(double));
    cudaMalloc((void**)&dev_result, N * sizeof(double));
    for (int j = 0; j < 100; j++){
        // 生成8个随机数，并将其存储在数组中
        for (int i = 0; i < 4; i++) {
            num = (((uint64_t)rand()) << 32) | rand();
            *(uint64_t *)&a[i] = num;
            num = (((uint64_t)rand()) << 32) | rand();
            *(uint64_t *)&b[i] = num;
        }
        // 将数据复制到 GPU 内存中
        cudaMemcpy(dev_a, a, N * sizeof(double), cudaMemcpyHostToDevice);
        cudaMemcpy(dev_b, b, N * sizeof(double), cudaMemcpyHostToDevice);

        // 定义块大小和线程大小
        dim3 block_size(1, 1, 1);
        dim3 grid_size(1, 1, 1);

        // 调用 CUDA 核函数
        dot_product<<<grid_size, block_size>>>(dev_a, dev_b, dev_result);

        // 将结果从 GPU 内存复制回 CPU 内存
        cudaMemcpy(result, dev_result, N * sizeof(double),
                   cudaMemcpyDeviceToHost);

        // 计算点积并打印结果
        double dot_product = 0.0f;
        for (int i = 0; i < 4; i++) {
            dot_product += a[i] * b[i];
        }

        if(dot_product != result[0]){
            printf("X86  %f\n", dot_product);
            printf("cuda %f\n", result[0]);

            // 打印读取的值
            for (int i = 0; i < 4; i++) {
              printf("a[%d] = %la\n", i, a[i]);
            }
            for (int i = 0; i < 4; i++) {
              printf("b[%d] = %la\n", i, b[i]);
            }
        }
    }
    // 释放 GPU 内存
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_result);

    return 0;
	}

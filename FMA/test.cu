#include <cstdint>
#include <stdio.h>
#include <stdint.h>
#include <mpfr.h>

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
    double GPU_ret[N] = {0.0f};


    // 使用当前时间作为随机数生成器的种子
    srand(time(NULL));
    // 分配 GPU 内存
    double *dev_a, *dev_b, *dev_result;
    cudaMalloc((void**)&dev_a, N * sizeof(double));
    cudaMalloc((void**)&dev_b, N * sizeof(double));
    cudaMalloc((void**)&dev_result, N * sizeof(double));
    size_t cnt = 0;
            while(cnt < 100000){
        // 生成8个随机数，并将其存储在数组中
    uint64_t num;
        for (int i = 0; i < 4; i++) {
            num = (((uint64_t)rand()) << 32) | rand();
            *(uint64_t *)&a[i] = num;
            num = (((uint64_t)rand()) << 32) | rand();
            *(uint64_t *)&b[i] = num;
        }
            //// 打印读取的值
            //for (int i = 0; i < 4; i++) {
              //printf("a[%d] = %la\n", i, a[i]);
            //}
            //for (int i = 0; i < 4; i++) {
              //printf("b[%d] = %la\n", i, b[i]);
            //}

        // 将数据复制到 GPU 内存中
        cudaMemcpy(dev_a, a, N * sizeof(double), cudaMemcpyHostToDevice);
        cudaMemcpy(dev_b, b, N * sizeof(double), cudaMemcpyHostToDevice);

        // 定义块大小和线程大小
        dim3 block_size(1, 1, 1);
        dim3 grid_size(1, 1, 1);

        // 调用 CUDA 核函数
        dot_product<<<grid_size, block_size>>>(dev_a, dev_b, dev_result);

        // 将结果从 GPU 内存复制回 CPU 内存
        cudaMemcpy(GPU_ret, dev_result, N * sizeof(double),
                   cudaMemcpyDeviceToHost);

        // CPU计算点积并打印结果
        double cpu_ret = 0.0f;
        for (int i = 0; i < 4; i++) {
            cpu_ret += a[i] * b[i];
        }

    if(isinf(cpu_ret) || isinf(GPU_ret[0]))
        continue;

  mpfr_t ma[N], mb[N], mpfr_ret;
  mpfr_t ma_gpu, ma_cpu;
  mpfr_t ma_dgpu, ma_dcpu;
    
    mpfr_init2(ma_gpu, 1024);
    mpfr_set_d(ma_gpu, GPU_ret[0], MPFR_RNDN);
    
    mpfr_init2(ma_cpu, 1024);
    mpfr_set_d(ma_cpu, cpu_ret, MPFR_RNDN);
  
        
  for (int i = 0; i < N; i++) {
    mpfr_init2(ma[i], 1024);
    mpfr_set_d(ma[i], a[i], MPFR_RNDN);
  }

  
  for (int i = 0; i < N; i++) {
    mpfr_init2(mb[i], 1024);
    mpfr_set_d(mb[i], b[i], MPFR_RNDN);
  }

  mpfr_init2(mpfr_ret, 1024);
  mpfr_set_d(mpfr_ret, 0.0, MPFR_RNDN);

  for (int i = 0; i < N; i++) {
    mpfr_fma(mpfr_ret, ma[i], mb[i], mpfr_ret, MPFR_RNDN);
  }


    mpfr_init2(ma_dcpu, 1024);
    mpfr_init2(ma_dgpu, 1024);
    mpfr_sub(ma_dgpu, ma_gpu, mpfr_ret, MPFR_RNDN);
    mpfr_sub(ma_dcpu, ma_cpu, mpfr_ret, MPFR_RNDN);
    
    mpfr_abs(ma_dgpu, ma_dgpu, MPFR_RNDN);
    mpfr_abs(ma_dcpu, ma_dcpu, MPFR_RNDN);


 int cmp = mpfr_cmp(ma_dgpu, ma_dcpu);
    if (cmp < 0) {
        printf("GPU win\n");
    } else if (cmp > 0) {
        printf("cpu win\n");
    } else {
        printf("double win\n");
    }

  mpfr_printf("mpfr %.100RNf\n", mpfr_ret);
  printf("X86  %f\n", cpu_ret);
  printf("cuda %f\n", GPU_ret[0]);
cnt = cnt + 1;
    }
    // 释放 GPU 内存
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_result);

    return 0;
	}

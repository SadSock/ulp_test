#include <stdio.h>
#include <stdint.h>
#include <math.h>

__global__ void double2uint64(double ret_f64) {
  uint64_t ret_u64;
  // 从外部读入
  ret_u64 = ret_f64;
  printf("%lx\n", ret_u64);

  // 先赋值给double类型，再隐式转换为uint64_t
  ret_f64 = ldexp(1.0, 64);
  ret_u64 = ret_f64;
  printf("%lx\n", ret_u64);

  // 直接隐式转换并赋值给uint64_t
  ret_u64 = ldexp(1.0, 64);
  printf("%lx\n", ret_u64);
}

int main(void)
{
  double ret_f64 = ldexp(1.0, 64);
  // 启动CUDA内核函数
  double2uint64<<<1, 1>>>(ret_f64);
  cudaDeviceSynchronize();
  return 0;
}

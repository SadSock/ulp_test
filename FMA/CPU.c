#include <stdio.h>
#include <stdint.h>

// 定义向量长度
#define N 4

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

  // 计算点积并打印结果
  double dot_product = 0.0f;
  for (int i = 0; i < 4; i++) {
    dot_product += a[i] * b[i];
  }

  printf("CPU: %f %la\n", dot_product, dot_product);

  // 打印读取的值
  for (int i = 0; i < 4; i++) {
    printf("a[%d] = %la\n", i, a[i]);
  }
  for (int i = 0; i < 4; i++) {
    printf("b[%d] = %la\n", i, b[i]);
  }

  return 0;
}

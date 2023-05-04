#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n = 1000, m = 1000, k = 2;  // 定义矩阵的维度
    double *data;                   // 定义矩阵指针
    data = (double *)malloc(n * m * k * sizeof(double));  // 动态分配内存

    // 随机生成矩阵数据
    srand(time(NULL));  // 初始化随机数种子
    for (int i = 0; i < n * m * k; i++) {
        data[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;  // 生成-1~1之间的双精度浮点数
    }

    // 将矩阵数据写入二进制文件
    FILE *fp = fopen("data.bin", "wb");
    fwrite(data, sizeof(double), n * m * k, fp);  // 写入数据
    fclose(fp);

    // 释放内存
    free(data);
    return 0;
}

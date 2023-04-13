#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main(int argc, char *argv[]) {

  uint64_t ret_u64;
  double ret_f64;

  FILE *fp;
  fp = fopen("input.txt", "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  if (fscanf(fp, "%lx",(uint64_t *)&ret_f64) != 1){
    printf("Error reading file\n");
    return 1;
  }

  ret_u64 = ret_f64;
  printf("%lx\n", ret_u64);

  ret_f64 = ldexp(1.0, 64);
  ret_u64 = ret_f64;
  printf("%lx\n", ret_u64);

  ret_u64 = ldexp(1.0, 64);
  printf("%lx\n", ret_u64);
  return 0;
}

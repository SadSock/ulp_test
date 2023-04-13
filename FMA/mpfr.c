#include <mpfr.h>
#include <stdint.h>
#include <stdio.h>
#define N 4

int main() {
  double a[N] = {0.0f};
  double b[N] = {0.0f};
  double result[N] = {0.0f};

  mpfr_t ma[N], mb[N], dot_product;
  FILE *fp;
  uint64_t num;

  fp = fopen("input.txt", "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  printf("Error reading file\n");
  for (int i = 0; i < N; i++) {
    if (fscanf(fp, "%la", &a[i]) != 1) {
      mpfr_init2(ma[i], 256);
      printf("Error reading file\n");
      return 1;
    }
  }

  printf("Error reading file\n");
  for (int i = 0; i < N; i++) {
    if (fscanf(fp, "%la", &b[i]) != 1) {
      mpfr_init2(mb[i], 256);
      printf("Error reading file\n");
      return 1;
    }
  }
  printf("Error reading file\n");
  mpfr_init2(dot_product, 256);
  mpfr_set_d(dot_product, 0.0, MPFR_RNDN);
  printf("1 Error reading file\n");

  mpfr_mul(dot_product, ma[0], mb[0], MPFR_RNDN);
  for (int i = 0; i < N; i++) {
    printf("2 Error reading file\n");
    mpfr_fma(dot_product, ma[i], mb[i], dot_product, MPFR_RNDN);
  }

  printf("3 Error reading file\n");
  mpfr_printf("The dot product is %.10RNf\n", dot_product);
  return 0;
}

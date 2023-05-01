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
  
  for (int i = 0; i < N; i++) {
    if (fscanf(fp, "%la", &a[i]) != 1) {
      printf("Error reading file\n");
      return 1;
    }
    mpfr_init2(ma[i], 1024);
    mpfr_set_d(ma[i], a[i], MPFR_RNDN);
  }

  
  for (int i = 0; i < N; i++) {
    if (fscanf(fp, "%la", &b[i]) != 1) {
      printf("Error reading file\n");
      return 1;
    }
    mpfr_init2(mb[i], 1024);
    mpfr_set_d(mb[i], b[i], MPFR_RNDN);
  }

  mpfr_init2(dot_product, 1024);
  mpfr_set_d(dot_product, 0.0, MPFR_RNDN);

  for (int i = 0; i < N; i++) {
    mpfr_fma(dot_product, ma[i], mb[i], dot_product, MPFR_RNDN);
  }

  double ret_f64 = mpfr_get_d(dot_product, MPFR_RNDN);
  mpfr_printf("mpfr = %.150RNf\n", dot_product);
  printf("ret_f64 = %la\n", ret_f64);
    return 0;
}

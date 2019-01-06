#define MATHLIB_STANDALONE
#include <Rmath.h>
#include <stdio.h>

void show_seed();

void printLn(double x) {
  printf("%f\n", x);
}

int main() {
  printLn(runif(0.0, 1.0));
  set_seed(1234,1);
  printLn(runif(0.0, 1.0));
  printLn(runif(0.0, 1.0));
  return 0;
}

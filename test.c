#include "Rmath_mt.h"

void printLn(double x) {
  printf("%f\n", x);
}

int main() {
  printLn(unif_rand());
  r_set_seed(1234);
  printLn(unif_rand());
  printLn(runif(0.0, 1.0));
  printLn(pnorm(1.96, 0, 1, 1, 0));
  printLn(dwilcox(100, 10, 20, 0));
  printLn(pwilcox(100, 10, 20, 0, 0));
  printLn(qwilcox(0.5, 10, 20, 0, 0));
  printLn(rwilcox(10, 20));
  return 0;
}

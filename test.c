#include "mt_unif_rand.h"

void printLn(double x) {
  printf("%f\n", x);
}

int main() {
  printLn(unif_rand());
  set_seed(1234,5678);
  printLn(runif(0.0, 1.0));
  printLn(runif(0.0, 1.0));
  printLn(pnorm(1.96, 0, 1, 1, 0));
  // printLn(dwilcox(100, 10, 20, 0));
  return 0;
}

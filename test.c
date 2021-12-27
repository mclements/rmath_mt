#include "mt_unif_rand.h"

void printLn(double x) {
  printf("%f\n", x);
}

int main() {
  printLn(runif(0.0, 1.0));
  r_set_seed(1234);
  printLn(runif(0.0, 1.0));
  printLn(runif(0.0, 1.0));
  return 0;
}

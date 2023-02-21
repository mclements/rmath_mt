#define MATHLIB_STANDALONE
#include <Rmath.h>
#include <stdio.h>

void r_set_seed(unsigned int inseed);
void show_seed();

/* replacement/shadow functions for random numbers */
void set_seed(unsigned int seed1, unsigned int seed2);
double unif_rand(void);
double R_unif_index(double dn);

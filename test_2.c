#define MATHLIB_STANDALONE
#include <Rmath.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

//copied from src/main/RNG.c:
typedef unsigned int Int32;
static Int32 dummy[625];

/* ===================  Mersenne Twister ========================== */
/* From http://www.math.keio.ac.jp/~matumoto/emt.html */

/* A C-program for MT19937: Real number version([0,1)-interval)
   (1999/10/28)
     genrand() generates one pseudorandom real number (double)
   which is uniformly distributed on [0,1)-interval, for each
   call. sgenrand(seed) sets initial values to the working area
   of 624 words. Before genrand(), sgenrand(seed) must be
   called once. (seed is any 32-bit integer.)
   Integer generator is obtained by modifying two lines.
     Coded by Takuji Nishimura, considering the suggestions by
   Topher Cooper and Marc Rieffel in July-Aug. 1997.

   Copyright (C) 1997, 1999 Makoto Matsumoto and Takuji Nishimura.
   When you use this, send an email to: matumoto@math.keio.ac.jp
   with an appropriate reference to your work.

   REFERENCE
   M. Matsumoto and T. Nishimura,
   "Mersenne Twister: A 623-Dimensionally Equidistributed Uniform
   Pseudo-Random Number Generator",
   ACM Transactions on Modeling and Computer Simulation,
   Vol. 8, No. 1, January 1998, pp 3--30.
*/

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0df   /* constant vector a */
#define UPPER_MASK 0x80000000 /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y)  (y >> 11)
#define TEMPERING_SHIFT_S(y)  (y << 7)
#define TEMPERING_SHIFT_T(y)  (y << 15)
#define TEMPERING_SHIFT_L(y)  (y >> 18)

static Int32 *mt = dummy+1; /* the array for the state vector  */
static int mti = N+1;

static
double MT_unif_rand(void)
{
    Int32 y;
    static Int32 mag01[2]={0x0, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti == N+1) {
      set_seed(1234,5678);
      dummy[0] = N;
    }
	
    mti = dummy[0];

    if (mti == N) { /* generate N words at one time */
	int kk;

	for (kk = 0; kk < N - M; kk++) {
	    y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
	    mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
	}
	for (; kk < N - 1; kk++) {
	    y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
	    mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
	}
	y = (mt[N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
	mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];

	mti = 0;
    }

    y = mt[mti++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);
    dummy[0] = mti;
    return ( (double)y * 2.3283064365386963e-10 ); /* reals: [0,1)-interval */
}

// set the seed as per R's set.seed()
void r_set_seed(unsigned int inseed) {
  Int32 seed = inseed;
  int j;
  for(j = 0; j < 50; j++)
    seed = (69069 * seed + 1);
  /* seed[0] is mti, *but* this is needed for historical consistency */
  for(j = 0; j <= N; j++) {
    seed = (69069 * seed + 1);
    dummy[j] = seed;
  }
  dummy[0] = N;
}

#undef N
#undef M
#undef MATRIX_A
#undef UPPER_MASK
#undef LOWER_MASK
#undef TEMPERING_MASK_B
#undef TEMPERING_MASK_C
#undef TEMPERING_SHIFT_U
#undef TEMPERING_SHIFT_S
#undef TEMPERING_SHIFT_T
#undef TEMPERING_SHIFT_L

// user-defined RNG
double unif_rand(void) { return MT_unif_rand(); }
void set_seed(unsigned int inseed, unsigned int ignored) {
  r_set_seed(inseed);
}
//copied from src/nmath/standalone/sunif.c:
//generate a random non-negative integer < 2 ^ bits in 16 bit chunks
static double rbits(int bits)
{
    int_least64_t v = 0;
    for (int n = 0; n <= bits; n += 16) {
        int v1 = (int) floor(unif_rand() * 65536);
        v = 65536 * v + v1;
    }
    // mask out the bits in the result that are not needed
    return (double) (v & ((1L << bits) - 1));
}
double R_unif_index(double dn)
{
    // rejection sampling from integers below the next larger power of two
    if (dn <= 0)
        return 0.0;
    int bits = (int) ceil(log2(dn));
    double dv;
    do { dv = rbits(bits); } while (dn <= dv);
    return dv;
}

void printLn(double x) {
  printf("%f\n", x);
}

int main() {
  printLn(unif_rand());
  r_set_seed(1234);
  printLn(runif(0.0, 1.0));
  printLn(pnorm(1.96, 0, 1, 1, 0));
  printLn(dwilcox(100, 10, 20, 0));
  printLn(pwilcox(100, 10, 20, 0, 0));
  printLn(qwilcox(0.5, 10, 20, 0, 0));
  printLn(rwilcox(10, 20));
  return 0;
}


LIBRMATH_A = $(shell pkg-config --variable=libdir libRmath)/libRmath.a

test:
	gcc -c mt_unif_rand.c
	gcc -o test test.c mt_unif_rand.o ${LIBRMATH_A} 
	./test

clean:
	rm -f test
	rm -f *.o

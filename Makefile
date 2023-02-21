
test: test.c Rmath_mt.c
	gcc -static -o test test.c Rmath_mt.c -lRmath -lm
	./test

test_2: test_2.c
	gcc -static -o test_2 test_2.c -lRmath -lm
	./test_2

clean:
	rm -f test *.o

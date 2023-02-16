
test:
	gcc --static -o test test.c mt_unif_rand.c -lRmath -lm
	./test

clean:
	rm -f test *.o

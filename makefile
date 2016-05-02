all: testSpi 

testSpi: testSpi.o
	gcc -Ofast -std=c11 testSpi.o -lbcm2835 -o testSpi

testSpi.o: testSpi.c
	gcc -O3 -std=c11 -c testSpi.c

clean:
	rm -rf *o testSpi

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void SetBit(int A[], int k);
void ClearBit(int A[], int k);
int GetBit(int A[], int k);
int NoEvenDigits(int i);
int contains(int *A, int val, int max);
int isCircularPrime(int i, int *list, int max);
void shift(int *A, int size);

int main() {

	int i, j, idx = 0, n = 0;
 	int *primes = malloc(125000);
	int *list = malloc(125000);
	
	for (i = 0; i < 1000000; i++) {
		SetBit(primes,i);
	}

	for (i = 2; i <= 1000; i++) {
		if (GetBit(primes,i)) {
			for (j = i*i; j <= 1000000; j += i) {
				ClearBit(primes,j);
			}	
		}
	}	

	for (i = 2; i <= 1000000; i++) {
		if (GetBit(primes,i) && NoEvenDigits(i)) {
			list[idx++] = i;
		}
	}	

	printf("We have %d primes less than one million with only odd digits (not including 2)\n",idx);
	printf("Circular primes less than 1 million:\n");
	for (i = 0; i < idx; i++) {
		if (isCircularPrime(list[i],list,idx)) {
			printf("%d\n",list[i]);
			n++;
		}
	}
	printf("Number: %d\n",n);

	return 0;
}

int isCircularPrime(int i, int *list, int max) {

	int j, k;
	int n = i;
	int numDigits = 0;
	int rotate = 0;
	int *digits;
	int idx = 0;
	
	while (n > 0) {
		numDigits++;
		n /= 10;
	}

	digits = malloc(numDigits);
	n = i;
	idx = numDigits-1;

	while (n > 0) {
		digits[idx--] = (n%10);
		n /= 10;
	}


	for (j = 0; j < numDigits-1; j++) {
		shift(digits,numDigits);
		for (k = numDigits-1; k >= 0; k--) {
			rotate += pow(10.0,k)*digits[numDigits-k-1];
		}
		if (!contains(list,rotate,max)) return 0;
		rotate = 0;
	}

	return 1;
}

void shift(int *A, int size) {
	
	int i;
	int temp[size];
	
	for (i = 0; i < size; i++) {
		temp[i] = A[i];
	}

	for (i = 0; i < size; i++) {
		A[i] = temp[(i+1)%size];
	}
}

int contains(int *A, int val, int max) {

	int i;
	for (i = 0; i < max; i++) {
		if (A[i] == val) return 1;
	}
	return 0;
}

int NoEvenDigits(int i) {

	int n = i;
	while (n > 0) {
		if ((n % 10)%2 == 0 && i > 2) return 0;
		n /= 10;
	}
	return 1;
}

void SetBit(int A[], int k) {

	A[k/32] |= 1 << (k%32);
}

void ClearBit(int A[], int k) {

	A[k/32] &= ~(1 << (k%32));
}

int GetBit(int A[], int k) {

	return ((A[k/32] & (1 << (k%32) )) != 0) ;
}

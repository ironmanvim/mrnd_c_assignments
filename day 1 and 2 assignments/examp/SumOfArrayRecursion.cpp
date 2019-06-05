#include<stdio.h>

long sum(int *a, int size) {
	if (size <= 0) {
		return 0;
	}
	if (size == 1) {
		return a[0];
	}
	return sum(a + 1, size - 1) + a[0];
}
/*
int main() {
	int a[] = { 1, 1 };
	long res = sum(a, 0);
	printf("%d", res);
	getchar();
}*/
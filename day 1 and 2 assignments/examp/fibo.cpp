#include <stdio.h>
#include <malloc.h>

int fiboMemo(int n, int *a) {
	if (a[n] != -1) {
		return a[n];
	}
	if (n == 0 || n == 1) {
		a[n] = n;
		return n;
	}
	int x = fiboMemo(n - 1, a);
	int y = fiboMemo(n - 2, a);
	a[n - 1] = x;
	a[n - 2] = y;
	return x + y;
}
int fibo(int n) {
	int *a = (int *)malloc(sizeof(int) * (n+1));
	for (int i = 0; i < n+1; i++) {
		a[i] = -1;
	}
	return fiboMemo(n, a);
}
//
//int main() {
//	int res = fibo(6);
//	printf("%d", res);
//	getchar();
//}	
#include <stdio.h>
#include <stdlib.h>
void twoColorSort(int *a, int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += a[i];
	}
	int i = 0;
	for (; i < size - sum; i++) {
		a[i] = 0;
	}
	for (; i < size; i++) {
		a[i] = 1;
	}
}
void threeColorSort(int *a, int size) {
	int one_count = 0, two_count = 0;
	for (int i = 0; i < size; i++) {
		if (a[i] == 1) one_count++;
		else if (a[i] == 2) two_count++;
	}
	int i = 0; 
	for (; i < size - (one_count + two_count); i++) {
		a[i] = 0;
	}
	for (; i < size - (two_count); i++) {
		a[i] = 1;
	}
	for (; i < size; i++) {
		a[i] = 2;
	}
}
/*
int main() {
	int a[] = { 0, 1, 0, 1, 0, 2, 1, 0, 1, 2, 0, 0, 1 };
	threeColorSort(a, 13);
	for (int i = 0; i < 13; i++) {
		printf("%d", a[i]);
	}
	getchar();
}*/
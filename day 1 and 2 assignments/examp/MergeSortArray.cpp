#include <stdio.h>
#include <stdlib.h>


void merge(int *array, int l, int mid, int u) {
	int iterStartL = l;
	int iterEndL = mid;
	int iterStartU = mid + 1;
	int iterEndU = u;
	int *temp = (int *)malloc(sizeof(int) * (u - l + 1));
	int iter_temp = 0;
	while ((iterStartL <= iterEndL) && (iterStartU <= iterEndU)) {
		if (array[iterStartL] > array[iterStartU]) {
			temp[iter_temp++] = array[iterStartU];
			iterStartU++;
		}
		else {
			temp[iter_temp++] = array[iterStartL];
			iterStartL++;
		}
	}
	while (iterStartL <= iterEndL) {
		temp[iter_temp++] = array[iterStartL];
		iterStartL++;
	}
	while (iterStartU <= iterEndU) {
		temp[iter_temp++] = array[iterStartU];
		iterStartU++;
	}
	for (int i = 0; i < iter_temp; i++) {
		array[i + l] = temp[i];
	}
}
void mergeSort(int *array, int l, int u) {
	if (l < u) {
		int mid = (l + u) / 2;
		mergeSort(array, l, mid);
		mergeSort(array, mid + 1, u);
		merge(array, l, mid, u);
	}
}

//int main() {
//	int a[] = { 1, 5, 6, 7, 2, 3, 9, 4 };
//	mergeSort(a, 0, 7);
//	for (int i = 0; i < 8; i++) {
//		printf("%d ", a[i]);
//	}
//	getchar();
//}
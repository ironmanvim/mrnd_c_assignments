#include <stdio.h>
#include <malloc.h>

int **matrix(int (*a)[100], int row1, int col1, int (*b)[100], int row2, int col2) {
	int **res = (int **)malloc(sizeof(int *) * row1);
	for (int i = 0; i < row1; i++) {
		res[i] = (int *)malloc(sizeof(int) * col2);
	}

	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++) {
			res[i][j] = 0;
			for (int k = 0; i < col1; k++) {
				res[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return NULL;
}
//int main() {
//	int a[][100] = {
//		{ 1, 2, 3 },
//		{ 4, 5, 6 },
//		{ 7, 8, 9 },
//	};
//	int b[][100] = {
//		{ 1 },
//		{ 2 },
//		{ 3 },
//	};
//}
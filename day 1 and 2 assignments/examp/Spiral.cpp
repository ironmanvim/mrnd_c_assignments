#include <stdio.h>
#include <stdlib.h>
void printLRUD(int (*matrix)[100], int from, int to, int constant, char direction, int *res, int *iter_res) {
	int i = from;
	while (i != to) {
		if (direction == 'l' || direction == 'r') {
			res[(*iter_res)++] = matrix[constant][i];
			// printf("%d ", matrix[constant][i]);
		}
		else {
			res[(*iter_res)++] = matrix[i][constant];
			// printf("%d ", matrix[i][constant]);
		}
		if (direction == 'l' || direction == 'd') {
			i++;
		}
		else {
			i--;
		}
	}
}
int *returnSpiral(int (*matrix)[100], int rows, int cols, int *res_size) {
	int *res = (int *)malloc(sizeof(int) * 100);
	int iter_res = 0;
	int r1 = 0, r2 = rows;
	int c1 = -1, c2 = cols - 1;
	while ((r1 != r2) || (c1 != c2)) {
		printLRUD(matrix, c1+1, c2+1, r1, 'l', res, &iter_res);
		// printf("\n");
		r1++;
		if (r1 >= r2) break;
		printLRUD(matrix, r1, r2, c2, 'd', res, &iter_res);
		// printf("\n");
		c2--;
		if (c1 >= c2) break;
		printLRUD(matrix, c2, c1, r2 - 1, 'r', res, &iter_res);
		// printf("\n");
		r2--;
		if (r1 >= r2) break;
		printLRUD(matrix, r2 - 1, r1 - 1, c1 + 1, 'u', res, &iter_res);
		// printf("\n");
		c1++;
		if (c1 >= c2) break;
	}
	*res_size = iter_res;
	return res;
}
/*
int main() {
	int rows = 4, cols = 6;
	/* scanf("%d%d", &rows, &cols);
	int **matrix = (int **)malloc(sizeof(int *) * rows);
	for (int i = 0; i < rows; i++) {
		matrix[i] = (int *)malloc(sizeof(int) * cols);
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	int matrix[][100] = {
		{ 1, 2, 3, 4, 5, 6 },
		{ 7, 8, 9, 10, 11, 12 },
		{ 13, 14, 15, 16, 17, 18 },
		{ 19, 20, 21, 22, 23, 24 }
	};

	/*for (int i = 0; i < 5; i++) {
		printLRUD(matrix, cols-1, -1, i, 'u');
		printf("\n");
	}
	int res_size = 0;
	int *res = returnSpiral(matrix, rows, cols, &res_size);
	for (int i = 0; i < res_size; i++) {
		printf("%d ", res[i]);
	}
	getchar();
}*/
#include <stdio.h>
#include <stdlib.h>

int **matrixTranspose(int **matrix, int rows, int cols) {
	int **newMaxtrix = (int **)malloc(sizeof(int *) * cols);
	for (int i = 0; i < cols; i++) {
		newMaxtrix[i] = (int *)malloc(sizeof(int) * rows);
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			newMaxtrix[j][i] = matrix[i][j];
		}
	}
	return newMaxtrix;
}
/*
int main() {
	int rows = 5, cols = 6;
	scanf("%d%d", &rows, &cols);
	int **matrix = (int **)malloc(sizeof(int *) * rows);
	for (int i = 0; i < cols; i++) {
		matrix[i] = (int *)malloc(sizeof(int) * cols);
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	printf("Old:\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("New:\n");
	int **resMatrix = matrixTranspose(matrix, rows, cols);
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			printf("%d ", resMatrix[i][j]);
		}
		printf("\n");
	}
	getchar();
}*/
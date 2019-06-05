#include <stdio.h>
#include <stdlib.h>

int **getPossibleIndices(int (*matrix)[6], int rows, int cols, int *index, int **visited, int *possible_len) {
	int **possible = (int **)malloc(sizeof(int *) * 4);
	for (int i = 0; i < 4; i++) {
		possible[i] = (int *)malloc(sizeof(int) * 2);
	}
	int k = 0;
	int x = index[0];
	int y = index[1];
	if (y + 1 != cols && matrix[x][y + 1] != 0 && visited[x][y + 1] != 1) {
		visited[x][y + 1] = 1;
		possible[k][0] = x;
		possible[k][1] = y + 1;
		k++;
	}
	if (x + 1 != rows && matrix[x + 1][y] != 0 && visited[x + 1][y] != 1) {
		visited[x + 1][y] = 1;
		possible[k][0] = x + 1;
		possible[k][1] = y;
		k++;
	}
	if (y - 1 != -1 && matrix[x][y - 1] != 0 && visited[x][y - 1] != 1) {
		visited[x][y - 1] = 1;
		possible[k][0] = x;
		possible[k][1] = y - 1;
		k++;
	}
	if (x - 1 != -1 && matrix[x - 1][y] != 0 && visited[x - 1][y] != 1) {
		visited[x-1][y] = 1;
		possible[k][0] = x - 1;
		possible[k][1] = y;
		k++;
	}
	*possible_len = k;
	return possible;
}
int solveMazeOptimized(int(*matrix)[6], int rows, int cols, int *start_index, int *end_index,int **visited) {
	int found = 0;
	int possible_size = 0;
	int min = 0;
	int **possible_indices = getPossibleIndices(matrix, rows, cols, start_index, visited, &possible_size);
	visited[start_index[0]][start_index[1]] = 1;
	for (int i = 0; i < possible_size; i++) {
		int res = solveMazeOptimized(matrix, rows, cols, possible_indices[i], end_index, visited);
		min += res;
	}
	if (start_index[0] == end_index[0] && start_index[1] == end_index[1])
		return min;
	return min;
}
int solveMaze(int(*matrix)[6], int rows, int cols, int *start_index, int *end_index, int **visited) {
	int found = 0;
	int possible_size = 0;
	int **possible_indices = getPossibleIndices(matrix, rows, cols, start_index, visited, &possible_size);
	visited[start_index[0]][start_index[1]] = 1;
	for (int i = 0; i < possible_size; i++) {
		int res = solveMaze(matrix, rows, cols, possible_indices[i], end_index, visited);
		if (res == 1) {
			visited[possible_indices[i][0]][possible_indices[i][1]] = 1;
			found = 1;
		}
		else if (res == 0) {
			visited[possible_indices[i][0]][possible_indices[i][1]] = 0;
		}
	}
	if (start_index[0] == end_index[0] && start_index[1] == end_index[1])
		return 1;
	return found;
}
int **maze(int (*matrix)[6], int rows, int cols, int *start_index, int *end_index) {
	int **result = (int **)malloc(sizeof(int *) * rows);
	for (int i = 0; i < rows; i++) {
		result[i] = (int *)malloc(sizeof(int) * cols);
		for (int j = 0; j < cols; j++) {
			result[i][j] = 0;
		}
	}
	int count = solveMazeOptimized(matrix, rows, cols, start_index, end_index, result);
	printf("%d\n", count);
	return result;
}

int main() {
	int a[6][6] = {
		{ 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 1, 0 },
		{ 1, 1, 0, 1, 0, 1 },
		{ 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 0, 1, 1, 1 },
		{ 0, 1, 1, 1, 1, 1 },
	};
	int start[] = { 5, 5 };
	int end[] = { 2, 3 };
	int **result = maze(a, 6, 6, start, end);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}
	getchar();
}


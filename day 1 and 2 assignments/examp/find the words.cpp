#include <stdio.h>
#include <string.h>

void search(char (*matrix)[100], int rows, int cols, char *word) {
	int len = strlen(word);
	int start_coordinates[2];
	int end_coordinates[2];
	int breaker = 1;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] == word[0]) {
				start_coordinates[0] = i;
				start_coordinates[1] = j;
				int k;
				/* Row Scanner Front */
				for (k = 0; word[k] != '\0'; k++) {
					if (word[k] != matrix[i][j + k]) {
						break;
					}
				}
				if (word[k] == '\0') {
					end_coordinates[0] = i;
					end_coordinates[1] = j + k - 1;
					printf("%d %d -> %d %d\n", i, j, end_coordinates[0], end_coordinates[1]);
				}
				/* Row Scanner Back */
				for (k = 0; word[k] != '\0'; k++) {
					if (word[k] != matrix[i][j - k]) {
						break;
					}
				}
				if (word[k] == '\0') {
					end_coordinates[0] = i;
					end_coordinates[1] = j - k + 1;
					printf("%d %d -> %d %d\n", i, j, end_coordinates[0], end_coordinates[1]);
				}
				/* Col Scanner Down */
				for (k = 0; word[k] != '\0'; k++) {
					if (word[k] != matrix[i + k][j]) {
						break;
					}
				}
				if (word[k] == '\0') {
					end_coordinates[0] = i + k - 1;
					end_coordinates[1] = j;
					printf("%d %d -> %d %d\n", i, j, end_coordinates[0], end_coordinates[1]);
				}
				/* Col Scanner Up */
				for (k = 0; word[k] != '\0'; k++) {
					if (word[k] != matrix[i - k][j]) {
						break;
					}
				}
				if (word[k] == '\0') {
					end_coordinates[0] = i - k + 1;
					end_coordinates[1] = j;
					printf("%d %d -> %d %d\n", i, j, end_coordinates[0], end_coordinates[1]);
				}
				/* L2R Diagonal Down Scanner */
				for (k = 0; word[k] != '\0'; k++) {
					if (word[k] != matrix[i + k][j + k]) {
						break;
					}
				}
				if (word[k] == '\0') {
					end_coordinates[0] = i + k - 1;
					end_coordinates[1] = j + k - 1;
					printf("%d %d -> %d %d\n", i, j, end_coordinates[0], end_coordinates[1]);
				}
				/* R2L Diagonal Down Scanner */
				for (k = 0; word[k] != '\0'; k++) {
					if (word[k] != matrix[i - k][j - k]) {
						break;
					}
				}
				if (word[k] == '\0') {
					end_coordinates[0] = i - k + 1;
					end_coordinates[1] = j - k + 1;
					printf("%d %d -> %d %d\n", i, j, end_coordinates[0], end_coordinates[1]);
				}
				/* L2R Diagonal Up Scanner */
				for (k = 0; word[k] != '\0'; k++) {
					if (word[k] != matrix[i - k][j + k]) {
						break;
					}
				}
				if (word[k] == '\0') {
					end_coordinates[0] = i - k + 1;
					end_coordinates[1] = j + k - 1;
					printf("%d %d -> %d %d\n", i, j, end_coordinates[0], end_coordinates[1]);
				}
				/* R2L Diagonal Up Scanner */
				for (k = 0; word[k] != '\0'; k++) {
					if (word[k] != matrix[i + k][j - k]) {
						break;
					}
				}
				if (word[k] == '\0') {
					end_coordinates[0] = i + k - 1;
					end_coordinates[1] = j - k + 1;
					printf("%d %d -> %d %d\n", i, j, end_coordinates[0], end_coordinates[1]);
				}
			}
		}
	}
}
//int main() {
//	char a[][100] = {
//		"vvmiv", "vimii", "vmmim", "vivvi", "vmima"
//	};
//	search(a, 5, 5, "vim");
//	getchar();
//}
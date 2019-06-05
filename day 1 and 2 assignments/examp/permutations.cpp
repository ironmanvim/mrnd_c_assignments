#include <stdio.h>
#include <malloc.h>

void permutate(int *permute, int level, int *a, int n) {
	for (int i = 0; i < level; i++) {
		if (level == 0) {
			break;
		}
		a[level - 1] = permute[i];
		if (level == 1) {
			for (int j = n - 1; j >= 0; j--) {
				printf("%d ", a[j]);
			}
			printf("\n");
		}
		else {
			int *temp = (int *)malloc(sizeof(int) * (level - 1));
			int k = 0;
			for (int j = 0; j < level; j++) {
				if (i != j) {
					temp[k++] = permute[j];
				}
			}
			permutate(temp, level - 1, a, n);
		}
	}
}
//int main() {
//	int res[3] = { 1, 3, 5 };
//	int temp[3];
//	permutate(res, 3, temp, 3);
//	getchar();
//}
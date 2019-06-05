//#include <stdio.h>
//#include <malloc.h>
//
//void sort(int *array, int size) {
//	for (int i = 0; i < size - 1; i++) {
//		for (int j = i + 1; j < size; j++) {
//			if (array[i] > array[j]) {
//				int temp = array[i];
//				array[i] = array[j];
//				array[j] = temp;
//			}
//		}
//	}
//}
//int permutateWithoutRepetition(int *permute, int level, int *a, int n) {
//	int count = 0;
//	for (int i = 0; i < level; i++) {
//		while (permute[i] == permute[i + 1]) {
//			i++;
//		}
//		if (level == 0) {
//			break;
//			return 0;
//		}
//		a[level - 1] = permute[i];
//		if (level == 1) {
//			for (int j = n - 1; j >= 0; j--) {
//				printf("%d ", a[j]);
//			}
//			printf("\n");
//			count++;
//		}
//		else {
//			int *temp = (int *)malloc(sizeof(int) * (level - 1));
//			int k = 0;
//			for (int j = 0; j < level; j++) {
//				if (i != j) {
//					temp[k++] = permute[j];
//				}
//			}
//			count += permutateWithoutRepetition(temp, level - 1, a, n);
//		}
//	}
//	return count;
//}
//int main() {
//	int res[7] = { 1, 3, 5, 5, 5, 1, 1 };
//	sort(res, 7);
//	int temp[7];
//	int count = permutateWithoutRepetition(res, 7, temp, 7);
//	printf("%d", count);
//	getchar();
//}
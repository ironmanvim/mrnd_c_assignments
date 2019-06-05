#include <stdio.h>

char printInvert(int a) {
	switch (a) {
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return 'E';
	case 4:
		return 'h';
	case 5:
		return '5';
	case 6:
		return '9';
	case 7:
		return 'L';
	case 8:
		return '8';
	case 9:
		return '6';
	default:
		return '\0';
	}
}
void printToLength(int level, int *a, int n) {
	for (int i = 0; i <= 9; i++) {
		if (level == 0) {
			break;
		}
		a[level-1] = i;
		if (level == 1) {
			for (int j = n-1; j >= 0; j--) {
				printf("%d", a[j]);
			}
			printf(" ");
		}
		else {
			printToLength(level - 1, a, n);
		}
	}
}
//int main() {
//	int a[3];
//	printToLength(3, a, 3);
//	getchar();
//}
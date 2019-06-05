#include <stdio.h>
int StairCase(int n, int k, int sum) {
	int count = 0;
	for (int i = 1; i <= k; i++) {
		if (sum > n) {
			return 0;
		}
		if (sum == n) {
			return 1;
		}
		else {
			count += StairCase(n, k, sum + i);
		}
	}
	return count;
}
int main() {
	int res = StairCase(4, 3, 0);
	printf("%d", res);
	getchar();
}
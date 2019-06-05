#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *compress(char *s) {
	char *res = (char *)malloc(sizeof(char) * strlen(s));
	int k = 0;
	int count = 0;
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] == s[i + 1]) {
			count++;
		}
		else if (count > 0) {
			char temp[20];
			_itoa(count+1, temp, 10);
			res[k++] = s[i];
			for (int j = 0; temp[j] != '\0'; j++) {
				res[k++] = temp[j];
			}
			count = 0;
		}
		else {
			res[k++] = s[i];
			count = 0;
		}
	}
	res[k++] = '\0';
	return res;
}
int main() {
	char quest[] = "abcdeff";
	char *res = compress(quest);
	printf("%s", res);
	getchar();
}
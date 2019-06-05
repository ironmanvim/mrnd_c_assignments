#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *next;
};
typedef struct Node Node;

Node *createNode(int data) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
Node *createLinkedListWithString(char *string) {
	Node *root = NULL;
	for (int i = 0; string[i] != '\0'; i++) {
		if (root == NULL) {
			root = createNode(string[i] - '0');
		}
		else {
			Node *temp;
			for (temp = root; temp->next != NULL; temp = temp->next);
			temp->next = createNode(string[i] - '0');
		}
	}
	return root;
}
void printLinkedList(Node *root) {
	for (Node *i = root; i != NULL; i = i->next) {
		printf("%d->", i->data);
	}
	printf("N");
}
int len(Node *node) {
	int count = 0;
	for (Node *i = node; i != NULL; i = i->next) {
		count++;
	}
	return count;
}
Node *sumOfLinkedLists(Node *a, Node *b) {
	int len_a = len(a);
	int len_b = len(b);
	int sum = len_a - len_b;
	Node *temp;
	if (sum > 0) {
		temp = a;
		while (sum) {
			sum--;
			temp = temp->next;
		}

	}
	else if (sum < 0) {
		temp = b;
		while (sum) {
			sum++;
			temp = temp->next;
		}
	}
	else {

	}
	return NULL;
}
//int main() {
//	Node *root1 = createLinkedListWithString("1234");
//	Node *root2 = createLinkedListWithString("567");
//}
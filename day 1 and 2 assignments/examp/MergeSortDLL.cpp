#include <stdio.h>
#include <stdlib.h>
struct DLNode {
	int data;
	struct DLNode *left;
	struct DLNode *right;
};
typedef struct DLNode DLNode;
DLNode *merge(DLNode *first, DLNode *second) {
	DLNode *root = NULL;
	DLNode *creater = NULL;
	DLNode *p1 = first, *p2 = second;
	while (p1 != NULL && p2 != NULL) {
		if (p1->data > p2->data) {
			if (creater == NULL) {
				creater = p2;
				root = creater;
			}
			else {
				creater->right = p2;
				p2->left = creater;
				creater = creater->right;
			}
			p2 = p2->right;
		}
		else {
			if (creater == NULL) {
				creater = p1;
				root = creater;
			}
			else {
				creater->right = p1;
				p1->left = creater;
				creater = creater->right;
			}
			p1 = p1->right;
		}
	}
	while (p1 != NULL) {
		creater->right = p1;
		p1->left = creater;
		creater = creater->right;
		p1 = p1->right;
	}
	while (p2 != NULL) {
		creater->right = p2;
		p2->left = creater;
		creater = creater->right;
		p2 = p2->right;
	}
	return root;
}
DLNode *mergeSort(DLNode *root) {
	if (root == NULL || root->right == NULL)
		return root;
	DLNode *mid = root, *mid_maker = root->right;
	if (mid != mid_maker) {
		while (mid_maker != NULL && mid_maker->right != NULL) {
			mid = mid->right;
			mid_maker = mid_maker->right->right;
		}
		mid = mid->right;
		mid->left->right = NULL;
		mid->left = NULL;
		DLNode *first = mergeSort(root);
		DLNode *second = mergeSort(mid);
		root = merge(first, second);
	}
	return root;
}
DLNode *createDLNode(int data) {
	DLNode *newNode = (DLNode *)malloc(sizeof(DLNode));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}
DLNode *createDLinkedListWithString(char *string) {
	DLNode *root = NULL;
	for (int i = 0; string[i] != '\0'; i++) {
		if (root == NULL) {
			root = createDLNode(string[i] - '0');
		}
		else {
			DLNode *temp;
			for (temp = root; temp->right != NULL; temp = temp->right);
			temp->right = createDLNode(string[i] - '0');
			temp->right->left = temp;
		}
	}
	return root;
}
void printDLinkedList(DLNode *root) {
	DLNode *i;
	for (i = root; i->right != NULL; i = i->right) {
		printf("%d->", i->data);
	}
	for (; i != NULL; i = i->left) {
		printf("<-%d", i->data);
	}
	printf("N");
}
//int main() {
//	DLNode *root = createDLinkedListWithString("9876543210");
//	root = mergeSort(root);
//	printDLinkedList(root);
//	getchar();
//}
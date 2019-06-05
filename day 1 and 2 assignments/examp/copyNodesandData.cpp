#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *next;
	struct Node *randomNext;
};
typedef struct Node Node;
Node *createLNode(int data) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	newNode->randomNext = NULL;
	return newNode;
}
Node *deepCopyWithHashing(Node *root) {
	Node *hash[100] = { NULL };
	Node *newRoot = NULL;
	Node *newNode;
	for (Node *i = root; i != NULL; i = i->next) {
		if (hash[i->data] == NULL) {
			newNode = createLNode(i->data);
			hash[i->data] = newNode;
			if (newRoot == NULL) {
				newRoot = newNode;
			}
		}
		else {
			newNode = hash[i->data];
		}
		if (i->next != NULL) {
			if (hash[i->next->data] == NULL) {
				Node *newNextNode = createLNode(i->next->data);
				hash[i->next->data] = newNextNode;
				newNode->next = newNextNode;
			}
			else {
				newNode->next = hash[i->next->data];
			}
		}
		else {
			newNode->next = NULL;
		}
		if (i->randomNext != NULL) {
			if (hash[i->randomNext->data] == NULL) {
				Node *newRandomNode = createLNode(i->randomNext->data);
				hash[i->randomNext->data] = newRandomNode;
				newNode->randomNext = newRandomNode;
			}
			else {
				newNode->randomNext = hash[i->randomNext->data];
			}
		}
		else {
			newNode->randomNext = NULL;
		}
	}
	return newRoot;
}

//int main() {
//	Node *one = createLNode(1);
//	Node *two = createLNode(2);
//	Node *three = createLNode(3);
//	Node *four = createLNode(4);
//	Node *five = createLNode(5);
//	Node *six = createLNode(6);
//	one->next = two;
//	two->next = three;
//	three->next = four;
//	four->next = five;
//	five->next = six;
//	one->randomNext = three;
//	two->randomNext = five;
//	three->randomNext = one;
//	four->randomNext = six;
//	five->randomNext = six;
//	six->randomNext = five;
//	Node *root = deepCopyWithHashing(one);
//	getchar();
//}
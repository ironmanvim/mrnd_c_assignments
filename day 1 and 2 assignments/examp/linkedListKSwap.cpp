//#include <stdio.h>
//#include <stdlib.h>
//struct Node {
//	int data;
//	struct Node *next;
//};
//typedef struct Node Node;
//Node *reverseLinkedList(Node *root) {
//	if (root != NULL) {
//		if (root->next == NULL) {
//			return root;
//		}
//		Node *newHead = reverseLinkedList(root->next);
//		Node *i;
//		for (i = root->next; i->next != NULL; i = i->next);
//		i->next = root;
//		root->next = NULL;
//		return newHead;
//	}
//	return NULL;
//}
//Node *linkedListSwapK(Node *root, int k) {
//	if (k <= 0) return root;
//	int len = 0;
//	int count = 1;
//	int iter_k = 0;
//	Node *temp = root;
//	Node *start = root;
//	Node *tail = start;
//	Node *head = NULL;
//	while(temp != NULL) {
//		if (count == k) {
//			Node *nextTemp = temp->next;
//			temp->next = NULL;
//			Node *newHead = reverseLinkedList(start);
//			if (head == NULL) {
//				root = newHead;
//			}
//			else {
//				tail->next = newHead;
//				tail = start;
//			}
//			head = newHead;
//			temp = nextTemp; 
//			start = temp;
//			count = 1;
//		}
//		else {
//			count++;
//			temp = temp->next;
//		}
//		len++;
//	}
//	if (len < k) return root;
//	if (count > 1) {
//		tail->next = start;
//	}
//	return root;
//}
//Node *createNode(int data) {
//	Node *newNode = (Node *)malloc(sizeof(Node));
//	newNode->data = data;
//	newNode->next = NULL;
//	return newNode;
//}
//Node *createLinkedListWithString(char *string) {
//	Node *root = NULL;
//	for (int i = 0; string[i] != '\0'; i++) {
//		if (root == NULL) {
//			root = createNode(string[i] - '0');
//		}
//		else {
//			Node *temp;
//			for (temp = root; temp->next != NULL; temp = temp->next);
//			temp->next = createNode(string[i] - '0');
//		}
//	}
//	return root;
//}
//void printLinkedList(Node *root) {
//	for (Node *i = root; i != NULL; i = i->next) {
//		printf("%d->", i->data);
//	}
//	printf("N");
//}
///*int main() {
//	for (int i = -3; i < 20; i++) {
//		Node *root = createLinkedListWithString("123456789012");
//		root = linkedListSwapK(root, i);
//		printLinkedList(root);
//		printf("\n");
//	}
//	getchar();
//}*/
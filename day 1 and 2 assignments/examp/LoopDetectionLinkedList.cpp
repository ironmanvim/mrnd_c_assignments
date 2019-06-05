//#include <stdio.h>
//#include <malloc.h>
//struct Node {
//	int data;
//	struct Node *next;
//};
//typedef struct Node Node;
//
//int detectLoop(Node *root) {
//	if (root == NULL) 
//		return 0;
//	Node *sp = root, *fp = root->next;
//	while (sp != fp && fp != NULL && fp->next != NULL) {
//		sp = sp->next;
//		fp = fp->next->next;
//	}
//	if (sp == fp) {
//		return 1;
//	}
//	return 0;
//}
//Node *createNode(int data) {
//	Node *newNode = (Node *)malloc(sizeof(Node));
//	newNode->data = data;
//	newNode->next = NULL;
//	return newNode;
//}
//Node *createLinkedListWithString(char *string) {
//	Node *root = NULL;
//	Node *temp = root;
//	for (int i = 0; string[i] != '\0'; i++) {
//		if (root == NULL) {
//			root = createNode(string[i] - '0');
//		}
//		else {
//			for (temp = root; temp->next != NULL; temp = temp->next);
//			temp->next = createNode(string[i] - '0');
//		}
//	}
//	return root;
//}
//Node *createLinkedListWithStringWithLoop(char *string, char loop) {
//	Node *root = NULL;
//	Node *temp = root;
//	for (int i = 0; string[i] != '\0'; i++) {
//		if (root == NULL) {
//			root = createNode(string[i] - '0');
//		}
//		else {
//			for (temp = root; temp->next != NULL; temp = temp->next);
//			temp->next = createNode(string[i] - '0');
//		}
//	}
//	temp = temp->next;
//	for (Node *i = root; i != NULL; i = i->next) {
//		if (i->data == loop - '0') {
//			temp->next = i;
//			break;
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
//int main() {
//	Node *root = createLinkedListWithStringWithLoop("1234567", '4');
//	int check = detectLoop(root);
//	printf("%d", check);
//	getchar();
//}
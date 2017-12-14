#include "list.h"

int GetHead(Node const *const node, Node **const pHead) {
	if (pHead == NULL || pHead == NULL)
		return ERR_NULLPTR;
	*pHead = NULL;
	Node *head;
	for (head = (Node*)node; head->prev != NULL; head = head->prev);
	*pHead = head;
	return SUCCESS;
}

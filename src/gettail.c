#include "list.h"

int GetTail(Node const *const node, Node **const pTail) {
	if (pTail == NULL || pTail == NULL)
		return ERR_NULLPTR;
	*pTail = NULL;
	Node *tail;
	for (tail = (Node*)node; tail->next != NULL; tail = tail->next);
	*pTail = tail;
	return SUCCESS;
}

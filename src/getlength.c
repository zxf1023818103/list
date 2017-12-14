#include "list.h"

int GetLengthBetween(Node const *const head, Node const *const tail, size_t *const pLength) {
	if (head == NULL || tail == NULL || pLength == NULL)
		return ERR_NULLPTR;
	*pLength = 0;
	size_t length = 1;
	for (Node *cur = (Node *)head; cur->next != NULL && cur != tail; cur = cur->next)
		length++;
	*pLength = length;
	return SUCCESS;
}

int GetLength(Node const *const node, size_t *const pLength) {
	if (node == NULL || pLength == NULL)
		return ERR_NULLPTR;
	*pLength = 0;
	size_t length = 1;
	Node *cur = (Node*)node;
	for (Node *cur = (Node*)node; cur->next != NULL && cur != node; cur = cur->next)
		length++;
	*pLength = length;
	return SUCCESS;
}

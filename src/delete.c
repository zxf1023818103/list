#include "list.h"
#include <stdlib.h>

int DeleteNode(Node * dest) {
	if (dest == NULL)
		return ERR_NULLPTR;
	if (dest->next == NULL) {
		dest->prev->next = NULL;
		free(dest);
	}
	else if (dest->prev == NULL) {
		dest->next->prev = NULL;
		free(dest);
	}
	else {
		dest->prev->next = dest->next;
		dest->next->prev = dest->prev;
		free(dest);
	}
	return SUCCESS;
}

int DeleteByIndex(Node* head, size_t index) {
	Node *dest;
	int ret;
	if (ret = AtNode(head, &dest, index) != SUCCESS)
		return ret;
	return DeleteNode(dest);
}

int DeleteBetween(Node *begin, Node *end) {
	if (begin == NULL || end == NULL)
		return ERR_NULLPTR;
	int ret;
	Node *cur = begin;
	while (cur->next != NULL) {
		cur = cur->next;
		if (ret = DeleteNode(cur))
			return ret;
	}
	if (ret = DeleteNode(cur))
		return ret;
	return SUCCESS;
}

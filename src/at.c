#include "list.h"

int AtNode(Node const *const head, Node **const pDest, size_t index) {
	if (head == NULL || pDest == NULL)
		return ERR_NULLPTR;
	*pDest = NULL;
	size_t i = 0;
	for (Node *cur = (Node*)head; cur != NULL; cur = cur->next) {
		if (i == index) {
			*pDest = cur;
			return SUCCESS;
		}
		i++;
	}
	return ERR_INDEX;
}

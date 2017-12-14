#include "list.h"
#include <stdlib.h>

int ReleaseList(Node *head) {
	if (head == NULL)		// FIXME: it doesn't work because the value isn't NULL.
		return ERR_NULLPTR;
	Node *cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
		free(cur->prev);
	}
	free(cur);
	return SUCCESS;
}

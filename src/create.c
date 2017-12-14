#include "list.h"
#include <stdlib.h>
#include <memory.h>

int CreateList(Node **const pHead, size_t length) {
	if (pHead == NULL)
		return ERR_NULLPTR;
	if (length == 0)
		return SUCCESS;
	*pHead = (Node*)malloc(sizeof(Node));
	memset((void*)*pHead, 0, sizeof(Node));
	Node *cur = *pHead;
	for (size_t i = 0; i < length - 1; i++) {
		cur->next = (Node*)malloc(sizeof(Node));
		memset((void*)cur->next, 0, sizeof(Node));
		cur->next->prev = cur;
		cur = cur->next;
	}
	return SUCCESS;
}

#include "list.h"

int ForeachBetween(Node *const begin, Node *const end, ForeachHandler handler, int *err, ForeachHandlerArgs *args) {
	if (begin == NULL || end == NULL || handler == NULL)
		return ERR_NULLPTR;
	*err = 0;
	int ret;
	for (Node *cur = begin; cur != end->next; cur = cur->next) {
		if (ret = handler(cur, args) != SUCCESS) {
			if (err != NULL)
				*err = ret;
			return ERR_FOREACH;
		}
	}
	return SUCCESS;
}

int ForeachBetweenR(Node *const begin, Node *const end, ForeachHandler handler, int *err, ForeachHandlerArgs *args) {
	if (begin == NULL || end == NULL || handler == NULL)
		return ERR_NULLPTR;
	*err = 0;
	int ret;
	for (Node *cur = end; cur != begin->prev; cur = cur->prev) {
		if (ret = handler(cur, args) != SUCCESS) {
			if (err != NULL)
				*err = ret;
			return ERR_FOREACH;
		}
	}
	return SUCCESS;
}

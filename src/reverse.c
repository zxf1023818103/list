#include "list.h"

int Reverse(Node *begin, Node *end) {
	if (begin == NULL || end == NULL)
		return ERR_NULLPTR;
	int ret;
	size_t length;
	if (ret = GetLengthBetween(begin, end, &length) != SUCCESS)
		return ret;
	Node *a, *b;
	for (size_t i = 0; i < length / 2; i++) {
		if (ret = AtNode(begin, &a, i) != SUCCESS)
			return ret;
		if (ret = AtNode(begin, &b, length - i - 1) != SUCCESS)
			return ret;
		if (ret = SwapNode(a, b) != SUCCESS)
			return ret;
	}
	return SUCCESS;
}

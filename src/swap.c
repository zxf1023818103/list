#include "list.h"

int SwapBetween(Node *a_begin, Node *a_end, Node *b_begin, Node *b_end) {
	if (a_begin == NULL || a_end == NULL || b_begin == NULL || b_end == NULL)
		return ERR_NULLPTR;
	Node *prev = a_begin->prev;
	Node *next = a_end->next;
	a_begin->prev = b_begin->prev;
	a_end->next = b_end->next;
	b_begin->prev = prev;
	b_end->next = next;
	return SUCCESS;
}

int SwapNode(Node *a, Node *b) {
	if (a == NULL || b == NULL)
		return ERR_NULLPTR;
	Node *prev = a->prev;
	Node *next = a->next;
	a->prev = b->prev;
	a->next = b->next;
	b->prev = prev;
	b->next = next;
	return SUCCESS;
}

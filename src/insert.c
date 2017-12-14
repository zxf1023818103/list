#include "list.h"
#include <stdlib.h>
#include <memory.h>

int Insert(Node const *const head, data_t data, size_t index) {
	if (head == NULL)
		return ERR_NULLPTR;
	size_t i = 0;
	Node *new_node;
	for (Node *cur = (Node*)head; cur != NULL; cur = cur->next) {
		if (i == index) {
			if (cur->prev == NULL) {
				new_node = cur->prev = (Node*)malloc(sizeof(Node));
				memset((void*)new_node, 0, sizeof(Node));
				new_node->next = cur;
			}
			else if (cur->next == NULL) {
				new_node = cur->next = (Node*)malloc(sizeof(Node));
				memset((void*)new_node, 0, sizeof(Node));
				new_node->prev = cur;
			}
			else {
				new_node = (Node*)malloc(sizeof(Node));
				memset((void*)new_node, 0, sizeof(Node));
				new_node->prev = cur->prev;
				new_node->next = cur;
				cur->prev->next = new_node;
				cur->prev = new_node;
			}
			new_node->data = data;
			return 0;
		}
		i++;
	}
	return ERR_INDEX;
}

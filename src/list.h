#ifndef LIST_H
#define LIST_H

#include <stdint.h>

#define SUCCESS       0
#define ERR_NULLPTR  -1
#define ERR_INDEX    -2
#define ERR_FOREACH  -3
#define ERR_NOTFOUND -4

#ifdef __cplusplus
extern "C" {
#endif

typedef int data_t;

typedef struct node {
	struct node *prev;
	data_t data;
	struct node *next;
} Node;

typedef void ForeachHandlerArgs;
typedef int(*ForeachHandler)(Node *const cur, ForeachHandlerArgs *args);

int CreateList(Node **const pHead, size_t length);
int ReleaseList(Node *head);
int AtNode(Node const *const head, Node **const pDest, size_t index);
int ForeachBetween(Node *const begin, Node *const end, ForeachHandler handler, int *err, ForeachHandlerArgs *args);
int ForeachBetweenR(Node *const begin, Node *const end, ForeachHandler handler, int *err, ForeachHandlerArgs *args);
int DeleteNode(Node * dest);
int DeleteByIndex(Node* head, size_t index);
int DeleteBetween(Node *begin, Node *end);
int SwapNode(Node *a, Node *b);
int SwapBetween(Node *a_begin, Node *a_end, Node *b_begin, Node *b_end);
int GetHead(Node const *const node, Node **const pHead);
int GetTail(Node const *const node, Node **const pTail);
int GetLength(Node const *const head, size_t *const pLength);
int GetLengthBetween(Node const *const head, Node const *const tail, size_t *const pLength);
int Insert(Node const *const head, data_t data, size_t index);
int Reverse(Node *begin, Node *end);
int Find(Node const *const head, const data_t *pData, Node **const pDest);
int FindBetween(Node const *const begin, Node const *const end, const data_t *pData, Node **const pDest);

#ifdef __cplusplus
}
#endif

#endif
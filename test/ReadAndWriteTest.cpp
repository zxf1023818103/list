#include <list.h>
#include <gtest/gtest.h>

int i;
const int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

typedef struct {
	int *array;
	size_t size;
} TestData;

int write_handler(Node *const cur, ForeachHandlerArgs *args) {
	TestData *data = (TestData*)args;
	cur->data = data->array[i++];
	return SUCCESS;
}

int read_handler(Node *const cur, ForeachHandlerArgs *args) {
	TestData *data = (TestData*)args;
	EXPECT_EQ(array[i++], cur->data);
	return SUCCESS;
}

TEST(ReadAndWriteTest, ForeachBetweenTest) {
	TestData data;
	data.array = (int*)array;
	data.size = sizeof array / sizeof(int);
	Node *node, *head, *tail;
	int err;
	i = 0;
	EXPECT_EQ(CreateList(&node, data.size), SUCCESS);
	EXPECT_EQ(GetHead(node, &head), SUCCESS);
	EXPECT_EQ(GetTail(node, &tail), SUCCESS);
	EXPECT_EQ(ForeachBetween(head, tail, write_handler, &err, (ForeachHandlerArgs*)&data), SUCCESS);
	EXPECT_EQ(i, sizeof array / sizeof(int));
	i = 0;
	EXPECT_EQ(ForeachBetween(head, tail, read_handler, &err, (ForeachHandlerArgs*)&data), SUCCESS);
	EXPECT_EQ(ReleaseList(head), SUCCESS);
}

TEST(ReadAndWriteTest, ForeachBetweenRTest) {
	TestData data;
	data.array = (int*)array;
	data.size = sizeof array / sizeof(int);
	Node *node, *head, *tail;
	int err;
	i = 0;
	EXPECT_EQ(CreateList(&node, data.size), SUCCESS);
	EXPECT_EQ(GetHead(node, &head), SUCCESS);
	EXPECT_EQ(GetTail(node, &tail), SUCCESS);
	EXPECT_EQ(ForeachBetweenR(head, tail, write_handler, &err, (ForeachHandlerArgs*)&data), SUCCESS);
	EXPECT_EQ(i, sizeof array / sizeof(int));
	i = 0;
	EXPECT_EQ(ForeachBetweenR(head, tail, read_handler, &err, (ForeachHandlerArgs*)&data), SUCCESS);
	EXPECT_EQ(ReleaseList(head), SUCCESS);
}

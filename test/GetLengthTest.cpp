#include <list.h>
#include <gtest/gtest.h>

TEST(GetLengthTest, BasicTest) {
	Node *head, *tail;
	CreateList(&head, 5);
	GetTail(head, &tail);
	size_t len;
	EXPECT_EQ(GetLengthBetween(head, tail, &len), SUCCESS);
	EXPECT_EQ(len, 5);
	ReleaseList(head);
}

TEST(GetLengthTest, GetLoopTest) {
	Node *head, *tail;
	
}
#include <list.h>
#include <gtest/gtest.h>

TEST(CreateAndReleaseTest, Create5Nodes) {
	Node *head;
	EXPECT_EQ(CreateList(&head, 5), SUCCESS);
	EXPECT_EQ(ReleaseList(head), SUCCESS);
}

TEST(CreateAndReleaseTest, Create1Node) {
	Node *head;
	EXPECT_EQ(CreateList(&head, 1), SUCCESS);
	EXPECT_EQ(ReleaseList(head), SUCCESS);
}

TEST(CreateAndReleaseTest, Create0Node) {
	Node *head;
	EXPECT_EQ(CreateList(&head, 0), SUCCESS);
	EXPECT_EQ(ReleaseList(head), SUCCESS);
}

TEST(CreateAndReleaseTest, HandleNullPointer) {
	EXPECT_EQ(CreateList(NULL, 0), ERR_NULLPTR);
	EXPECT_EQ(ReleaseList(NULL), ERR_NULLPTR);
}

# 链表（一）：概念、创建与释放链表

链表作为一种基本的数据结构，广泛运用在程序设计中。相比于数组而言，链表在遍历访问及增删数据方面性能开销极低。因此链表经常作为插入排序等算法的基础实现部分。本文拟向读者简要介绍链表的概念、原理、实现及链表的常用操作的实现。

### 概述
链表，顾名思义，是一种链状的数据结构。链表由多个单元组成，每个单元被称为链表的一个节点。链表分为**前向链表**（forward list）和**双向链表**（list）。对于前向链表而言，每个节点包含了两部分信息：下一个节点的位置信息和用户存储的数据。对于双向链表而言，每个节点还包含了上一个节点的位置信息。各个节点通过包含的信息，共同连接成为一个有序的整体。

### 链表节点 = 结构体 + 指针
在C语言中，我们使用结构体与指针组合的方式定义链表节点。下面的代码定义了一个典型的双向链表节点类型。
```c
struct list_node {
    struct node *previous;
    void *data;
    struct node *next;
};
```
其中，`previous`和`next`分别是指向上一个节点和下一个节点的指针。`data`是一个`void`类型的指针，该指针指向用户数据，例如整数、一本书的信息或一名学生的成绩。以此类推，前向链表节点类型声明如下，仅比双向链表节点少一个指向上一节点的指针`previous`：
```c
struct forward_list_node {
    void *data;
    struct forward_list_node *next;
};
```
我们可以使用以下代码创建一个节点：
```c
struct list_node node;
```
但是在大多数情况下，为了简便，我们经常会使用`typedef`给节点类型取一个别名。以下代码为`struct list_node`类型创建了别名`Node`：
```c
typedef struct list_node Node;
```
这样我们就可以用以下代码创建一个节点：
```c
Node node;
```
为了更加简便，节点类型的定义可以和`typedef`连着写，这也是代码中的一般写法：
```c
typedef struct list_node {
    struct node *previous;
    void *data;
    struct node *next;
} Node;
```

### 链表的创建
简单地来说，创建一个链表有两个步骤：
 1. 创建节点
 2. 把节点连起来

由于存储数目的不确定性，我们无法通过声明数组或变量的方式创建链表节点。因此我们需要使用动态内存分配函数在运行时创建相应数目的节点。最常用的是`malloc`函数。但是，我在这里推荐使用`calloc`函数来分配内存。原因是`calloc`在分配内存的同时会把分配的内存清零。这样就可以省去将头节点的`head`指针和尾节点的`next`指针手动设为`NULL`的操作。还可以避免因忘记清零造成的指针越界访问的错误。

首先创建链表的第一个节点：
```c
Node *head = (Node*)calloc(1, sizeof(Node));
```
声明一个`Node`类型的指针`current`，用于存储当前所在节点：
```c
Node *current = head;
```
然后，利用`current`指针创建链表的下一个节点：
```c
current->next = (Node*)calloc(1, sizeof(Node));
```
此处对`calloc`的返回值使用了强制类型转换，将其从`void *`转换成了`Node *`类型。这是因为在C++编译器中，不存在从`void *`到任意一重指针类型的隐式类型转换，从而因为类型不匹配引发编译错误。这一点和C语言不同。

别忘记将新节点的`previous`指针指向当前所在节点，否则就找不到回来的路了（笑）：
```c
current->next->previous = current;
```
最后，将`current`移向新创建的节点：
```c
current = current->next;
```
借助指向当前节点的指针变量`current`，我们可以很方便地用循环实现创建链表。现在将单过程的代码塞进循环里。
```c
size_t length = 10;  // 要创建的链表长度
Node *head = calloc(1, sizeof(Node));
Node *current = head;
for (size_t i = 0; i < length; i++) {
    current->next = (Node*)calloc(1, sizeof(Node));
    current->next->previous = current;
    current = current->next;
}
```
运行上面的这段代码，我们便得到了一串长度为10的链表。

链表创建好了，现在我们可以向里面存点东西了。

### 遍历链表
在创建链表时我们使用了`current`指针来记录当前节点。同样的，在遍历链表的时候，我们同样使用`current`指针来帮助我们把过程写进循环里。下面我们以将10个整数放进链表为例，讲述如何遍历访问链表节点。为了简便，`current`被缩略为`cur`；判断终止和移向下一节点的操作被被放入`for`循环的括号内；数组下标`i`的自增和`data`指针赋值操作被放在同一行代码中。
```c
int array[10] = { 1,2,3,4,5,6,7,8,9,10 };
int i = 0;  // 当前数组的下标
for (Node *cur = head; cur != NULL; cur = cur->next)
    cur->data = (void*)&array[i++];
```
这样代码看起来就比较清爽了。由于`data`成员被定义为`void *`类型，而要存放的整数的指针是`int *`类型，我们需要使用强制类型转换将其强制转换为`void *`类型。如果对指针很懵逼或嫌指针操作麻烦的话，我们也可以在定义时将`data`成员的类型修改为`int`，这样我们就可以直接使用`cur->data = array[i++]`这样的语句来赋值。

同样，如果我们想要逆序遍历链表节点，我们只需要倒着写就OK了。
```c
for (Node *cur = tail; cur != NULL; cur = cur->prev) {
    // 要进行的操作
}
```

### 释放链表
链表使用完毕后，需要释放掉，否则会造成内存泄漏。要想释放链表，我们需要一个一个释放掉其节点。在这里，我们需要一些技巧。牢记要点：**过河拆桥**。

首先，依然需要创建一个`cur`指针来帮助我们完成操作。让`cur`指向头节点`head`。
```c
Node *cur = head;
```
然后，先将`cur`移至下一个节点，此为**过河**。对于当前要删除的节点来说，`cur`是它的下一个节点。**记得判断下一个节点是否为空**。
```c
if (cur->next != NULL)
    cur = cur->next;
```
然后，删除`cur`的上一个节点，也就是当前节点，此为**拆桥**。
```c
free(cur->previous);
```
然后我们把上面的代码放进循环：
```c
while (cur->next != NULL) {
	cur = cur->next;
	free(cur->previous);
}
```
当循环执行完毕后，还有最后一个节点没有被释放。此时`cur`指向最后一个节点。最后我们手动释放最后一个节点：
```c
free(cur);
```

### 小结
最后，我们将创建和释放链表的操作包装成函数。为了清晰易懂，我们规范一下返回值的含义：

|宏定义|值|含义|
|-----|---|---|
|SUCCESS|0|操作成功|
|ERR_NULLPTR|-1|传入指针为空|
|ERR_ALLOC|-2|内存分配失败|

首先是创建链表的部分：
```c
#define SUCCESS 0
#define ERR_NULLPTR -1
#define ERR_ALLOC -2

int CreateList(Node **pHead, size_t length) {
    if (pHead == NULL)
        return ERR_NULLPTR;
    if (length == 0)
        return SUCCESS;
    *pHead = (Node*)calloc(1, sizeof(Node));
    if (*pHead == NULL)
        return ERR_ALLOC;
    Node *cur = *pHead;
    for (size_t i = 0; i < length - 1; i++) {
        cur->next = (Node*)calloc(1, sizeof(Node));
        if (cur->next == NULL)
            return ERR_ALLOC;
        cur->next->previous = cur;
        cur = cur->next;
    }
    return SUCCESS;
}
```
这里的`pHead`参数是指向链表头节点指针的指针，即指向`head`的指针。使用方法如下：
```c
// 创建一条有5个节点的链表
Node *head;
int ret;    // 记录函数的返回值
ret = CreateList(&head, 5);
// 错误处理略去
```

然后是释放链表的部分：
```c
int ReleaseList(Node *head) {
    if (head == NULL)
    return ERR_NULLPTR;
    Node *cur = head;
    while (cur->next != NULL) {
        cur = cur->next;
        free(cur->prev);
    }
    free(cur);
    return SUCCESS;
}
```
使用时传`head`给函数就行了，略去不表。

在VS 2017上进行测试时发现，在`ReleaseList`中即使判断了`head`是否为空，如果给函数传`NULL`指针，程序依然会崩溃。报错时`cur`指针的值为`0xCCCCCCCC`，这是Debug模式下编译器自动给未初始化内存填充的值。在Release模式下`cur`值为`0xFFFFFFEF`。而在Linux下使用GCC编译测试则无此问题。由于时间限制，未在Windows下的GCC编译器进行测试，读者们不妨自己用Dev-C++试一下。
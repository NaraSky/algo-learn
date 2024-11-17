#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义链表节点结构体
typedef struct Node {
    int data;   // 节点数据
    Node *next; // 指向下一个节点的指针
} Node;

// 定义链表结构体
typedef struct LinkList {
    Node head;  // 哨兵节点，便于操作链表
    Node *tail; // 指向链表尾部节点的指针
} LinkList;

// 创建新节点
Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node)); // 分配内存
    p->data = val;                          // 设置节点数据
    p->next = NULL;                         // 初始化节点的 next 指针
    return p;
}

// 初始化链表
LinkList *initLinkList() {
    LinkList *l = (LinkList *)malloc(sizeof(LinkList)); // 分配内存
    l->head.next = NULL;  // 哨兵节点的 next 指针设为 NULL
    l->tail = &(l->head); // 初始时尾部指针指向哨兵节点
    return l;
}

// 清空链表
void clearLinkList(LinkList *l) {
    Node *p = l->head.next, *q; // 从哨兵节点的 next 指针开始遍历
    while (p) {                 // 遍历链表并释放节点内存
        q = p->next;
        free(p);
        p = q;
    }
    free(l); // 释放链表结构体的内存
    return;
}

// 定义队列结构体
typedef struct Queue {
    LinkList *l; // 使用链表作为底层数据结构
    int count;   // 队列中的元素数量
} Queue;

// 初始化队列
Queue *initQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue)); // 分配内存
    q->l = initLinkList();                     // 初始化链表
    q->count = 0;                              // 初始化元素数量为 0
    return q;
}

// 检查链表是否为空
int emptyList(LinkList *l) {
    return l->head.next == NULL; // 哨兵节点的 next 指针是否为 NULL
}

// 获取链表头部元素
int frontList(LinkList *l) {
    if (emptyList(l))
        return 0;              // 如果链表为空，返回 0
    return l->head.next->data; // 返回头部节点数据
}

// 在链表尾部插入元素
int insertTail(LinkList *l, int val) {
    Node *node = getNewNode(val); // 创建新节点
    l->tail->next = node;         // 将当前尾节点的 next 指针指向新节点
    l->tail = node;               // 更新尾部指针
    return 1;                     // 插入成功返回 1
}

// 删除链表头部元素
int eraseHead(LinkList *l) {
    if (emptyList(l))
        return 0;                      // 如果链表为空，返回 0
    Node *p = l->head.next;            // 临时保存头部节点
    l->head.next = l->head.next->next; // 哨兵节点的 next 指针指向下一个节点
    if (p == l->tail)                  // 如果链表中只有一个节点，更新尾部指针
        l->tail = &(l->head);
    free(p);  // 释放原头部节点内存
    return 1; // 删除成功返回 1
}

// 检查队列是否为空
int empty(Queue *q) {
    return q->count == 0; // 队列中的元素数量是否为 0
}

// 获取队列头部元素
int front(Queue *q) {
    if (empty(q))
        return 0;           // 如果队列为空，返回 0
    return frontList(q->l); // 调用链表的 frontList 方法
}

// 向队列尾部添加元素
int push(Queue *q, int val) {
    insertTail(q->l, val); // 调用链表的 insertTail 方法
    q->count += 1;         // 更新队列中的元素数量
    return 1;              // 插入成功返回 1
}

// 从队列头部移除元素
int pop(Queue *q) {
    eraseHead(q->l); // 调用链表的 eraseHead 方法
    q->count -= 1;   // 更新队列中的元素数量
    return 1;        // 删除成功返回 1
}

// 清空队列
void clearQueue(Queue *q) {
    if (q == NULL)
        return;          // 如果队列为空，直接返回
    clearLinkList(q->l); // 清空链表
    free(q);             // 释放队列结构体的内存
    return;
}

// 输出队列内容
void outputQueue(Queue *q) {
    printf("Queue : ");
    Node *p = q->l->head.next; // 从链表头部开始遍历
    for (int i = 0; i < q->count; i++, p = p->next) {
        printf("%4d", p->data); // 输出每个节点的数据
    }
    printf("\n\n");
    return;
}

// 主函数
int main() {
    srand(time(0));         // 初始化随机数种子
#define MAX_OP 10           // 最大操作次数
    Queue *q = initQueue(); // 初始化队列
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 5;    // 随机选择操作类型（0,1: pop; 2,3,4: push）
        int val = rand() % 100; // 随机生成一个值
        switch (op) {
        case 0:
        case 1:
            if (!empty(q)) { // 如果队列不为空，执行 pop 操作
                printf("front of queue : %d\n", front(q));
                pop(q);
            }
            break;
        case 2:
        case 3:
        case 4:
            printf("push %d to queue\n", val); // 执行 push 操作
            push(q, val);
            break;
        }
        outputQueue(q); // 输出队列当前状态
    }
    clearQueue(q); // 清空队列，释放内存
    return 0;
}

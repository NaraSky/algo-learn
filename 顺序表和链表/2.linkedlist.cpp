#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义链表节点结构
typedef struct Node {
    int data;          // 节点数据
    struct Node *next; // 指向下一个节点的指针
} Node;

// 创建新节点
Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node)); // 分配内存
    p->data = val;                          // 设置节点数据
    p->next = NULL;                         // 初始化下一节点为空
    return p;                               // 返回新节点
}

// 在指定位置插入新节点
Node *insert(Node *head, int pos, int val) {
    Node dummy, *p = &dummy;        // 创建虚拟头节点
    dummy.next = head;              // 将虚拟头节点指向链表的头节点
    Node *node = getNewNode(val);   // 创建新节点
    for (int i = 0; i < pos; i++) { // 找到插入位置
        if (p->next == NULL)
            break; // 防止位置越界
        p = p->next;
    }
    node->next = p->next; // 插入新节点 node指向p的指向
    p->next = node;       // p的指向指向node
    return dummy.next;    // 返回新的头节点（处理头插的情况）
}

// 清空链表
void clear(Node *head) {
    Node *p = head;
    while (p != NULL) {
        Node *next = p->next; // 保存下一节点指针
        free(p);              // 释放当前节点内存
        p = next;             // 移动到下一节点
    }
}

// 输出链表
void output_linklist(Node *head) {
    Node *p = head;
    printf("Index: ");
    int index = 0;
    for (p = head; p != NULL; p = p->next) {
        printf("%4d ", index++); // 输出索引
    }
    printf("\nData:  ");
    for (p = head; p != NULL; p = p->next) {
        printf("%4d ", p->data); // 输出数据
    }
    printf("\n\n");
}

// 查找链表中的指定值
int find(Node *head, int val) {
    Node *p = head;
    int index = 0;
    while (p != NULL) {
        if (p->data == val) { // 找到目标值
            printf("Value %d found at index %d\n", val, index);
            return 1;
        }
        index++;
        p = p->next;
    }
    printf("Value %d not found\n", val); // 未找到
    return 0;
}

// 主函数
int main() {
    srand(time(0));
    const int MAX_OP = 7; // 最大操作次数
    Node *head = NULL;    // 初始化链表为空
    for (int i = 0; i < MAX_OP; i++) {
        int pos = rand() % (i + 1); // 随机生成插入位置
        int val = rand() % 100;     // 随机生成值
        printf("Insert %d at position %d\n", val, pos);
        head = insert(head, pos, val); // 插入新节点
        output_linklist(head);         // 输出当前链表状态
    }
    int val;
    printf("Enter values to search (Ctrl+D to exit):\n");
    while (scanf("%d", &val) != EOF) { // 循环查找用户输入的值
        find(head, val);
    }
    clear(head); // 清空链表
    return 0;
}

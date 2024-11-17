#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define swap(a, b)                                                             \
    {                                                                          \
        __typeof(a) __c = a;                                                   \
        a = b, b = __c;                                                        \
    }

// 定义链表节点结构体
typedef struct Node {
    char *s;           // 存储字符串的指针
    struct Node *next; // 指向下一个节点的指针
} Node;

// 定义哈希表结构体
typedef struct HashTable {
    Node *data; // 存储链表头指针的数组
    int cnt;    // 当前哈希表中存储的元素数量
    int size;   // 哈希表的大小（桶的数量）
} HashTable;

// 函数声明
void expand(HashTable *h);         // 扩展哈希表
void clearHashTable(HashTable *h); // 清理哈希表的内存

// 创建一个新节点
Node *getNewNode(const char *s) {
    Node *p = (Node *)malloc(sizeof(Node)); // 为节点分配内存
    p->s = strdup(s);                       // 复制字符串并赋值给节点的 s 字段
    p->next = NULL;                         // 初始化 next 指针为空
    return p;
}

// 创建一个新的哈希表，初始大小为 n
HashTable *getNewHashTable(int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable)); // 为哈希表分配内存
    h->data = (Node *)malloc(sizeof(Node) * n); // 为哈希表的桶数组分配内存
    for (int i = 0; i < n; i++) {
        h->data[i].next = NULL; // 初始化每个桶的 next 指针为空
    }
    h->size = n; // 设置哈希表的大小
    h->cnt = 0;  // 初始时哈希表的元素数量为 0
    return h;
}

// 哈希函数，计算字符串的哈希值
int hash_func(const char *s) {
    int seed = 131, h = 0; // 初始化哈希值和种子
    for (int i = 0; s[i]; i++) {
        h = h * seed + s[i]; // 对每个字符进行哈希操作
    }
    return h & 0x7fffffff; // 保证哈希值为正整数
}

// 查找哈希表中是否存在指定的字符串
bool find(HashTable *h, const char *s) {
    int hcode = hash_func(s), ind = hcode % h->size; // 计算哈希值并定位到桶
    Node *p = h->data[ind].next;                     // 获取桶头的链表
    while (p) {
        if (strcmp(p->s, s) == 0) // 如果找到了目标字符串
            return true;
        p = p->next; // 否则继续查找下一个节点
    }
    return false; // 如果没有找到，返回 false
}

// 插入一个新的字符串到哈希表中
bool insert(HashTable *h, const char *s) {
    if (h->cnt >= h->size * 2) { // 如果哈希表元素数量超出容量的一半，扩展哈希表
        expand(h);
    }
    int hcode = hash_func(s), ind = hcode % h->size; // 计算哈希值并定位到桶
    Node *p = getNewNode(s);                         // 创建新节点
    p->next = h->data[ind].next;                     // 将新节点插入到链表头
    h->data[ind].next = p;                           // 更新桶的链表头
    h->cnt += 1;                                     // 增加元素数量
    return true;
}

// 交换两个哈希表的内容
void swapHashTable(HashTable *h1, HashTable *h2) {
    swap(h1->data, h2->data); // 交换哈希表的桶数组
    swap(h1->cnt, h2->cnt);   // 交换元素数量
    swap(h1->size, h2->size); // 交换哈希表大小
    return;
}

// 扩展哈希表，增加桶的数量
void expand(HashTable *h) {
    printf("expand Hash Table %d -> %d\n", h->size,
           h->size * 2); // 打印扩展信息
    HashTable *new_h =
        getNewHashTable(h->size * 2); // 创建一个新的哈希表，大小为原来的两倍
    for (int i = 0; i < h->size; i++) {
        Node *p = h->data[i].next; // 遍历原哈希表中的每个链表
        while (p) {
            insert(new_h, p->s); // 将每个元素插入到新哈希表中
            p = p->next;         // 移动到下一个节点
        }
    }
    swapHashTable(h, new_h); // 交换原哈希表和新哈希表
    clearHashTable(new_h);   // 清理新哈希表的内存
    return;
}

// 释放节点内存
void clearNode(Node *p) {
    if (p == NULL)
        return; // 如果节点为空，则返回
    if (p->s)
        free(p->s); // 释放节点中的字符串内存
    free(p);        // 释放节点本身的内存
    return;
}

// 清理哈希表的内存
void clearHashTable(HashTable *h) {
    if (h == NULL)
        return; // 如果哈希表为空，则返回
    for (int i = 0; i < h->size; i++) {
        Node *p = h->data[i].next, *q;
        while (p) {
            q = p->next;
            clearNode(p); // 释放每个节点的内存
            p = q;        // 继续处理下一个节点
        }
    }
    free(h->data); // 释放哈希表的桶数组内存
    free(h);       // 释放哈希表的内存
    return;
}

// 输出哈希表的内容
void output(HashTable *h) {
    printf("\n\nHash Table(%d / %d) : \n", h->cnt,
           h->size); // 输出当前哈希表的元素数量和大小
    for (int i = 0; i < h->size; i++) {
        printf("%d : ", i);        // 输出桶的索引
        Node *p = h->data[i].next; // 获取桶头的链表
        while (p) {
            printf("%s -> ", p->s); // 输出链表中的元素
            p = p->next;            // 继续处理下一个节点
        }
        printf("\n"); // 换行
    }
    return;
}

int main() {
    srand(time(0));                        // 设置随机种子
    char s[100];                           // 存储输入的字符串
#define MAX_N 2                            // 设置哈希表的初始大小为 2
    HashTable *h = getNewHashTable(MAX_N); // 创建一个新的哈希表

    // 从标准输入读取字符串并插入哈希表，直到遇到 "end" 为止
    while (~scanf("%s", s)) {
        if (strcmp(s, "end") == 0)
            break;    // 如果输入 "end"，则退出循环
        insert(h, s); // 插入字符串到哈希表
    }
    output(h); // 输出哈希表的内容

    // 查找哈希表中指定的字符串，并输出结果
    while (~scanf("%s", s)) {
        printf("find(%s) = %d\n", s,
               find(h, s)); // 输出查找结果（1 表示找到，0 表示未找到）
    }

#undef MAX_N  // 取消宏定义 MAX_N
    return 0; // 程序结束
}

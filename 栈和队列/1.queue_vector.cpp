#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义动态数组结构体
typedef struct vector {
    int *data; // 存储数组数据的指针
    int size;  // 数组的大小
} vector;

// 初始化一个动态数组
vector *initVector(int n) {
    vector *v = (vector *)malloc(sizeof(vector)); // 分配内存给动态数组结构体
    v->size = n;                                  // 设置数组大小
    v->data = (int *)malloc(sizeof(int) * n);     // 分配内存给数组数据
    return v;                                     // 返回动态数组指针
}

// 获取数组中指定位置的元素
int vectorSeek(vector *v, int pos) {
    if (pos < 0 || pos >= v->size)
        return -1;       // 检查访问是否越界
    return v->data[pos]; // 返回指定位置的元素
}

// 在指定位置插入元素
int insertVector(vector *v, int pos, int val) {
    if (pos < 0 || pos >= v->size)
        return 0;       // 检查位置是否有效
    v->data[pos] = val; // 在指定位置插入值
    return 1;           // 插入成功返回 1
}

// 清空动态数组
void clearVector(vector *v) {
    if (v == NULL)
        return;    // 如果数组为空，直接返回
    free(v->data); // 释放数组数据的内存
    free(v);       // 释放数组结构体的内存
    return;
}

// 定义队列结构体
typedef struct Queue {
    vector *data; // 使用动态数组存储队列数据
    int size;     // 队列容量
    int head;     // 队列头部索引
    int tail;     // 队列尾部索引
    int count;    // 队列中的元素数量
} Queue;

// 初始化队列
Queue *initQueue(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue)); // 分配内存给队列结构体
    q->data = initVector(n);                   // 初始化动态数组用于存储数据
    q->size = n;                               // 设置队列容量
    q->head = q->tail = q->count = 0;          // 初始化队列的头尾索引和元素计数
    return q;                                  // 返回队列指针
}

// 检查队列是否为空
int empty(Queue *q) {
    return q->count == 0; // 如果元素数量为 0，则队列为空
}

// 获取队列头部元素
int front(Queue *q) {
    return vectorSeek(q->data, q->head); // 通过动态数组的头部索引获取元素
}

// 向队列尾部添加元素
int push(Queue *q, int val) {
    if (q->count == q->size)
        return 0;                        // 如果队列已满，返回 0
    insertVector(q->data, q->tail, val); // 在尾部索引位置插入元素
    q->tail += 1;                        // 尾部索引后移
    if (q->tail == q->size)
        q->tail = 0; // 如果尾部索引越界，回到数组开头
    q->count += 1;   // 增加队列元素数量
    return 1;        // 插入成功返回 1
}

// 从队列头部移除元素
int pop(Queue *q) {
    if (empty(q))
        return 0; // 如果队列为空，返回 0
    q->head += 1; // 头部索引后移
    if (q->head == q->size)
        q->head = 0; // 如果头部索引越界，回到数组开头
    q->count -= 1;   // 减少队列元素数量
    return 1;        // 移除成功返回 1
}

// 清空队列
void clearQueue(Queue *q) {
    if (q == NULL)
        return;           // 如果队列为空，直接返回
    clearVector(q->data); // 清空动态数组
    free(q);              // 释放队列结构体的内存
    return;
}

// 输出队列内容
void outputQueue(Queue *q) {
    printf("Queue : ");
    for (int i = 0; i < q->count; i++) {
        // 输出从头部索引开始的每个元素
        printf("%4d", vectorSeek(q->data, (q->head + i) % q->size));
    }
    printf("\n\n");
    return;
}

// 主函数
int main() {
    srand(time(0));          // 初始化随机数种子
#define MAX_OP 10            // 最大操作次数
    Queue *q = initQueue(5); // 初始化队列，容量为 5
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 5;    // 随机选择操作类型（0,1: pop; 2,3,4: push）
        int val = rand() % 100; // 随机生成一个值
        switch (op) {
        case 0:
        case 1:
            if (!empty(q)) { // 如果队列不为空，执行 pop 操作
                printf("front of queue : %d\n", front(q)); // 输出队列头部元素
                pop(q);                                    // 移除队列头部元素
            }
            break;
        case 2:
        case 3:
        case 4:
            printf("push %d to queue\n", val); // 执行 push 操作
            push(q, val);
            break;
        }
        outputQueue(q); // 输出当前队列状态
    }
    clearQueue(q); // 清空队列，释放内存
    return 0;
}

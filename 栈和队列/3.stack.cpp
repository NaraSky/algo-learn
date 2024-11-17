#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义栈的结构体
typedef struct Stack {
    int *data; // 用数组模拟栈的存储
    int size;  // 栈的容量
    int top;   // 栈顶索引
} Stack;

// 初始化栈
Stack *initStack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack)); // 分配栈结构体的内存
    s->data = (int *)malloc(sizeof(int) * n);  // 分配存储栈元素的数组
    s->size = n;                               // 设置栈的容量
    s->top = -1;                               // 初始化栈为空，top 指向 -1
    return s;
}

// 检查栈是否为空
int empty(Stack *s) {
    return s->top == -1; // top 为 -1 时，栈为空
}

// 获取栈顶元素
int top(Stack *s) {
    if (empty(s))
        return 0;           // 如果栈为空，返回 0
    return s->data[s->top]; // 返回栈顶元素
}

// 向栈中压入元素
int push(Stack *s, int val) {
    if (s->top + 1 == s->size)
        return 0;          // 如果栈满，返回 0 表示失败
    s->top += 1;           // 栈顶指针加 1
    s->data[s->top] = val; // 将元素存入栈顶位置
    return 1;              // 返回 1 表示成功
}

// 从栈中弹出元素
int pop(Stack *s) {
    if (empty(s))
        return 0; // 如果栈为空，返回 0 表示失败
    s->top -= 1;  // 栈顶指针减 1
    return 1;     // 返回 1 表示成功
}

// 清空栈并释放内存
void clearStack(Stack *s) {
    if (s == NULL)
        return;    // 如果栈为 NULL，直接返回
    free(s->data); // 释放栈元素存储数组的内存
    free(s);       // 释放栈结构体的内存
    return;
}

// 输出栈的内容
void outputStack(Stack *s) {
    printf("Stack : ");                 // 打印栈的内容
    for (int i = s->top; i >= 0; --i) { // 从栈顶到栈底依次输出元素
        printf("%4d", s->data[i]);
    }
    printf("\n\n");
    return;
}

// 主函数
int main() {
    srand(time(0));          // 初始化随机数种子
#define MAX_OP 10            // 最大操作次数
    Stack *s = initStack(5); // 初始化栈，容量为 5

    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 3;    // 随机生成操作类型 (0: pop; 1,2: push)
        int val = rand() % 100; // 随机生成一个值

        switch (op) {
        case 0:
            if (!empty(s)) { // 如果栈不为空，执行 pop 操作
                printf("pop stack, item = %d\n", top(s));
                pop(s);
            } else {
                printf("pop stack failed, stack is empty\n");
            }
            break;
        case 1:
        case 2:
            if (push(s, val)) { // 尝试向栈中压入元素
                printf("push stack, item = %d\n", val);
            } else {
                printf("push stack failed, stack is full\n");
            }
            break;
        }
        outputStack(s); // 输出当前栈的内容
    }

    clearStack(s); // 清空栈并释放内存
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000000 // 假设最大栈容量

struct Stack {
    unsigned long long
        *data; // 栈存储的数据，使用 unsigned long long 以支持 x < 2^64
    int size;  // 栈的容量
    int top;   // 栈顶索引
};

struct Stack *createStack(int size) {
    struct Stack *s = (struct Stack *)malloc(sizeof(struct Stack));
    s->size = size;
    s->top = 0;
    s->data = (unsigned long long *)malloc(size * sizeof(unsigned long long));
    return s;
}

void freeStack(struct Stack *s) {
    free(s->data);
    free(s);
}

void push(struct Stack *s, unsigned long long x) {
    if (s->top < s->size) {
        s->data[s->top++] = x;
    }
}

void pop(struct Stack *s) {
    if (s->top == 0) {
        printf("Empty\n");
    } else {
        s->top--;
    }
}

void query(struct Stack *s) {
    if (s->top == 0) {
        printf("Anguei!\n");
    } else {
        printf("%llu\n", s->data[s->top - 1]);
    }
}

int size(struct Stack *s) { return s->top; }

int main() {
    int T; // 数据组数
    scanf("%d", &T);

    while (T--) {
        int n; // 操作次数
        scanf("%d", &n);

        struct Stack *s = createStack(MAX_SIZE);
        char command[10];
        unsigned long long x;

        for (int i = 0; i < n; ++i) {
            scanf("%s", command); // 读取命令
            if (strcmp(command, "push") == 0) {
                scanf("%llu", &x); // 读取要压入的数
                push(s, x);
            } else if (strcmp(command, "pop") == 0) {
                pop(s);
            } else if (strcmp(command, "query") == 0) {
                query(s);
            } else if (strcmp(command, "size") == 0) {
                printf("%d\n", size(s)); // 输出当前栈的大小
            }
        }

        freeStack(s); // 释放栈的内存
    }

    return 0;
}

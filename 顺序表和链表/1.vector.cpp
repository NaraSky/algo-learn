#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义一个动态数组结构 vector
typedef struct vector {
    int size, count; // size 是数组容量，count 是当前存储的元素个数
    int *data;       // 指向数组存储数据的指针
} vector;

// 创建一个新的 vector
vector *getNewVector(int n) {
    vector *p = (vector *)malloc(sizeof(vector)); // 分配内存给 vector 结构体
    p->size = n;                                  // 初始化数组容量为 n
    p->count = 0;                                 // 初始化当前存储元素个数为 0
    p->data = (int *)malloc(sizeof(int) * n); // 为数据部分分配 n 个整数的内存
    return p;                                 // 返回新创建的 vector 指针
}

// 动态扩展 vector 的容量
int expand(vector *v) {
    if (v == NULL)
        return 0; // 如果 vector 指针为 NULL，扩展失败
    printf("expand v from %d to %d\n", v->size, 2 * v->size);

    // 使用 realloc 扩展数组的内存
    // 如果分配成功，原数据会被自动复制到新地址。
    // 如果分配失败，原内存不会改变，需要检查返回值是否为 NULL
    int *p = (int *)realloc(v->data, sizeof(int) * 2 * v->size);
    if (p == NULL) // 如果内存分配失败
        return 0;  // 扩展失败
    v->data = p;   // 更新数据指针为新的内存位置
    v->size *= 2;  // 更新容量为原来的两倍
    return 1;      // 扩展成功
}

// 在 vector 的指定位置插入一个值
int insert(vector *v, int pos, int val) {
    if (pos < 0 || pos > v->count)
        return 0; // 如果插入位置无效，插入失败
    if (v->size == v->count && !expand(v))
        return 0; // 如果容量不足且扩展失败，插入失败

    // 将插入位置后的元素向后移动
    for (int i = v->count - 1; i >= pos; i--) {
        v->data[i + 1] = v->data[i];
    }
    v->data[pos] = val; // 在指定位置插入值
    v->count += 1;      // 更新当前元素个数
    return 1;           // 插入成功
}

// 从 vector 中移除指定位置的值
int erase(vector *v, int pos) {
    if (pos < 0 || pos >= v->count)
        return 0; // 如果删除位置无效，删除失败

    // 将删除位置后的元素向前移动
    for (int i = pos + 1; i < v->count; i++) {
        v->data[i - 1] = v->data[i];
    }
    v->count -= 1; // 更新当前元素个数
    return 1;      // 删除成功
}

// 输出 vector 的内容
void output_vector(vector *v) {
    int len = 0;
    for (int i = 0; i < v->size; i++) {
        len += printf("%3d", i); // 输出数组的索引
    }
    printf("\n");
    for (int i = 0; i < len; i++)
        printf("-"); // 绘制分割线
    printf("\n");
    for (int i = 0; i < v->count; i++) {
        printf("%3d", v->data[i]); // 输出存储的元素
    }
    printf("\n\n");
}

// 释放 vector 所占的内存
void clear(vector *v) {
    if (v == NULL)
        return;    // 如果指针为 NULL，直接返回
    free(v->data); // 释放数据部分的内存
    free(v);       // 释放 vector 结构体的内存
}

int main() {
    srand(time(0));              // 初始化随机数种子
#define MAX_OP 20                // 最大操作次数
    vector *v = getNewVector(2); // 创建容量为 2 的 vector
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4, pos, val, ret;
        switch (op) {
        case 0:
        case 1:
        case 2:                            // 75% 的概率插入数据
            pos = rand() % (v->count + 2); // 生成插入位置
            val = rand() % 100;            // 生成随机值
            ret = insert(v, pos, val);     // 插入值到 vector
            printf("insert %d at %d to vector = %d\n", val, pos, ret);
            break;
        case 3:                            // 25% 的概率删除数据
            pos = rand() % (v->count + 2); // 生成删除位置
            ret = erase(v, pos);           // 删除指定位置的值
            printf("erase item at %d in vector = %d\n", pos, ret);
            break;
        }
        output_vector(v); // 输出 vector 当前状态
    }
    clear(v); // 清理 vector
    return 0;
}

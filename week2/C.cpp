// #include <iostream>
// using namespace std;

// int main() {
//     int n;
//     cin >> n;
//     int a[n];
//     for (int i = 0; i < n; i++)
//         cin >> a[i];

//     for (int i = 0; i < n; i++) {
//         bool found = false;               // 用于标记是否找到
//         for (int j = i + 1; j < n; j++) { // 从 i + 1 开始查找
//             if (a[j] > a[i]) {
//                 printf("%d ",
//                        j + 1); // 找到大于 a[i] 的元素，输出下标（1-based）
//                 found = true;  // 标记为找到
//                 break;         // 结束内层循环
//             }
//         }
//         if (!found) {
//             printf("0 "); // 如果没有找到大于 a[i] 的元素，输出 0
//         }
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 3000000

int main() {
    int n;
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));
    int *f = (int *)malloc(n * sizeof(int));
    int *stack = (int *)malloc(n * sizeof(int));
    int top = -1;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        // 当前元素 a[i]
        while (top != -1 && a[stack[top]] <= a[i]) {
            top--; // 弹出小于等于当前元素的下标
        }
        if (top == -1) {
            f[i] = 0; // 没有找到更大的元素
        } else {
            f[i] = stack[top] + 1;
        }
        stack[++top] = i; // 将当前元素的下标压入栈中
    }

    // 输出结果
    for (int i = 0; i < n; i++) {
        printf("%d ", f[i]);
    }
    printf("\n");

    // 释放内存
    free(a);
    free(f);
    free(stack);

    return 0;
}

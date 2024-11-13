#include <stdio.h>

// 宏定义 P，用于打印函数名和函数返回值
#define P(func)                                                                \
    {                                                                          \
        printf("%s = %d\n", #func, func);                                      \
    }

// 二分查找函数 1：查找数组 num 中的元素 x
int binary_search1(int *num, int n, int x) {
    int head = 0;     // 左指针，初始指向数组的开始
    int tail = n - 1; // 右指针，初始指向数组的结束
    int mid;          // 中间指针

    // 当左指针不超过右指针时进行循环
    while (head <= tail) {
        mid = (head + tail) >> 1; // 计算中间位置
        if (num[mid] == x)
            return mid; // 如果找到元素，返回其索引
        if (num[mid] > x)
            tail = mid - 1; // 如果中间元素大于 x，移动右指针
        else
            head = mid + 1; // 如果中间元素小于 x，移动左指针
    }
    return -1; // 如果未找到，返回 -1
}

// 二分查找函数 2：查找数组 num 中最后一个为 1 的元素的索引
int binary_search2(int *num, int n) {
    int head = -1;    // 左指针，初始为 -1（表示在数组外）
    int tail = n - 1; // 右指针，初始指向数组的结束
    int mid;          // 中间指针

    // 当左指针小于右指针时进行循环
    while (head < tail) {
        mid = (head + tail + 1) >> 1; // 计算中间位置，向上取整
        if (num[mid] == 1)
            head = mid; // 如果中间元素为 1，移动左指针
        else
            tail = mid - 1; // 如果中间元素不是 1，移动右指针
    }
    return head; // 返回最后一个为 1 的元素的索引
}

// 二分查找函数 3：查找数组 num 中第一个为 1 的元素的索引
int binary_search3(int *num, int n) {
    int head = 0; // 左指针，初始指向数组的开始
    int tail = n; // 右指针，初始为 n（表示在数组外）
    int mid;      // 中间指针

    // 当左指针小于右指针时进行循环
    while (head < tail) {
        mid = (head + tail) >> 1; // 计算中间位置
        if (num[mid] == 1)
            tail = mid; // 如果中间元素为 1，移动右指针
        else
            head = mid + 1; // 如果中间元素不是 1，移动左指针
    }

    // 如果 head 等于 n，说明没有找到 1，返回 -1；否则返回 head 的索引
    return head == n ? -1 : head;
}

int main() {
    // 测试数组
    int arr1[10] = {1, 3, 5, 7, 11, 13, 17, 19, 23, 29}; // 有序数组
    int arr2[10] = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0};       // 以 1 开头的数组
    int arr3[10] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1};       // 以 0 开头的数组

    // 调用函数并打印结果
    P(binary_search1(arr1, 10, 11)); // 查找 11 的索引
    P(binary_search2(arr2, 10));     // 查找最后一个 1 的索引
    P(binary_search3(arr3, 10));     // 查找第一个 1 的索引

    return 0; // 程序正常结束
}

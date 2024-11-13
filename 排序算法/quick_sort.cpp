#include "sort_test.h"
#include <stdio.h>
#include <stdlib.h>

// 快速排序算法，对数组 arr 的索引范围 [l, r) 进行排序
void quick_sort(int *arr, int l, int r) {
    // 基本情况：当区间元素少于等于 2 个时进行处理
    if (r - l <= 2) {
        if (r - l <= 1)
            return; // 如果区间长度为 0 或 1，直接返回
        if (arr[l] > arr[l + 1])
            swap(arr[l], arr[l + 1]); // 如果区间长度为 2，确保顺序
        return;
    }

    // 1. 分区 (Partitioning)：选择 arr[l] 作为基准元素 z
    int x = l, y = r - 1, z = arr[l];
    while (x < y) {
        // 从右向左找到第一个小于基准的元素
        while (x < y && z <= arr[y])
            --y;
        if (x < y)
            arr[x++] = arr[y]; // 将较小元素移到左侧

        // 从左向右找到第一个大于基准的元素
        while (x < y && arr[x] <= z)
            ++x;
        if (x < y)
            arr[y--] = arr[x]; // 将较大元素移到右侧
    }
    // 将基准元素 z 放到最终的分割点位置
    arr[x] = z;

    // 2. 递归排序左右子数组
    quick_sort(arr, l, x);     // 对左侧子数组 [l, x) 进行排序
    quick_sort(arr, x + 1, r); // 对右侧子数组 [x + 1, r) 进行排序
    return;
}

int main() {
    int *arr = getRandData(SMALL_DATA_N); // 生成一个随机数组用于测试
    TEST(quick_sort, arr, SMALL_DATA_N);  // 测试快速排序算法
    free(arr);                            // 释放动态分配的数组内存
    return 0;
}

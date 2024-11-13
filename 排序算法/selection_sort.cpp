#include "sort_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 选择排序函数，对数组 arr 的索引范围 [l, r) 进行排序
void selection_sort(int *arr, int l, int r) {
    // 从左至右遍历数组，i 为当前放置最小元素的位置
    for (int i = l, I = r - 1; i < I; i++) {
        int ind = i; // ind 保存当前未排序部分最小元素的索引
        // 从 i+1 到 r-1 找到最小值的索引
        for (int j = i + 1; j < r; j++) {
            if (arr[j] < arr[ind])
                ind = j; // 更新最小值索引 ind
        }
        // 将最小元素放到位置 i 处
        swap(arr[i], arr[ind]);
    }
    return;
}

int main() {
    // 生成大小为 SMALL_DATA_N 的随机数组
    int *arr = getRandData(SMALL_DATA_N);
    // 使用 TEST 宏函数测试 selection_sort 函数，排序 arr 数组
    TEST(selection_sort, arr, SMALL_DATA_N);
    // 释放动态分配的内存
    free(arr);
    return 0;
}

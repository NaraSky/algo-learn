#include "sort_test.h"
#include <stdio.h>
#include <stdlib.h>

// 冒泡排序，对数组 arr 的索引范围 [l, r) 进行排序
void bubble_sort(int *arr, int l, int r) {
    // 外层循环：逐轮缩小排序范围，每轮将当前最大值“冒泡”到范围末尾
    for (int i = r - 1, I = l + 1, cnt; i >= I; i--) {
        cnt = 0; // 计数器，用于记录当前轮次是否发生交换
        // 内层循环：在 [l, i) 范围内比较相邻元素并交换
        for (int j = l; j < i; j++) {
            if (arr[j] <= arr[j + 1])
                continue; // 若顺序正确则跳过
            swap(arr[j],
                 arr[j + 1]); // 交换相邻元素，使较大元素逐渐“冒泡”到右边
            cnt += 1;         // 记录交换次数
        }
        // 若本轮遍历没有发生任何交换，表示数组已排序，提前退出
        if (cnt == 0)
            break;
    }
    return;
}

int main() {
    // 生成一个大小为 SMALL_DATA_N 的随机数组
    int *arr = getRandData(SMALL_DATA_N);
    // 测试冒泡排序算法新
    TEST(bubble_sort, arr, SMALL_DATA_N);
    // 释放动态分配的数组内存
    free(arr);
    return 0;
}

#include "sort_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 常规插入排序，对数组 arr 的索引范围 [l, r) 进行排序
void insert_sort(int *arr, int l, int r) {
    // 从第二个元素（索引 l + 1）开始，将每个元素插入到已排序部分
    for (int i = l + 1; i < r; i++) {
        int j = i;
        // 将当前元素 arr[j] 插入到前面的已排序部分，直到满足 arr[j-1] <= arr[j]
        while (j > l && arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]); // 交换 arr[j] 和 arr[j-1]
            j -= 1;                   // 继续向前比较并插入
        }
    }
    return;
}

// 无监视哨插入排序，对数组 arr 的索引范围 [l, r) 进行排序
void unguarded_insert_sort(int *arr, int l, int r) {
    // 找到数组最小值的位置 ind，将其移到最左边作为“监视哨”
    int ind = l;
    for (int i = l + 1; i < r; i++) {
        if (arr[i] < arr[ind])
            ind = i; // 更新最小值索引 ind
    }
    // 将最小元素交换到最左边
    while (ind > l) {
        swap(arr[ind], arr[ind - 1]);
        ind -= 1;
    }
    // 从 l+1 开始执行插入排序，因为 l 处元素已为最小值，保证无需边界检查
    for (int i = l + 1; i < r; i++) {
        int j = i;
        // 无需边界检查，将 arr[j] 插入到前面的已排序部分
        while (arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]); // 交换 arr[j] 和 arr[j-1]
            j -= 1;
        }
    }
    return;
}

int main() {
    // 生成一个大小为 SMALL_DATA_N 的随机数组
    int *arr = getRandData(SMALL_DATA_N);
    // 测试常规插入排序算法
    TEST(insert_sort, arr, SMALL_DATA_N);
    // 测试无监视哨插入排序算法
    TEST(unguarded_insert_sort, arr, SMALL_DATA_N);
    // 释放动态分配的数组内存
    free(arr);
    return 0;
}

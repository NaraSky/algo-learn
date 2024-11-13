#include <stdio.h>
#include <stdlib.h>

// 函数：归并排序
// 描述：对数组进行归并排序，从索引 l 到 r 进行排序。
// 参数：
//   int *arr: 指向要排序的数组的指针
//   int l: 排序的起始索引
//   int r: 排序的结束索引（不包括 r）
void merge_sort(int *arr, int l, int r) {
    // 当待排序的元素数量小于或等于 1 时，直接返回
    if (r - l <= 1)
        return;

    // 计算中间索引
    int mid = (l + r) / 2;

    // 递归排序左半部分和右半部分
    merge_sort(arr, l, mid);
    merge_sort(arr, mid, r);

    // 初始化两个指针，分别指向左半部分和右半部分的起始位置
    int p1 = l;   // 左半部分指针
    int p2 = mid; // 右半部分指针
    int k = 0;    // 临时数组的索引

    // 创建一个临时数组，用于合并
    int *temp = (int *)malloc(sizeof(int) * (r - l));

    // 合并两个有序部分
    while (p1 < mid || p2 < r) {
        if (p2 == r || (p1 < mid && arr[p1] <= arr[p2])) {
            // 右半部分的所有元素已经被处理完。
            // 如果左半部分未结束且当前元素小于等于右半部分元素
            temp[k++] = arr[p1++]; // 将左半部分元素添加到临时数组
        } else {
            // 如果右半部分未结束
            temp[k++] = arr[p2++]; // 将右半部分元素添加到临时数组
        }
    }

    // 将临时数组中的元素拷贝回原数组
    for (int i = 0; i < k; i++) {
        arr[l + i] = temp[i];
    }

    // 释放临时数组内存
    free(temp);
}

// 主函数：程序入口
int main() {
    // 示例用法
    int arr[] = {5, 3, 8, 6, 2};          // 要排序的数组
    int n = sizeof(arr) / sizeof(arr[0]); // 数组的长度

    // 调用归并排序函数
    merge_sort(arr, 0, n);

    // 打印排序后的数组
    printf("排序后的数组：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0; // 程序正常结束
}

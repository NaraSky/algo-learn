#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// 输出数组及其下标的函数
void output(vector<int> &arr) {
    int n = arr.size(), len = 0;

    // 输出数组下标
    for (int i = 0; i < n; i++) {
        len += printf("%3d", i); // 每个下标占3个字符宽度
    }
    printf("\n"); // 换行
    for (int i = 0; i < len; i++)
        printf("-"); // 输出与下标对齐的横线
    printf("\n");    // 换行

    // 输出数组的实际值
    for (int i = 0; i < n; i++) {
        len += printf("%3d", arr[i]); // 每个数值占3个字符宽度
    }
    printf("\n"); // 换行
    return;
}

int main() {
    int n, k;

    // 输入数组长度n和窗口大小k
    cin >> n >> k;

    vector<int> arr; // 存储输入的数组
    deque<int> q;    // 双端队列，用于维护当前窗口的索引

    // 读取数组元素
    for (int i = 0, a; i < n; i++) {
        cin >> a;
        arr.push_back(a); // 把输入的元素放入数组
    }

    // 输出输入的数组及其下标
    output(arr);

    // 对每个数组元素，维护一个滑动窗口
    for (int i = 0; i < n; i++) {

        // 维护一个单调队列，队列中保存的索引对应的数组值是单调递增的
        // 如果当前队列中的元素比arr[i]大，则移除队列尾部的元素
        while (!q.empty() && arr[q.back()] > arr[i]) {
            q.pop_back(); // 队列尾部出队
        }

        // 将当前元素的索引加入队列
        q.push_back(i); // 索引i入队

        // 如果队列头部的元素索引已不在当前窗口内，移除队列头部元素
        if (i - q.front() == k)
            q.pop_front(); // 窗口超出k大小，移除队列前面的元素

        // 输出当前窗口的最小值及其区间
        printf("[%d, %d] = arr[%d] = %d\n", max(i - k + 1, 0),
               i,                        // 输出窗口的起始和结束索引
               q.front(), arr[q.front()] // 输出当前窗口的最小值及其索引
        );
    }
    return 0;
}
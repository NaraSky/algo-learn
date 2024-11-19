#include <iostream>
using namespace std;

#define MAX_N 100               // 定义数组的最大大小
long long arr[MAX_N + 5] = {0}; // 缓存数组，用于存储中间结果，避免重复计算

// 递归函数 f，用于计算第 n 项的值
long long f(int n) {
    if (n <= 2)
        return n; // 基本情况：f(1) = 1, f(2) = 2
    //  原始递归（无记忆化）的时间复杂度为O(2^n)，因为每次递归都会计算两个子问题。
    // 加入记忆化后，时间复杂度降低为𝑂(𝑛)，因为每个值只计算一次。
    if (arr[n])
        return arr[n];            // 如果缓存中已有结果，直接返回
    arr[n] = f(n - 1) + f(n - 2); // 递归计算并存储到缓存中
    return arr[n];                // 返回计算结果
}

int main() {
    int n; // 用户输入 n，表示需要计算第 n 项的值
    cin >> n;
    cout << f(n) << endl;
    return 0;
}

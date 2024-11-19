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

long long f[105] = {
    0}; // 定义数组 f，用于存储从 f(1) 到 f(n) 的值，避免重复计算

int main() {
    int n;    // 用户输入 n，表示需要计算第 n 项的值
    cin >> n; // 读取用户输入
    f[1] = 1; // 初始化边界条件：f(1) = 1
    f[2] = 2; // 初始化边界条件：f(2) = 2

    // 时间复杂度为𝑂(𝑛)，空间复杂度为 𝑂(𝑛) O(n)（存储数组 f）。
    // 使用迭代方式计算 f(3) 到 f(n)
    for (int i = 3; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2]; // 根据递推公式计算
    }

    cout << f[n] << endl; // 输出第 n 项的结果
    return 0;             // 程序正常结束
}

// int main() {
//     int n;
//     cin >> n;
//     if (n == 1)
//         cout << 1 << endl;
//     else if (n == 2)
//         cout << 2 << endl;
//     else {
//         long long a = 1, b = 2, c;
//         for (int i = 3; i <= n; i++) {
//             c = a + b;
//             a = b;
//             b = c;
//         }
//         cout << b << endl;
//     }
//     return 0;
// }

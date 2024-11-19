#include <iostream>
#include <vector>
using namespace std;

// 计算将 n 分成 k 份的分法数
int partition_count(int n, int k) {
    // 创建 DP 表，初始化为 0
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    dp[0][0] = 1; // 初始条件：将 0 分成 0 份有 1 种方法

    // 填充 DP 表 容斥原理
    // 有1-->dp[i - 1][j - 1]假设当前划分中至少有一个部分等于
    // 1，那么我们可以先将 j 份中的每一份分配一个“1”。

    // 无1-->dp[i - j][j] 如果当前划分中不存在“1”，那么每一份的值必须大于等于
    // 2。为了满足这个条件，可以将每一份的值都减去“1”（模拟每一份至少有一个“1”），这会消耗掉j
    // 个单位的值。
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            // 每份至少为 1，所以总和 n≥k
            if (i >= j) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - j][j];
            }
        }
    }

    return dp[n][k];
}

int main() {
    int n, k;
    // 输入 n 和 k
    cin >> n >> k;

    // 输出结果
    cout << partition_count(n, k) << endl;

    return 0;
}

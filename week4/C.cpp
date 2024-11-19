#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 最大草药价值计算函数
int maxHerbValue(int t, int m, vector<pair<int, int>> &herbs) {
    // 初始化 DP 数组，大小为 t + 1，初始值为 0
    vector<int> dp(t + 1, 0);

    // 遍历每种草药
    for (const auto &herb : herbs) {
        int a = herb.first;  // 采集时间
        int b = herb.second; // 草药价值

        // 如果所需时间大于可用时间，跳过
        if (a > t)
            continue;

        // 完全背包：时间从小到大遍历
        for (int j = a; j <= t; ++j) {
            dp[j] = max(dp[j], dp[j - a] + b);
        }
    }

    // 返回最大价值
    return dp[t];
}

int main() {
    int t, m;
    // 输入总时间 t 和草药种类数 m
    cin >> t >> m;

    // 输入每种草药的时间和价值
    vector<pair<int, int>> herbs(m);
    for (int i = 0; i < m; ++i) {
        cin >> herbs[i].first >> herbs[i].second;
    }

    // 输出最大价值
    cout << maxHerbValue(t, m, herbs) << endl;

    return 0;
}

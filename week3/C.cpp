#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    // 反向图的邻接表
    vector<vector<int>> reverseGraph(N + 1);
    vector<int> inDegree(N + 1, 0);

    // 读取输入，构建反向图
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        reverseGraph[v].push_back(u); // 反向边：v -> u
        inDegree[u]++;                // 更新入度
    }

    // 队列，用于拓扑排序
    queue<int> q;
    vector<int> A(N + 1); // 存储结果

    // 初始化：入度为 0 的点加入队列
    for (int i = 1; i <= N; ++i) {
        A[i] = i; // 初始每个点的 A(v) = v
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    // 拓扑排序 + 动态规划
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // 遍历当前点的所有反向邻居
        for (int neighbor : reverseGraph[current]) {
            A[neighbor] = max(A[neighbor], A[current]); // 更新 A(neighbor)
            inDegree[neighbor]--;                       // 入度减 1
            if (inDegree[neighbor] == 0) {
                q.push(neighbor); // 入度为 0，加入队列
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;

    return 0;
}

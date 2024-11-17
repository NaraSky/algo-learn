#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    // 邻接表存储有向图
    vector<vector<int>> graph(n + 1); // 使用 1-based 索引
    vector<int> inDegree(n + 1, 0);   // 存储每个顶点的入度

    // 读取输入并构建图
    for (int i = 1; i <= n; ++i) {
        int descendant;
        while (cin >> descendant && descendant != 0) {
            graph[i].push_back(descendant); // i 指向 descendant
            inDegree[descendant]++;         // descendant 的入度加 1
        }
    }

    // 拓扑排序
    queue<int> q;       // 用队列存储所有入度为 0 的顶点
    vector<int> result; // 存储拓扑排序结果

    // 将所有入度为 0 的顶点入队
    for (int i = 1; i <= n; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    // 开始排序
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        result.push_back(current); // 加入结果序列

        // 遍历当前顶点的所有后代，更新入度
        for (int descendant : graph[current]) {
            inDegree[descendant]--;
            if (inDegree[descendant] == 0) {
                q.push(descendant);
            }
        }
    }

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}

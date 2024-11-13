#include <iostream>
#include <vector>

using namespace std;

int main() {
    int l, m;
    cin >> l >> m;

    // 初始化一个大小为 l + 1 的布尔数组，表示每棵树的状态
    vector<bool> removed(l + 1, false);

    // 遍历每个区域，标记移走的树
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        // 将区间 [u, v] 内的树标记为移走
        for (int j = u; j <= v; ++j) {
            removed[j] = true;
        }
    }

    // 计算剩余的树的数量
    int remainingTrees = 0;
    for (int i = 0; i <= l; ++i) {
        if (!removed[i]) {
            remainingTrees++;
        }
    }

    cout << remainingTrees << endl;

    return 0;
}

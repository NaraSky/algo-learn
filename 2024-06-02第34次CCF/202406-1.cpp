#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, p, q;
    cin >> n >> m >> p >> q;

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    // 构造目标矩阵 b
    vector<vector<int>> b(p, vector<int>(q));
    int linear_idx = 0; // 用于一维映射的索引
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            int row = linear_idx / m; // 原矩阵的行号
            int col = linear_idx % m; // 原矩阵的列号
            b[i][j] = a[row][col];
            linear_idx++;
        }
    }

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(n, 0));
    vector<vector<int>> b(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        a[u][v] = 1;
        a[v][u] = 1;
        b[u].push_back(v);
        b[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        sort(b[i].begin(), b[i].end());

        cout << b[i].size() << " ";

        for (int c : b[i]) {
            cout << c + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}
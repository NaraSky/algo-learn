#include <iostream>
using namespace std;

int ma_dis_x[9] = {0, 2, 1, -1, -2, -2, -1, 1, 2};
int ma_dis_y[9] = {0, 1, 2, 2, 1, -1, -2, -2, -1};
int maps[101][101]; // 1表示该点可以通过，0表示不能通过

long long jg[101][101]; // 结果数组，用于记录到达各点的路径数

int main() {
    int n, m, max, may;
    cin >> n >> m >> max >> may;

    // 初始化数组
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            maps[i][j] = 1; // 先设置所有点可以通过
        }
    }

    // 设置马能走到的点为0，表示不能通过，包括马所在的位置
    for (int i = 0; i <= 8; i++) {
        int nx = max + ma_dis_x[i];
        int ny = may + ma_dis_y[i];
        if (nx >= 0 && nx <= n && ny >= 0 && ny <= m) { // 确保不越界
            maps[nx][ny] = 0; // 设置马能到的点不能通过
        }
    }

    // 动态规划计算路径数
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 && j == 0) {
                jg[i][j] = 1;                       // 设置起点路径数为1
            } else if (maps[i][j] == 1) {           // 该点可以通过
                if (j > 0 && maps[i][j - 1] == 1) { // 从左边来
                    jg[i][j] += jg[i][j - 1];
                }
                if (i > 0 && maps[i - 1][j] == 1) { // 从上边来
                    jg[i][j] += jg[i - 1][j];
                }
            }
        }
    }

    cout << jg[n][m] << endl; // 输出最终点的路径数
    return 0;
}

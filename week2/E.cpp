#include <iostream>
#include <stack>
#include <vector>

using namespace std;

bool canFollowPopSequence(const vector<int> &pushed, const vector<int> &poped) {
    stack<int> stk;
    int popIndex = 0; // 用于追踪poped序列的当前位置

    for (int num : pushed) {
        stk.push(num); // 将元素压入栈中

        // 尝试匹配并弹出栈顶元素，直到栈为空或栈顶元素与poped当前元素不匹配
        while (!stk.empty() && stk.top() == poped[popIndex]) {
            stk.pop();  // 弹出栈顶元素
            popIndex++; // 移动到poped序列的下一个元素
        }
    }

    // 如果栈为空，则说明所有的pop操作都成功匹配了，返回true
    // 否则，说明有些元素没有被成功弹出，返回false
    return stk.empty();
}

int main() {
    int q; // 查询数量
    cin >> q;

    while (q--) {
        int n; // 序列长度
        cin >> n;

        vector<int> pushed(n), poped(n);
        for (int i = 0; i < n; ++i) {
            cin >> pushed[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> poped[i];
        }

        if (canFollowPopSequence(pushed, poped)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}
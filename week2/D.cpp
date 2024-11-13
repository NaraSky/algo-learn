#include <deque>
#include <iostream>
#include <vector>
using namespace std;

void test(int n, int k, const vector<int> &a) {
    deque<int> min_deque, max_deque;
    vector<int> min_res, max_res;

    for (int i = 0; i < n; ++i) {
        while (!min_deque.empty() && a[min_deque.back()] >= a[i]) {
            min_deque.pop_back();
        }
        min_deque.push_back(i);

        while (!max_deque.empty() && a[max_deque.back()] <= a[i]) {
            max_deque.pop_back();
        }
        max_deque.push_back(i);

        if (min_deque.front() <= i - k) {
            min_deque.pop_front();
        }
        if (max_deque.front() <= i - k) {
            max_deque.pop_front();
        }

        if (i >= k - 1) {
            min_res.push_back(a[min_deque.front()]);
            max_res.push_back(a[max_deque.front()]);
        }
    }

    for (int i = 0; i < min_res.size(); ++i) {
        cout << min_res[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < max_res.size(); ++i) {
        cout << max_res[i] << " ";
    }
    cout << endl;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    test(n, k, a);

    return 0;
}

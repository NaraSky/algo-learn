#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int get_hash(string &s) {
    int base = 131, h = 0;
    for (int i = 0; s[i]; i++) {
        h = h * base + s[i];
        // 对于字符串的每个字符，将 h 乘以 base，再加上当前字符的 ASCII 值。
    }
    return h;
}
int main() {
    int n, hash_code, ans = 0;
    unordered_map<int, vector<string>> h;
    string s;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s;
        hash_code = get_hash(s);
        if (h.find(hash_code) == h.end()) {
            ans += 1;
            h[hash_code].push_back(s);
        } else {
            int flag = 1;
            for (auto t : h[hash_code]) {
                if (t != s)
                    continue;
                flag = 0;
                break;
            }
            if (flag) {
                ans += 1;
                h[hash_code].push_back(s);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
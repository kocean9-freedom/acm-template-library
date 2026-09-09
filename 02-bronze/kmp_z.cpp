// KMP + Z 函数：KMP 找模式串出现位置，Z 求每个后缀与整串 LCP。
// 复杂度均为 O(n)。主程序采用洛谷 P3375 风格输入输出。
#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string &s) {
    int n = (int)s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> z_function(const string &s) {
    int n = (int)s.size();
    vector<int> z(n);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text, pat;
    cin >> text >> pat;
    vector<int> pi = prefix_function(pat);
    for (int i = 0, j = 0; i < (int)text.size(); i++) {
        while (j && text[i] != pat[j]) j = pi[j - 1];
        if (text[i] == pat[j]) j++;
        if (j == (int)pat.size()) {
            cout << i - j + 2 << '\n';  // 1 下标起点。
            j = pi[j - 1];
        }
    }
    for (int i = 0; i < (int)pi.size(); i++) cout << pi[i] << " \n"[i + 1 == (int)pi.size()];
    return 0;
}

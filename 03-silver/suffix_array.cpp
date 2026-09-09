// 后缀数组倍增法 + Kasai LCP。输出 0 下标 SA，以及 lcp[i]=LCP(sa[i-1],sa[i])。
// 当前写法用 comparison sort，复杂度 O(n log^2 n)，适合个人板与中等规模数据。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    vector<int> sa(n), rk(n), tmp(n);
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i < n; i++) rk[i] = (unsigned char)s[i];
    for (int k = 1;; k <<= 1) {
        sort(sa.begin(), sa.end(), [&](int x, int y) {
            if (rk[x] != rk[y]) return rk[x] < rk[y];
            int rx = x + k < n ? rk[x + k] : -1;
            int ry = y + k < n ? rk[y + k] : -1;
            return rx < ry;
        });
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            int x = sa[i - 1], y = sa[i];
            pair<int, int> px = {rk[x], x + k < n ? rk[x + k] : -1};
            pair<int, int> py = {rk[y], y + k < n ? rk[y + k] : -1};
            tmp[y] = tmp[x] + (px != py);
        }
        rk = tmp;
        if (rk[sa.back()] == n - 1) break;
    }
    vector<int> pos(n), lcp(n);
    for (int i = 0; i < n; i++) pos[sa[i]] = i;
    for (int i = 0, h = 0; i < n; i++) {
        int p = pos[i];
        if (!p) continue;
        int j = sa[p - 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
        lcp[p] = h;
        if (h) h--;
    }
    for (int i = 0; i < n; i++) cout << sa[i] << " \n"[i + 1 == n];
    for (int i = 0; i < n; i++) cout << lcp[i] << " \n"[i + 1 == n];
    return 0;
}

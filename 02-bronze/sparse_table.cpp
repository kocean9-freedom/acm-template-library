// ST 表：静态区间最大值，要求合并操作可重复贡献（max/min/gcd）。
// 预处理 O(n log n)，单次查询 O(1)。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int LOG = 20;
int n, m, st[MAXN][LOG], lg[MAXN];

int query(int l, int r) {
    int k = lg[r - l + 1];
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> st[i][0];
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            st[i][k] = max(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
        }
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }
    return 0;
}

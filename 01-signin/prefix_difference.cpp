// 一维差分：m 次区间加，最后还原数组。
// 输入：n m；初始数组；m 行 l r v。下标从 1 开始。
// 复杂度：O(n+m)，空间 O(n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 5;

int n, m;
ll a[MAXN], d[MAXN], sum[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        d[i] = a[i] - a[i - 1];
        sum[i] = sum[i - 1] + a[i];  // 原数组前缀和，静态查询可直接用。
    }
    while (m--) {
        int l, r;
        ll v;
        cin >> l >> r >> v;
        d[l] += v;
        d[r + 1] -= v;
    }
    for (int i = 1; i <= n; i++) {
        a[i] = a[i - 1] + d[i];
        cout << a[i] << " \n"[i == n];
    }
    return 0;
}

// 基础 DP：非负/有负权网格中，只能向右或向下，求左上到右下最小路径和。
// f[i][j] 只依赖上方和左方，可滚动为一维。复杂度 O(nm)，空间 O(m)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> f(m + 1, INF);
    f[1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ll x;
            cin >> x;
            f[j] = min(f[j], f[j - 1]) + x;
        }
    }
    cout << f[m] << '\n';
    return 0;
}

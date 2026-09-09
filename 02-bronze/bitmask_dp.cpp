// 状压 DP：从 0 出发、以 n-1 结束且每点恰访问一次的最短 Hamilton 路，n <= 20。
// f[mask][i] 表示已访问 mask 且当前在 i 的最小代价。复杂度 O(2^n*n^2)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<ll>> w(n, vector<ll>(n));
    for (auto &row : w) for (ll &x : row) cin >> x;
    vector<vector<ll>> f(1 << n, vector<ll>(n, INF));
    f[1][0] = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int x = 0; x < n; x++) if (mask >> x & 1) {
            if (f[mask][x] == INF) continue;
            for (int y = 0; y < n; y++) if (!(mask >> y & 1)) {
                f[mask | 1 << y][y] = min(f[mask | 1 << y][y], f[mask][x] + w[x][y]);
            }
        }
    }
    cout << f[(1 << n) - 1][n - 1] << '\n';
    return 0;
}

// 区间 DP：矩阵链乘法最少标量乘法次数。
// f[l][r] 枚举最后断点 k，由两个更短区间转移。复杂度 O(n^3)，空间 O(n^2)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> p(n + 1);
    for (ll &x : p) cin >> x;
    vector<vector<ll>> f(n + 1, vector<ll>(n + 1));
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            f[l][r] = INF;
            for (int k = l; k < r; k++) {
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + p[l - 1] * p[k] * p[r]);
            }
        }
    }
    cout << f[1][n] << '\n';
    return 0;
}

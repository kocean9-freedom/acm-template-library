// Floyd：小规模图的全源最短路，可有负边但不能有可达负环。
// 复杂度 O(n^3)，空间 O(n^2)，通常 n <= 500。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 505;
const ll INF = 4e18;

int n, m, q;
ll d[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) d[i][j] = (i == j ? 0 : INF);
    }
    while (m--) {
        int x, y;
        ll w;
        cin >> x >> y >> w;
        d[x][y] = min(d[x][y], w);
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (d[i][k] == INF) continue;
            for (int j = 1; j <= n; j++) {
                if (d[k][j] == INF) continue;
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << (d[x][y] == INF ? -1 : d[x][y]) << '\n';
    }
    return 0;
}

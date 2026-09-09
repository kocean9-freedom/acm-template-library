// Bellman-Ford：有向图允许负边，求单源最短路并判断从源点可达的负环。
// 复杂度 O(nm)。稀疏非负图优先 Dijkstra；差分约束见银牌目录。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

struct Edge {
    int x, y;
    ll w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;
    vector<Edge> e(m);
    for (auto &[x, y, w] : e) cin >> x >> y >> w;
    vector<ll> dis(n + 1, INF);
    dis[s] = 0;

    bool neg = false;
    for (int i = 1; i <= n; i++) {
        bool changed = false;
        for (auto [x, y, w] : e) {
            if (dis[x] == INF || dis[y] <= dis[x] + w) continue;
            dis[y] = dis[x] + w;
            changed = true;
            if (i == n) neg = true;
        }
        if (!changed) break;
    }
    if (neg) {
        cout << "NEGATIVE CYCLE\n";
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        if (dis[i] == INF) cout << "INF";
        else cout << dis[i];
        cout << " \n"[i == n];
    }
    return 0;
}

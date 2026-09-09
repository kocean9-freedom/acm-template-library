// Tarjan SCC + 缩点 DAG DP：点权有向图上的最大路径权值和。
// 复杂度 O(n+m)。对应常见题型：洛谷 P3387。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 5;

int n, m, tim, top, scc_cnt;
int dfn[MAXN], low[MAXN], st[MAXN], bel[MAXN], deg[MAXN];
ll w[MAXN], sw[MAXN], f[MAXN];
bool ins[MAXN];
vector<int> e[MAXN], dag[MAXN];

void tarjan(int x) {
    dfn[x] = low[x] = ++tim;
    st[++top] = x;
    ins[x] = true;
    for (int y : e[x]) {
        if (!dfn[y]) tarjan(y), low[x] = min(low[x], low[y]);
        else if (ins[y]) low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] != low[x]) return;
    ++scc_cnt;
    while (true) {
        int y = st[top--];
        ins[y] = false;
        bel[y] = scc_cnt;
        sw[scc_cnt] += w[y];
        if (y == x) break;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    vector<pair<int, int>> edges;
    while (m--) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        edges.push_back({x, y});
    }
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
    for (auto [x, y] : edges) {
        x = bel[x], y = bel[y];
        if (x != y) dag[x].push_back(y), deg[y]++;
    }
    queue<int> q;
    for (int i = 1; i <= scc_cnt; i++) {
        f[i] = sw[i];
        if (!deg[i]) q.push(i);
    }
    ll ans = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        ans = max(ans, f[x]);
        for (int y : dag[x]) {
            f[y] = max(f[y], f[x] + sw[y]);
            if (--deg[y] == 0) q.push(y);
        }
    }
    cout << ans << '\n';
    return 0;
}

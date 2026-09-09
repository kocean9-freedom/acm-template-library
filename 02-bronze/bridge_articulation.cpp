// Tarjan 求无向图的桥与割点。返祖边用 dfn，树边回溯更新 low。
// 根有至少两个 DFS 儿子才是割点；重边靠边编号区分。复杂度 O(n+m)。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
int n, m, timer, dfn[MAXN], low[MAXN];
bool cut[MAXN];
vector<pair<int, int>> e[MAXN];
vector<pair<int, int>> bridges;

void dfs(int x, int in_edge) {
    dfn[x] = low[x] = ++timer;
    int child = 0;
    for (auto [y, id] : e[x]) {
        if (!dfn[y]) {
            child++;
            dfs(y, id);
            low[x] = min(low[x], low[y]);
            if (low[y] > dfn[x]) bridges.push_back(minmax(x, y));
            if (in_edge != -1 && low[y] >= dfn[x]) cut[x] = true;
        } else if (id != in_edge) {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (in_edge == -1 && child >= 2) cut[x] = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back({y, i});
        e[y].push_back({x, i});
    }
    for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i, -1);
    sort(bridges.begin(), bridges.end());
    cout << bridges.size() << '\n';
    for (auto [x, y] : bridges) cout << x << ' ' << y << '\n';
    vector<int> cuts;
    for (int i = 1; i <= n; i++) if (cut[i]) cuts.push_back(i);
    cout << cuts.size() << '\n';
    for (int i = 0; i < (int)cuts.size(); i++) {
        cout << cuts[i] << " \n"[i + 1 == (int)cuts.size()];
    }
    return 0;
}

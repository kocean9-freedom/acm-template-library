// 倍增 LCA：树上最近公共祖先。
// 预处理 O(n log n)，单次查询 O(log n)。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 5;
const int LOG = 20;

int n, m, root, dep[MAXN], up[MAXN][LOG];
vector<int> e[MAXN];

void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    up[x][0] = fa;
    for (int k = 1; k < LOG; k++) up[x][k] = up[up[x][k - 1]][k - 1];
    for (int y : e[x]) if (y != fa) dfs(y, x);
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    int d = dep[x] - dep[y];
    for (int k = 0; k < LOG; k++) if (d >> k & 1) x = up[x][k];
    if (x == y) return x;
    for (int k = LOG - 1; k >= 0; k--) {
        if (up[x][k] != up[y][k]) x = up[x][k], y = up[y][k];
    }
    return up[x][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> root;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(root, 0);
    while (m--) {
        int x, y;
        cin >> x >> y;
        cout << lca(x, y) << '\n';
    }
    return 0;
}

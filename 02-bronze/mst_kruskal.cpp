// Kruskal：无向图最小生成树。
// 复杂度 O(m log m)，不连通时输出 orz。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 5;

struct Edge {
    int x, y, w;
    bool operator<(const Edge &o) const { return w < o.w; }
};

int n, m, fa[MAXN], siz[MAXN];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (siz[x] < siz[y]) swap(x, y);
    fa[y] = x;
    siz[x] += siz[y];
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    vector<Edge> e(m);
    for (auto &[x, y, w] : e) cin >> x >> y >> w;
    sort(e.begin(), e.end());
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    int cnt = 0;
    ll ans = 0;
    for (auto [x, y, w] : e) {
        if (merge(x, y)) ans += w, cnt++;
    }
    if (cnt != n - 1) cout << "orz\n";
    else cout << ans << '\n';
    return 0;
}

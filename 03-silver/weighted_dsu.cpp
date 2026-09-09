// 带权并查集：维护 potential[y]-potential[x]=w，并回答同集合两点势能差。
// d[x]=potential[x]-potential[parent[x]]；路径压缩时同步累加。近似 O(alpha(n))。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 5;
int fa[MAXN], siz[MAXN];
ll d[MAXN];

int find(int x) {
    if (fa[x] == x) return x;
    int p = fa[x];
    fa[x] = find(fa[x]);
    d[x] += d[p];
    return fa[x];
}

bool unite(int x, int y, ll w) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return d[y] - d[x] == w;
    if (siz[fx] <= siz[fy]) {
        fa[fx] = fy;
        d[fx] = d[y] - d[x] - w;
        siz[fy] += siz[fx];
    } else {
        fa[fy] = fx;
        d[fy] = w + d[x] - d[y];
        siz[fx] += siz[fy];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    iota(fa + 1, fa + n + 1, 1);
    fill(siz + 1, siz + n + 1, 1);
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            ll w;
            cin >> w;
            if (!unite(x, y, w)) cout << "CONTRADICTION\n";
        } else {
            if (find(x) != find(y)) cout << "UNKNOWN\n";
            else cout << d[y] - d[x] << '\n';
        }
    }
    return 0;
}

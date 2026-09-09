// 树链剖分 + 线段树：路径/子树区间加与区间和，答案取模。
// 预处理 O(n)，单次路径操作 O(log^2 n)，子树操作 O(log n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 5;

int n, m, root;
ll mod, a[MAXN];
int fa[MAXN], dep[MAXN], siz[MAXN], son[MAXN], top[MAXN], dfn[MAXN], rid[MAXN], tim;
ll sum[MAXN << 2], tag[MAXN << 2];
vector<int> e[MAXN];

void dfs1(int x, int f) {
    fa[x] = f;
    dep[x] = dep[f] + 1;
    siz[x] = 1;
    for (int y : e[x]) {
        if (y == f) continue;
        dfs1(y, x);
        siz[x] += siz[y];
        if (siz[y] > siz[son[x]]) son[x] = y;
    }
}

void dfs2(int x, int tp) {
    top[x] = tp;
    dfn[x] = ++tim;
    rid[tim] = x;
    if (son[x]) dfs2(son[x], tp);
    for (int y : e[x]) if (y != fa[x] && y != son[x]) dfs2(y, y);
}

void apply(int i, int l, int r, ll v) {
    v %= mod;
    sum[i] = (sum[i] + (r - l + 1) * v) % mod;
    tag[i] = (tag[i] + v) % mod;
}

void down(int i, int l, int r) {
    if (!tag[i]) return;
    int mid = (l + r) >> 1;
    apply(i << 1, l, mid, tag[i]);
    apply(i << 1 | 1, mid + 1, r, tag[i]);
    tag[i] = 0;
}

void build(int i, int l, int r) {
    if (l == r) {
        sum[i] = a[rid[l]] % mod;
        return;
    }
    int mid = (l + r) >> 1;
    build(i << 1, l, mid);
    build(i << 1 | 1, mid + 1, r);
    sum[i] = (sum[i << 1] + sum[i << 1 | 1]) % mod;
}

void update(int ql, int qr, ll v, int i = 1, int l = 1, int r = n) {
    if (ql <= l && r <= qr) {
        apply(i, l, r, v);
        return;
    }
    down(i, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(ql, qr, v, i << 1, l, mid);
    if (qr > mid) update(ql, qr, v, i << 1 | 1, mid + 1, r);
    sum[i] = (sum[i << 1] + sum[i << 1 | 1]) % mod;
}

ll query(int ql, int qr, int i = 1, int l = 1, int r = n) {
    if (ql <= l && r <= qr) return sum[i];
    down(i, l, r);
    int mid = (l + r) >> 1;
    ll ans = 0;
    if (ql <= mid) ans += query(ql, qr, i << 1, l, mid);
    if (qr > mid) ans += query(ql, qr, i << 1 | 1, mid + 1, r);
    return ans % mod;
}

void path_add(int x, int y, ll v) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        update(dfn[top[x]], dfn[x], v);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    update(dfn[x], dfn[y], v);
}

ll path_sum(int x, int y) {
    ll ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = (ans + query(dfn[top[x]], dfn[x])) % mod;
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return (ans + query(dfn[x], dfn[y])) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> root >> mod;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs1(root, 0);
    dfs2(root, root);
    build(1, 1, n);
    while (m--) {
        int op, x, y;
        ll v;
        cin >> op >> x;
        if (op == 1) cin >> y >> v, path_add(x, y, v);
        else if (op == 2) cin >> y, cout << path_sum(x, y) << '\n';
        else if (op == 3) cin >> v, update(dfn[x], dfn[x] + siz[x] - 1, v);
        else cout << query(dfn[x], dfn[x] + siz[x] - 1) << '\n';
    }
    return 0;
}

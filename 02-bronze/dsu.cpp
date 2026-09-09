// 并查集：维护连通块，支持合并与连通性查询。
// 均摊复杂度近似 O(1)，下标从 1 开始。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
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
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) merge(x, y);
        else cout << (find(x) == find(y) ? "Y" : "N") << '\n';
    }
    return 0;
}

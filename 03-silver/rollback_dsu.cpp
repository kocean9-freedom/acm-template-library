// 可撤销并查集：支持合并、记录版本、回滚到指定历史长度、查询连通性。
// 为了可撤销不能路径压缩，只按大小合并；单次合并/查询 O(log n)，回滚 O(撤销次数)。
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> fa, siz;
    struct Change { int child, parent_size; };
    vector<Change> history;

    explicit DSU(int n) : fa(n + 1), siz(n + 1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int x) const {
        while (fa[x] != x) x = fa[x];
        return x;
    }

    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) {
            history.push_back({-1, -1});
            return;
        }
        if (siz[x] > siz[y]) swap(x, y);
        history.push_back({x, siz[y]});
        fa[x] = y;
        siz[y] += siz[x];
    }

    void rollback(int t) {
        while ((int)history.size() > t) {
            auto [x, old_size] = history.back();
            history.pop_back();
            if (x == -1) continue;
            int y = fa[x];
            fa[x] = x;
            siz[y] = old_size;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    DSU dsu(n);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            dsu.unite(x, y);
        } else if (op == 2) {
            cout << dsu.history.size() << '\n';
        } else if (op == 3) {
            int t;
            cin >> t;
            dsu.rollback(t);
        } else {
            int x, y;
            cin >> x >> y;
            cout << (dsu.find(x) == dsu.find(y) ? 'Y' : 'N') << '\n';
        }
    }
    return 0;
}

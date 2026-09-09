// 离散 Li Chao 树：动态加入直线 y=kx+b，查询给定 x 的最大值。
// 先离线收集所有查询坐标，避免巨大值域节点池。单次 O(log q)，计算用 __int128。
#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;
const i128 NEG = -((i128)1 << 120);

struct Line {
    i128 k = 0, b = NEG;
    i128 get(long long x) const { return k * x + b; }
};

struct Query {
    int op;
    long long x, y;
};

vector<long long> xs;
vector<Line> tr;

void add(Line nw, int i, int l, int r) {
    int mid = (l + r) >> 1;
    long long xl = xs[l], xm = xs[mid];
    bool left = nw.get(xl) > tr[i].get(xl);
    bool middle = nw.get(xm) > tr[i].get(xm);
    if (middle) swap(nw, tr[i]);
    if (l == r) return;
    if (left != middle) add(nw, i << 1, l, mid);
    else add(nw, i << 1 | 1, mid + 1, r);
}

i128 query(int p, int i, int l, int r) {
    i128 ans = tr[i].get(xs[p]);
    if (l == r) return ans;
    int mid = (l + r) >> 1;
    if (p <= mid) return max(ans, query(p, i << 1, l, mid));
    return max(ans, query(p, i << 1 | 1, mid + 1, r));
}

void print_i128(i128 x) {
    if (x < 0) cout << '-', x = -x;
    if (x >= 10) print_i128(x / 10);
    cout << char('0' + x % 10);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    vector<Query> ops;
    for (int i = 0; i < q; i++) {
        int op;
        long long x, y = 0;
        cin >> op >> x;
        if (op == 1) cin >> y;
        else xs.push_back(x);
        ops.push_back({op, x, y});
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    if (xs.empty()) return 0;
    tr.assign(xs.size() * 4 + 5, Line{});
    int lines = 0;
    for (auto [op, x, y] : ops) {
        if (op == 1) {
            add({x, y}, 1, 0, xs.size() - 1);
            lines++;
        } else if (!lines) {
            cout << "EMPTY\n";
        } else {
            int p = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
            print_i128(query(p, 1, 0, xs.size() - 1));
            cout << '\n';
        }
    }
    return 0;
}

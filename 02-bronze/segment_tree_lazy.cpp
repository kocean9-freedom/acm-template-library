// 懒标记线段树：区间加、区间和。下标从 1 开始。
// 单次操作 O(log n)，空间 O(n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 5;

int n, m;
ll a[MAXN], sum[MAXN << 2], tag[MAXN << 2];

void up(int i) {
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

void apply(int i, int l, int r, ll v) {
    sum[i] += (r - l + 1) * v;
    tag[i] += v;
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
        sum[i] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(i << 1, l, mid);
    build(i << 1 | 1, mid + 1, r);
    up(i);
}

void update(int ql, int qr, ll v, int i, int l, int r) {
    if (ql <= l && r <= qr) {
        apply(i, l, r, v);
        return;
    }
    down(i, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(ql, qr, v, i << 1, l, mid);
    if (qr > mid) update(ql, qr, v, i << 1 | 1, mid + 1, r);
    up(i);
}

ll query(int ql, int qr, int i, int l, int r) {
    if (ql <= l && r <= qr) return sum[i];
    down(i, l, r);
    int mid = (l + r) >> 1;
    ll ans = 0;
    if (ql <= mid) ans += query(ql, qr, i << 1, l, mid);
    if (qr > mid) ans += query(ql, qr, i << 1 | 1, mid + 1, r);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            ll v;
            cin >> v;
            update(l, r, v, 1, 1, n);
        } else {
            cout << query(l, r, 1, 1, n) << '\n';
        }
    }
    return 0;
}

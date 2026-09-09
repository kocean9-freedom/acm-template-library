// 二进制序列线段树：区间置 0/1、区间翻转、查询 1 的个数/最长连续 1。
// 对应常见题型：洛谷 P2572。输入区间为 0 下标，内部转为 1 下标。
// 单次操作 O(log n)，空间 O(n)。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

struct Node {
    int len, sum;
    int pre[2], suf[2], best[2];
};

int n, m, a[MAXN], set_tag[MAXN << 2];
bool rev_tag[MAXN << 2];
Node tr[MAXN << 2];

Node merge_node(const Node &L, const Node &R) {
    if (!L.len) return R;
    if (!R.len) return L;
    Node x{};
    x.len = L.len + R.len;
    x.sum = L.sum + R.sum;
    for (int v = 0; v <= 1; v++) {
        x.pre[v] = L.pre[v] == L.len ? L.len + R.pre[v] : L.pre[v];
        x.suf[v] = R.suf[v] == R.len ? R.len + L.suf[v] : R.suf[v];
        x.best[v] = max({L.best[v], R.best[v], L.suf[v] + R.pre[v]});
    }
    return x;
}

void apply_set(int i, int v) {
    tr[i].sum = v ? tr[i].len : 0;
    for (int b = 0; b <= 1; b++) {
        int x = b == v ? tr[i].len : 0;
        tr[i].pre[b] = tr[i].suf[b] = tr[i].best[b] = x;
    }
    set_tag[i] = v;
    rev_tag[i] = false;
}

void apply_rev(int i) {
    tr[i].sum = tr[i].len - tr[i].sum;
    swap(tr[i].pre[0], tr[i].pre[1]);
    swap(tr[i].suf[0], tr[i].suf[1]);
    swap(tr[i].best[0], tr[i].best[1]);
    if (set_tag[i] != -1) set_tag[i] ^= 1;
    else rev_tag[i] = !rev_tag[i];
}

void up(int i) {
    tr[i] = merge_node(tr[i << 1], tr[i << 1 | 1]);
}

void down(int i) {
    if (set_tag[i] != -1) {
        apply_set(i << 1, set_tag[i]);
        apply_set(i << 1 | 1, set_tag[i]);
        set_tag[i] = -1;
    }
    if (rev_tag[i]) {
        apply_rev(i << 1);
        apply_rev(i << 1 | 1);
        rev_tag[i] = false;
    }
}

void build(int i, int l, int r) {
    set_tag[i] = -1;
    tr[i].len = r - l + 1;
    if (l == r) {
        tr[i].sum = a[l];
        tr[i].pre[a[l]] = tr[i].suf[a[l]] = tr[i].best[a[l]] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(i << 1, l, mid);
    build(i << 1 | 1, mid + 1, r);
    up(i);
}

void update(int ql, int qr, int op, int i, int l, int r) {
    if (ql <= l && r <= qr) {
        if (op <= 1) apply_set(i, op);
        else apply_rev(i);
        return;
    }
    down(i);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(ql, qr, op, i << 1, l, mid);
    if (qr > mid) update(ql, qr, op, i << 1 | 1, mid + 1, r);
    up(i);
}

Node query(int ql, int qr, int i, int l, int r) {
    if (ql <= l && r <= qr) return tr[i];
    down(i);
    int mid = (l + r) >> 1;
    if (qr <= mid) return query(ql, qr, i << 1, l, mid);
    if (ql > mid) return query(ql, qr, i << 1 | 1, mid + 1, r);
    return merge_node(query(ql, qr, i << 1, l, mid),
                      query(ql, qr, i << 1 | 1, mid + 1, r));
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
        l++, r++;
        if (op <= 2) update(l, r, op, 1, 1, n);
        else {
            Node ans = query(l, r, 1, 1, n);
            cout << (op == 3 ? ans.sum : ans.best[1]) << '\n';
        }
    }
    return 0;
}

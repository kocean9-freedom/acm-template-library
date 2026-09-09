// 主席树：静态数组区间第 k 小。
// 建树 O(n log n)，单次查询 O(log n)，需要离散化。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
const int MAXNODE = MAXN * 22;

int n, m, tot, a[MAXN], root[MAXN];
int ls[MAXNODE], rs[MAXNODE], sum[MAXNODE];

int update(int pre, int l, int r, int p) {
    int now = ++tot;
    ls[now] = ls[pre], rs[now] = rs[pre], sum[now] = sum[pre] + 1;
    if (l == r) return now;
    int mid = (l + r) >> 1;
    if (p <= mid) ls[now] = update(ls[pre], l, mid, p);
    else rs[now] = update(rs[pre], mid + 1, r, p);
    return now;
}

int kth(int left_root, int right_root, int l, int r, int k) {
    if (l == r) return l;
    int cnt = sum[ls[right_root]] - sum[ls[left_root]];
    int mid = (l + r) >> 1;
    if (k <= cnt) return kth(ls[left_root], ls[right_root], l, mid, k);
    return kth(rs[left_root], rs[right_root], mid + 1, r, k - cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    vector<int> b;
    for (int i = 1; i <= n; i++) cin >> a[i], b.push_back(a[i]);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 1; i <= n; i++) {
        int p = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
        root[i] = update(root[i - 1], 1, (int)b.size(), p);
    }
    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        int p = kth(root[l - 1], root[r], 1, (int)b.size(), k);
        cout << b[p - 1] << '\n';
    }
    return 0;
}

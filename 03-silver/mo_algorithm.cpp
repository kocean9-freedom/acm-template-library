// 普通莫队：静态数组多次询问区间不同数个数。
// 离散化后移动左右端点，复杂度约 O((n+q)*sqrt(n))。
#include <bits/stdc++.h>
using namespace std;

struct Query {
    int l, r, id, block;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1), b;
    for (int i = 1; i <= n; i++) cin >> a[i], b.push_back(a[i]);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();

    int siz = max(1, (int)sqrt(n));
    vector<Query> ask(q);
    for (int i = 0; i < q; i++) {
        cin >> ask[i].l >> ask[i].r;
        ask[i].id = i;
        ask[i].block = ask[i].l / siz;
    }
    sort(ask.begin(), ask.end(), [](const Query &x, const Query &y) {
        if (x.block != y.block) return x.block < y.block;
        return x.block & 1 ? x.r > y.r : x.r < y.r;
    });

    vector<int> cnt(b.size()), ans(q);
    int l = 1, r = 0, now = 0;
    auto add = [&](int p) { if (cnt[a[p]]++ == 0) now++; };
    auto del = [&](int p) { if (--cnt[a[p]] == 0) now--; };
    for (auto qu : ask) {
        while (l > qu.l) add(--l);
        while (r < qu.r) add(++r);
        while (l < qu.l) del(l++);
        while (r > qu.r) del(r--);
        ans[qu.id] = now;
    }
    for (int x : ans) cout << x << '\n';
    return 0;
}

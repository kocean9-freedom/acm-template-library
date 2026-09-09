// 树状数组：单点加、区间和。下标必须从 1 开始。
// 单次修改/查询 O(log n)，空间 O(n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 5e5 + 5;

int n, m;
ll tr[MAXN];

int lowbit(int x) { return x & -x; }

void add(int x, ll v) {
    for (; x <= n; x += lowbit(x)) tr[x] += v;
}

ll ask(int x) {
    ll ans = 0;
    for (; x; x -= lowbit(x)) ans += tr[x];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        add(i, x);
    }
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) add(x, y);
        else cout << ask(y) - ask(x - 1) << '\n';
    }
    return 0;
}

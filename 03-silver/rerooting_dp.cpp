// 换根 DP：求树上每个点到所有点的距离和。
// 已知 ans[x] 后移根到儿子 y：ans[y]=ans[x]+n-2*siz[y]。复杂度 O(n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 5;
int n, siz[MAXN];
ll ans[MAXN];
vector<int> e[MAXN];

void dfs1(int x, int fa, int dep) {
    siz[x] = 1;
    ans[1] += dep;
    for (int y : e[x]) {
        if (y == fa) continue;
        dfs1(y, x, dep + 1);
        siz[x] += siz[y];
    }
}

void dfs2(int x, int fa) {
    for (int y : e[x]) {
        if (y == fa) continue;
        ans[y] = ans[x] + n - 2LL * siz[y];
        dfs2(y, x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs1(1, 0, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
    return 0;
}

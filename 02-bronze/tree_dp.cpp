// 树形 DP：带点权树的最大权独立集，相邻点不能同时选择。
// f[x][0/1] 表示不选/选择 x 的子树最优值。复杂度 O(n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 5;
int n;
ll w[MAXN], f[MAXN][2];
vector<int> e[MAXN];

void dfs(int x, int fa) {
    f[x][1] = w[x];
    for (int y : e[x]) {
        if (y == fa) continue;
        dfs(y, x);
        f[x][0] += max(f[y][0], f[y][1]);
        f[x][1] += f[y][0];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(1, 0);
    cout << max(f[1][0], f[1][1]) << '\n';
    return 0;
}

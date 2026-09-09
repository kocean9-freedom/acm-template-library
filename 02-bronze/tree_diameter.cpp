// 树的直径：两次 DFS，适用于非负边权树。
// 复杂度 O(n)。若有负边权，需改用树形 DP。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 5;

int n, far_node;
ll far_dis;
vector<pair<int, int>> e[MAXN];

void dfs(int x, int fa, ll d) {
    if (d > far_dis) far_dis = d, far_node = x;
    for (auto [y, w] : e[x]) if (y != fa) dfs(y, x, d + w);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        e[x].push_back({y, w});
        e[y].push_back({x, w});
    }
    far_dis = -1;
    dfs(1, 0, 0);
    int s = far_node;
    far_dis = -1;
    dfs(s, 0, 0);
    cout << far_dis << '\n';
    return 0;
}

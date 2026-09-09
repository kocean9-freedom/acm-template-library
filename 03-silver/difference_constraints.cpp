// 差分约束：每条限制 x[v]-x[u] <= w 建边 u->v(w)，求一组可行势能。
// 所有点初始入队等价于超级源；SPFA 检测负环。最坏 O(nm)，存在负环则无解。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 5;
int n, m, cnt[MAXN];
ll dis[MAXN];
bool inq[MAXN];
vector<pair<int, ll>> e[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        e[u].push_back({v, w});
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) q.push(i), inq[i] = true;
    bool ok = true;
    while (!q.empty() && ok) {
        int x = q.front();
        q.pop();
        inq[x] = false;
        for (auto [y, w] : e[x]) {
            if (dis[y] <= dis[x] + w) continue;
            dis[y] = dis[x] + w;
            cnt[y] = cnt[x] + 1;
            if (cnt[y] >= n) {
                ok = false;
                break;
            }
            if (!inq[y]) q.push(y), inq[y] = true;
        }
    }
    if (!ok) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int i = 1; i <= n; i++) cout << dis[i] << " \n"[i == n];
    return 0;
}

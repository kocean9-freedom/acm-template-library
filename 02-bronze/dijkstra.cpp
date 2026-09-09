// 堆优化 Dijkstra：非负边权有向图单源最短路。
// 复杂度 O((n+m) log n)，不可用于负边权。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;
const int MAXN = 2e5 + 5;
const ll INF = 4e18;

int n, m, s;
ll dis[MAXN];
bool vis[MAXN];
vector<pair<int, int>> e[MAXN];

void dijkstra(int s) {
    fill(dis + 1, dis + n + 1, INF);
    priority_queue<pli, vector<pli>, greater<pli>> q;
    dis[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x]) continue;
        vis[x] = true;
        for (auto [y, w] : e[x]) {
            if (dis[y] > dis[x] + w) {
                dis[y] = dis[x] + w;
                q.push({dis[y], y});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s;
    while (m--) {
        int x, y, w;
        cin >> x >> y >> w;
        e[x].push_back({y, w});
    }
    dijkstra(s);
    for (int i = 1; i <= n; i++) {
        if (dis[i] == INF) cout << -1;
        else cout << dis[i];
        cout << " \n"[i == n];
    }
    return 0;
}

// 0-1 BFS：边权只有 0/1 的有向图单源最短路。
// 复杂度 O(n+m)，比 Dijkstra 少一个 log。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, s, dis[MAXN];
vector<pair<int, int>> e[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s;
    while (m--) {
        int x, y, w;
        cin >> x >> y >> w;
        e[x].push_back({y, w});
    }
    fill(dis + 1, dis + n + 1, INF);
    deque<int> q;
    dis[s] = 0;
    q.push_front(s);
    while (!q.empty()) {
        int x = q.front();
        q.pop_front();
        for (auto [y, w] : e[x]) {
            if (dis[y] <= dis[x] + w) continue;
            dis[y] = dis[x] + w;
            if (w == 0) q.push_front(y);
            else q.push_back(y);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << (dis[i] == INF ? -1 : dis[i]) << " \n"[i == n];
    }
    return 0;
}

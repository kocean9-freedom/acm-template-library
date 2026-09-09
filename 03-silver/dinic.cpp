// Dinic 最大流：有向图，支持平行边。
// 常见复杂度 O(n^2*m)，二分图等结构通常更快。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

struct Dinic {
    struct Edge { int to, rev; ll cap; };
    int n;
    vector<vector<Edge>> e;
    vector<int> dep, cur;

    Dinic(int n) : n(n), e(n + 1), dep(n + 1), cur(n + 1) {}

    void add(int x, int y, ll c) {
        Edge a{y, (int)e[y].size(), c};
        Edge b{x, (int)e[x].size(), 0};
        e[x].push_back(a);
        e[y].push_back(b);
    }

    bool bfs(int s, int t) {
        fill(dep.begin(), dep.end(), -1);
        queue<int> q;
        dep[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto &ed : e[x]) {
                if (ed.cap > 0 && dep[ed.to] == -1) dep[ed.to] = dep[x] + 1, q.push(ed.to);
            }
        }
        return dep[t] != -1;
    }

    ll dfs(int x, int t, ll flow) {
        if (x == t) return flow;
        ll used = 0;
        for (int &i = cur[x]; i < (int)e[x].size(); i++) {
            Edge &ed = e[x][i];
            if (ed.cap <= 0 || dep[ed.to] != dep[x] + 1) continue;
            ll f = dfs(ed.to, t, min(flow - used, ed.cap));
            if (!f) continue;
            ed.cap -= f;
            e[ed.to][ed.rev].cap += f;
            used += f;
            if (used == flow) break;
        }
        return used;
    }

    ll work(int s, int t) {
        ll ans = 0;
        while (bfs(s, t)) {
            fill(cur.begin(), cur.end(), 0);
            ans += dfs(s, t, INF);
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Dinic flow(n);
    while (m--) {
        int x, y;
        long long c;
        cin >> x >> y >> c;
        flow.add(x, y, c);
    }
    cout << flow.work(s, t) << '\n';
    return 0;
}

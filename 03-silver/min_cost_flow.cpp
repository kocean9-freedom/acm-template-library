// 最小费用最大流：每条边有容量 cap 和单位费用 cost。
// SPFA 找最短增广路，适合常规中小数据；返回 {最大流, 最小费用}。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

struct MCMF {
    struct Edge { int to, rev; ll cap, cost; };
    int n;
    vector<vector<Edge>> e;
    vector<ll> dis;
    vector<int> pv, pe;
    vector<bool> inq;

    MCMF(int n) : n(n), e(n + 1), dis(n + 1), pv(n + 1), pe(n + 1), inq(n + 1) {}

    void add(int x, int y, ll cap, ll cost) {
        Edge a{y, (int)e[y].size(), cap, cost};
        Edge b{x, (int)e[x].size(), 0, -cost};
        e[x].push_back(a);
        e[y].push_back(b);
    }

    bool spfa(int s, int t) {
        fill(dis.begin(), dis.end(), INF);
        fill(inq.begin(), inq.end(), false);
        queue<int> q;
        dis[s] = 0;
        q.push(s);
        inq[s] = true;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            inq[x] = false;
            for (int i = 0; i < (int)e[x].size(); i++) {
                Edge &ed = e[x][i];
                if (ed.cap > 0 && dis[ed.to] > dis[x] + ed.cost) {
                    dis[ed.to] = dis[x] + ed.cost;
                    pv[ed.to] = x;
                    pe[ed.to] = i;
                    if (!inq[ed.to]) inq[ed.to] = true, q.push(ed.to);
                }
            }
        }
        return dis[t] != INF;
    }

    pair<ll, ll> work(int s, int t) {
        ll flow = 0, cost = 0;
        while (spfa(s, t)) {
            ll f = INF;
            for (int x = t; x != s; x = pv[x]) f = min(f, e[pv[x]][pe[x]].cap);
            for (int x = t; x != s; x = pv[x]) {
                Edge &ed = e[pv[x]][pe[x]];
                ed.cap -= f;
                e[x][ed.rev].cap += f;
            }
            flow += f;
            cost += f * dis[t];
        }
        return {flow, cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    MCMF flow(n);
    while (m--) {
        int x, y;
        ll cap, cost;
        cin >> x >> y >> cap >> cost;
        flow.add(x, y, cap, cost);
    }
    auto [f, c] = flow.work(s, t);
    cout << f << ' ' << c << '\n';
    return 0;
}

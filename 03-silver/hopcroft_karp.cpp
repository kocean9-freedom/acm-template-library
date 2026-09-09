// Hopcroft-Karp：二分图最大匹配。BFS 同时找最短增广路层，DFS 批量增广。
// 左点 1..nl，右点 1..nr。复杂度 O(m*sqrt(nl+nr))。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nl, nr, m;
    cin >> nl >> nr >> m;
    vector<vector<int>> e(nl + 1);
    while (m--) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
    }
    vector<int> ml(nl + 1), mr(nr + 1), dis(nl + 1);

    auto bfs = [&]() {
        queue<int> q;
        fill(dis.begin(), dis.end(), -1);
        for (int x = 1; x <= nl; x++) {
            if (!ml[x]) dis[x] = 0, q.push(x);
        }
        bool found = false;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int y : e[x]) {
                if (!mr[y]) found = true;
                else if (dis[mr[y]] == -1) dis[mr[y]] = dis[x] + 1, q.push(mr[y]);
            }
        }
        return found;
    };

    function<bool(int)> dfs = [&](int x) {
        for (int y : e[x]) {
            if (!mr[y] || (dis[mr[y]] == dis[x] + 1 && dfs(mr[y]))) {
                ml[x] = y;
                mr[y] = x;
                return true;
            }
        }
        dis[x] = -1;
        return false;
    };

    int ans = 0;
    while (bfs()) {
        for (int x = 1; x <= nl; x++) if (!ml[x] && dfs(x)) ans++;
    }
    cout << ans << '\n';
    return 0;
}

// 无向图欧拉路：每条边恰走一次，Hierholzer 算法。输出字典序较小的一条路径。
// 存边编号区分重边；需恰有 0 或 2 个奇度点且非零度点连通。O(m log m)。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> e(n + 1);
    vector<int> deg(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back({y, i});
        e[y].push_back({x, i});
        deg[x]++, deg[y]++;
    }
    vector<int> odd;
    for (int i = 1; i <= n; i++) if (deg[i] & 1) odd.push_back(i);
    if (odd.size() != 0 && odd.size() != 2) {
        cout << "NO\n";
        return 0;
    }
    int s = odd.empty() ? 1 : odd[0];
    if (odd.empty()) while (s <= n && deg[s] == 0) s++;
    if (s > n) {
        cout << "1\n";
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        sort(e[i].begin(), e[i].end(), greater<pair<int, int>>());
    }

    vector<char> used(m);
    vector<int> st = {s}, path;
    while (!st.empty()) {
        int x = st.back();
        while (!e[x].empty() && used[e[x].back().second]) e[x].pop_back();
        if (e[x].empty()) {
            path.push_back(x);
            st.pop_back();
        } else {
            auto [y, id] = e[x].back();
            e[x].pop_back();
            if (!used[id]) used[id] = true, st.push_back(y);
        }
    }
    if ((int)path.size() != m + 1) {
        cout << "NO\n";
        return 0;
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i] << " \n"[i + 1 == (int)path.size()];
    }
    return 0;
}

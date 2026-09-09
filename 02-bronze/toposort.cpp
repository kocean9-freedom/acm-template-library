// 拓扑排序：输出有向无环图的字典序最小拓扑序。
// 若存在环输出 -1。复杂度 O((n+m) log n)。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
int n, m, deg[MAXN];
vector<int> e[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    while (m--) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        deg[y]++;
    }
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 1; i <= n; i++) if (!deg[i]) q.push(i);
    vector<int> ans;
    while (!q.empty()) {
        int x = q.top();
        q.pop();
        ans.push_back(x);
        for (int y : e[x]) if (--deg[y] == 0) q.push(y);
    }
    if ((int)ans.size() != n) {
        cout << -1 << '\n';
    } else {
        for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i == n - 1];
    }
    return 0;
}

// 匈牙利增广：二分图最大匹配，左部 1..n1，右部 1..n2。
// 复杂度 O(n1*m)，适合中小图；大图可换 Hopcroft-Karp/Dinic。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
int n1, n2, m, match_r[MAXN], vis[MAXN], tim;
vector<int> e[MAXN];

bool dfs(int x) {
    for (int y : e[x]) {
        if (vis[y] == tim) continue;
        vis[y] = tim;
        if (!match_r[y] || dfs(match_r[y])) {
            match_r[y] = x;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n1 >> n2 >> m;
    while (m--) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
    }
    int ans = 0;
    for (int x = 1; x <= n1; x++) {
        ++tim;
        ans += dfs(x);
    }
    cout << ans << '\n';
    return 0;
}

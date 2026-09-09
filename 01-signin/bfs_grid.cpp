// 网格 BFS：求 S 到 T 的最少四联通步数，# 不能走。
// 复杂度 O(nm)，空间 O(nm)。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int n, m, dis[MAXN][MAXN];
string g[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    pair<int, int> s, t;
    for (int i = 0; i < n; i++) {
        cin >> g[i];
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'S') s = {i, j};
            if (g[i][j] == 'T') t = {i, j};
        }
    }
    memset(dis, -1, sizeof(dis));
    queue<pair<int, int>> q;
    dis[s.first][s.second] = 0;
    q.push(s);
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (g[nx][ny] == '#' || dis[nx][ny] != -1) continue;
            dis[nx][ny] = dis[x][y] + 1;
            q.push({nx, ny});
        }
    }
    cout << dis[t.first][t.second] << '\n';
    return 0;
}

// DSU on tree：求每个子树不同颜色数。轻儿子结果清空，重儿子结果保留。
// 常见复杂度 O(n log n)，本实现用 DFS 序整段增删；深链可能需改迭代 DFS。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
int n, timer, distinct_cnt;
int color[MAXN], siz[MAXN], son[MAXN], in[MAXN], out[MAXN], seq[MAXN], ans[MAXN];
vector<int> e[MAXN], cnt;

void dfs1(int x, int fa) {
    siz[x] = 1;
    in[x] = ++timer;
    seq[timer] = x;
    for (int y : e[x]) {
        if (y == fa) continue;
        dfs1(y, x);
        siz[x] += siz[y];
        if (siz[y] > siz[son[x]]) son[x] = y;
    }
    out[x] = timer;
}

void add_node(int x, int delta) {
    if (delta == 1 && cnt[color[x]]++ == 0) distinct_cnt++;
    if (delta == -1 && --cnt[color[x]] == 0) distinct_cnt--;
}

void add_subtree(int x, int delta) {
    for (int i = in[x]; i <= out[x]; i++) add_node(seq[i], delta);
}

void dfs2(int x, int fa, bool keep) {
    for (int y : e[x]) {
        if (y != fa && y != son[x]) dfs2(y, x, false);
    }
    if (son[x]) dfs2(son[x], x, true);
    for (int y : e[x]) {
        if (y != fa && y != son[x]) add_subtree(y, 1);
    }
    add_node(x, 1);
    ans[x] = distinct_cnt;
    if (!keep) add_subtree(x, -1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vector<int> all(n);
    for (int i = 1; i <= n; i++) cin >> color[i], all[i - 1] = color[i];
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    for (int i = 1; i <= n; i++) {
        color[i] = lower_bound(all.begin(), all.end(), color[i]) - all.begin();
    }
    cnt.assign(all.size(), 0);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs1(1, 0);
    dfs2(1, 0, true);
    for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
    return 0;
}

// 2-SAT：每个条件 (x=a) OR (y=b)，输出任一可行赋值。
// 复杂度 O(n+m)。变量 i 的两个点为 2*i 和 2*i+1。
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 2e6 + 5;

int n, m, tim, top, scc_cnt;
int dfn[MAXV], low[MAXV], st[MAXV], bel[MAXV];
bool ins[MAXV];
vector<int> e[MAXV];

int id(int x, int v) { return (x << 1) | v; }

void tarjan(int x) {
    dfn[x] = low[x] = ++tim;
    st[++top] = x;
    ins[x] = true;
    for (int y : e[x]) {
        if (!dfn[y]) tarjan(y), low[x] = min(low[x], low[y]);
        else if (ins[y]) low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] != low[x]) return;
    ++scc_cnt;
    while (true) {
        int y = st[top--];
        ins[y] = false;
        bel[y] = scc_cnt;
        if (y == x) break;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    while (m--) {
        int x, a, y, b;
        cin >> x >> a >> y >> b;
        e[id(x, a ^ 1)].push_back(id(y, b));
        e[id(y, b ^ 1)].push_back(id(x, a));
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[id(i, 0)]) tarjan(id(i, 0));
        if (!dfn[id(i, 1)]) tarjan(id(i, 1));
    }
    for (int i = 1; i <= n; i++) {
        if (bel[id(i, 0)] == bel[id(i, 1)]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    cout << "POSSIBLE\n";
    for (int i = 1; i <= n; i++) {
        cout << (bel[id(i, 0)] > bel[id(i, 1)]) << " \n"[i == n];
    }
    return 0;
}

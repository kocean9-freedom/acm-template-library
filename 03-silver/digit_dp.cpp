// 数位 DP 示例：统计 [0,n] 中十进制相邻数位不相等的整数个数。
// 状态为 pos/pre/started/tight；复杂度 O(位数*10*状态数)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> dig;
ll memo[20][11][2];
bool seen[20][11][2];

ll dfs(int pos, int pre, bool started, bool tight) {
    if (pos == (int)dig.size()) return 1;  // 包含数字 0。
    if (!tight && seen[pos][pre][started]) return memo[pos][pre][started];
    int up = tight ? dig[pos] : 9;
    ll ans = 0;
    for (int d = 0; d <= up; d++) {
        bool ns = started || d != 0;
        if (started && ns && d == pre) continue;
        ans += dfs(pos + 1, ns ? d : 10, ns, tight && d == up);
    }
    if (!tight) {
        seen[pos][pre][started] = true;
        memo[pos][pre][started] = ans;
    }
    return ans;
}

ll solve(ll n) {
    if (n < 0) return 0;
    dig.clear();
    for (char c : to_string(n)) dig.push_back(c - '0');
    memset(seen, 0, sizeof(seen));
    return dfs(0, 10, false, true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll l, r;
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << '\n';
    return 0;
}

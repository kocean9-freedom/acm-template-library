// Manacher：线性求最长回文子串长度。
// 在原串字符间插入 #，统一处理奇偶回文。复杂度 O(n)。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    string t = "^";
    for (char c : s) t += '#', t += c;
    t += "#$";
    vector<int> p(t.size());
    int center = 0, right = 0, ans = 0;
    for (int i = 1; i + 1 < (int)t.size(); i++) {
        int mirror = 2 * center - i;
        if (i < right) p[i] = min(right - i, p[mirror]);
        while (t[i + p[i] + 1] == t[i - p[i] - 1]) p[i]++;
        if (i + p[i] > right) center = i, right = i + p[i];
        ans = max(ans, p[i]);
    }
    cout << ans << '\n';
    return 0;
}

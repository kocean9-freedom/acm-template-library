// 双模字符串哈希：回答两个子串是否相等，输入区间为 1 下标闭区间。
// 预处理 O(n)，单次 O(1)。哈希有极小碰撞概率；需要绝对正确时改用 SA/KMP 等结构。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD1 = 1000000007;
const ll MOD2 = 1000000009;
const ll BASE = 911382323;

struct Hash {
    vector<ll> h1, h2, p1, p2;

    explicit Hash(const string &s) {
        int n = s.size();
        h1.resize(n + 1);
        h2.resize(n + 1);
        p1.resize(n + 1, 1);
        p2.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            int x = (unsigned char)s[i - 1] + 1;
            h1[i] = (h1[i - 1] * BASE + x) % MOD1;
            h2[i] = (h2[i - 1] * BASE + x) % MOD2;
            p1[i] = p1[i - 1] * BASE % MOD1;
            p2[i] = p2[i - 1] * BASE % MOD2;
        }
    }

    pair<ll, ll> get(int l, int r) const {
        ll x1 = (h1[r] - h1[l - 1] * p1[r - l + 1]) % MOD1;
        ll x2 = (h2[r] - h2[l - 1] * p2[r - l + 1]) % MOD2;
        if (x1 < 0) x1 += MOD1;
        if (x2 < 0) x2 += MOD2;
        return {x1, x2};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int q;
    cin >> s >> q;
    Hash hs(s);
    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        bool same = r1 - l1 == r2 - l2 && hs.get(l1, r1) == hs.get(l2, r2);
        cout << (same ? "Yes" : "No") << '\n';
    }
    return 0;
}

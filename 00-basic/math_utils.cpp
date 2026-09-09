// 整数工具：快速幂、gcd/lcm、扩展欧几里得、正模。
// 复杂度：qpow O(log b)，exgcd O(log min(a,b))。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll qpow(ll a, ll b, ll mod) {
    ll ans = 1 % mod;
    a = (a % mod + mod) % mod;
    while (b) {
        if (b & 1) ans = (__int128)ans * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return ans;
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}

ll inv(ll a, ll mod) {
    ll x, y;
    ll g = exgcd(a, mod, x, y);
    if (g != 1) return -1;
    return (x % mod + mod) % mod;
}

ll mod(ll x, ll p) {
    return (x % p + p) % p;
}

ll safe_lcm(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    return a / gcd(a, b) * b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b, p;
    if (!(cin >> a >> b >> p)) return 0;
    cout << gcd(a, b) << ' ' << safe_lcm(a, b) << '\n';
    cout << qpow(a, b, p) << ' ' << inv(mod(a, p), p) << '\n';
    return 0;
}

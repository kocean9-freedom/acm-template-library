// 数论函数板：线性筛 + 质数模组合数。
// 筛法 O(n)，组合数预处理 O(n)、查询 O(1)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> linear_sieve(int n) {
    vector<int> primes, minp(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!minp[i]) minp[i] = i, primes.push_back(i);
        for (int p : primes) {
            if (p > minp[i] || (ll)i * p > n) break;
            minp[i * p] = p;
        }
    }
    return primes;
}

struct Comb {
    ll mod;
    vector<ll> fac, ifac;

    ll qpow(ll a, ll b) {
        ll ans = 1;
        while (b) {
            if (b & 1) ans = ans * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return ans;
    }

    Comb(int n, ll p) : mod(p), fac(n + 1), ifac(n + 1) {
        fac[0] = 1;
        for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
        ifac[n] = qpow(fac[n], mod - 2);
        for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
    }

    ll C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fac[n] * ifac[k] % mod * ifac[n - k] % mod;
    }
};

int main() {
    return 0;
}

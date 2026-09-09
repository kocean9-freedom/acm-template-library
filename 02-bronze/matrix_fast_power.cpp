// 矩阵快速幂求 k 阶线性递推：F(t)=sum c[i]*F(t-1-i)。
// 输入 F(0..k-1)、c(0..k-1) 和正模数，输出 F(n) mod mod。复杂度 O(k^3 log n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
using i128 = __int128_t;

struct Matrix {
    int n;
    ll mod;
    vector<vector<ll>> a;

    Matrix(int n, ll mod, bool one = false) : n(n), mod(mod), a(n, vector<ll>(n)) {
        if (one) for (int i = 0; i < n; i++) a[i][i] = 1 % mod;
    }

    Matrix operator*(const Matrix &b) const {
        Matrix c(n, mod);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) if (a[i][k]) {
                for (int j = 0; j < n; j++) {
                    c.a[i][j] = (c.a[i][j] + (i128)a[i][k] * b.a[k][j]) % mod;
                }
            }
        }
        return c;
    }
};

Matrix qpow(Matrix a, long long b) {
    Matrix ans(a.n, a.mod, true);
    while (b) {
        if (b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    long long n, mod;
    cin >> k >> n >> mod;
    vector<ll> f(k), c(k);
    for (ll &x : f) cin >> x, x = (x % mod + mod) % mod;
    for (ll &x : c) cin >> x, x = (x % mod + mod) % mod;
    if (n < k) {
        cout << f[n] << '\n';
        return 0;
    }
    Matrix trans(k, mod);
    trans.a[0] = c;
    for (int i = 1; i < k; i++) trans.a[i][i - 1] = 1;
    Matrix pw = qpow(trans, n - k + 1);
    ll ans = 0;
    for (int i = 0; i < k; i++) {
        ans = (ans + (i128)pw.a[0][i] * f[k - 1 - i]) % mod;
    }
    cout << ans << '\n';
    return 0;
}

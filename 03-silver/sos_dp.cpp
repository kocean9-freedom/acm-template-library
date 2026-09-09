// SOS DP：g[mask]=sum_{sub subset mask} f[sub]。
// 位必须放外层，保证每个维度只加入一次。复杂度 O(k*2^k)，空间 O(2^k)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    int n = 1 << k;
    vector<ll> g(n);
    for (ll &x : g) cin >> x;
    for (int bit = 0; bit < k; bit++) {
        for (int mask = 0; mask < n; mask++) {
            if (mask >> bit & 1) g[mask] += g[mask ^ 1 << bit];
        }
    }
    for (int mask = 0; mask < n; mask++) cout << g[mask] << " \n"[mask + 1 == n];
    return 0;
}

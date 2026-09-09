// 子集枚举骨架：统计和等于 target 的子集数量，n <= 25。
// 重点不是这道题，而是先算状态数，再用位掩码完整枚举。复杂度 O(n*2^n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll target;
    cin >> n >> target;
    vector<ll> a(n);
    for (ll &x : a) cin >> x;

    ll ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) sum += a[i];
        }
        ans += sum == target;
    }
    cout << ans << '\n';
    return 0;
}

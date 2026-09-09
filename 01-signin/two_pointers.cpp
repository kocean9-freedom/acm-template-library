// 双指针：非负数组中，和不超过 m 的最长连续子段。
// 题面若允许负数，窗口单调性失效，不能直接套用。
// 复杂度：O(n)，空间 O(n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 5;

int n;
ll m, a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0;
    ll sum = 0;
    for (int l = 1, r = 1; r <= n; r++) {
        sum += a[r];
        while (l <= r && sum > m) sum -= a[l++];
        ans = max(ans, r - l + 1);
    }
    cout << ans << '\n';
    return 0;
}

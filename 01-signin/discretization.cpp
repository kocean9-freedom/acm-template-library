// 离散化：将任意整数映射到从 1 开始的排名，相等元素排名相同。
// 复杂度 O(n log n)，空间 O(n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n + 1), b;
    for (int i = 1; i <= n; i++) cin >> a[i], b.push_back(a[i]);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 1; i <= n; i++) {
        int id = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
        cout << id << " \n"[i == n];
    }
    return 0;
}

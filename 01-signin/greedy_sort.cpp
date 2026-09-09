// 区间调度：选最多个两两不重叠的半开区间 [l,r)。
// 按右端点升序，能接就选；交换论证可把任一最优解首段换成最早结束段。O(n log n)。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> seg(n);
    for (auto &[l, r] : seg) cin >> l >> r;
    sort(seg.begin(), seg.end(), [](auto a, auto b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    int ans = 0, last = numeric_limits<int>::min();
    for (auto [l, r] : seg) {
        if (l >= last) {
            ans++;
            last = r;
        }
    }
    cout << ans << '\n';
    return 0;
}
